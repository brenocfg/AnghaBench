#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sdebug_dev_info {int target; TYPE_2__* sdbg_host; } ;
struct scsi_cmnd {scalar_t__ cmnd; } ;
struct TYPE_4__ {TYPE_1__* shost; } ;
struct TYPE_3__ {int host_no; } ;

/* Variables and functions */
 scalar_t__ DEV_READONLY (int) ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_FIELD_IN_CDB ; 
 unsigned char MODE_SENSE ; 
 int /*<<< orphan*/  SAVING_PARAMS_UNSUP ; 
 int SDEBUG_MAX_MSENSE_SZ ; 
 int check_condition_result ; 
 int check_readiness (struct scsi_cmnd*,int,struct sdebug_dev_info*) ; 
 int fill_from_dev_buffer (struct scsi_cmnd*,unsigned char*,int /*<<< orphan*/ ) ; 
 int get_sdebug_capacity () ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int /*<<< orphan*/  mk_sense_buffer (struct sdebug_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int resp_caching_pg (unsigned char*,int,int) ; 
 int resp_ctrl_m_pg (unsigned char*,int,int) ; 
 int resp_disconnect_pg (unsigned char*,int,int) ; 
 int resp_err_recov_pg (unsigned char*,int,int) ; 
 int resp_format_pg (unsigned char*,int,int) ; 
 int resp_iec_m_pg (unsigned char*,int,int) ; 
 int resp_sas_pcd_m_spg (unsigned char*,int,int,int) ; 
 int resp_sas_sf_m_pg (unsigned char*,int,int) ; 
 int resp_sas_sha_m_spg (unsigned char*,int) ; 
 scalar_t__ scsi_debug_ptype ; 
 int scsi_debug_sector_size ; 
 int sdebug_capacity ; 

__attribute__((used)) static int resp_mode_sense(struct scsi_cmnd * scp, int target,
			   struct sdebug_dev_info * devip)
{
	unsigned char dbd, llbaa;
	int pcontrol, pcode, subpcode, bd_len;
	unsigned char dev_spec;
	int k, alloc_len, msense_6, offset, len, errsts, target_dev_id;
	unsigned char * ap;
	unsigned char arr[SDEBUG_MAX_MSENSE_SZ];
	unsigned char *cmd = (unsigned char *)scp->cmnd;

	if ((errsts = check_readiness(scp, 1, devip)))
		return errsts;
	dbd = !!(cmd[1] & 0x8);
	pcontrol = (cmd[2] & 0xc0) >> 6;
	pcode = cmd[2] & 0x3f;
	subpcode = cmd[3];
	msense_6 = (MODE_SENSE == cmd[0]);
	llbaa = msense_6 ? 0 : !!(cmd[1] & 0x10);
	if ((0 == scsi_debug_ptype) && (0 == dbd))
		bd_len = llbaa ? 16 : 8;
	else
		bd_len = 0;
	alloc_len = msense_6 ? cmd[4] : ((cmd[7] << 8) | cmd[8]);
	memset(arr, 0, SDEBUG_MAX_MSENSE_SZ);
	if (0x3 == pcontrol) {  /* Saving values not supported */
		mk_sense_buffer(devip, ILLEGAL_REQUEST, SAVING_PARAMS_UNSUP,
			       	0);
		return check_condition_result;
	}
	target_dev_id = ((devip->sdbg_host->shost->host_no + 1) * 2000) +
			(devip->target * 1000) - 3;
	/* set DPOFUA bit for disks */
	if (0 == scsi_debug_ptype)
		dev_spec = (DEV_READONLY(target) ? 0x80 : 0x0) | 0x10;
	else
		dev_spec = 0x0;
	if (msense_6) {
		arr[2] = dev_spec;
		arr[3] = bd_len;
		offset = 4;
	} else {
		arr[3] = dev_spec;
		if (16 == bd_len)
			arr[4] = 0x1;	/* set LONGLBA bit */
		arr[7] = bd_len;	/* assume 255 or less */
		offset = 8;
	}
	ap = arr + offset;
	if ((bd_len > 0) && (!sdebug_capacity))
		sdebug_capacity = get_sdebug_capacity();

	if (8 == bd_len) {
		if (sdebug_capacity > 0xfffffffe) {
			ap[0] = 0xff;
			ap[1] = 0xff;
			ap[2] = 0xff;
			ap[3] = 0xff;
		} else {
			ap[0] = (sdebug_capacity >> 24) & 0xff;
			ap[1] = (sdebug_capacity >> 16) & 0xff;
			ap[2] = (sdebug_capacity >> 8) & 0xff;
			ap[3] = sdebug_capacity & 0xff;
		}
		ap[6] = (scsi_debug_sector_size >> 8) & 0xff;
		ap[7] = scsi_debug_sector_size & 0xff;
		offset += bd_len;
		ap = arr + offset;
	} else if (16 == bd_len) {
		unsigned long long capac = sdebug_capacity;

        	for (k = 0; k < 8; ++k, capac >>= 8)
                	ap[7 - k] = capac & 0xff;
		ap[12] = (scsi_debug_sector_size >> 24) & 0xff;
		ap[13] = (scsi_debug_sector_size >> 16) & 0xff;
		ap[14] = (scsi_debug_sector_size >> 8) & 0xff;
		ap[15] = scsi_debug_sector_size & 0xff;
		offset += bd_len;
		ap = arr + offset;
	}

	if ((subpcode > 0x0) && (subpcode < 0xff) && (0x19 != pcode)) {
		/* TODO: Control Extension page */
		mk_sense_buffer(devip, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB,
			       	0);
		return check_condition_result;
	}
	switch (pcode) {
	case 0x1:	/* Read-Write error recovery page, direct access */
		len = resp_err_recov_pg(ap, pcontrol, target);
		offset += len;
		break;
	case 0x2:	/* Disconnect-Reconnect page, all devices */
		len = resp_disconnect_pg(ap, pcontrol, target);
		offset += len;
		break;
        case 0x3:       /* Format device page, direct access */
                len = resp_format_pg(ap, pcontrol, target);
                offset += len;
                break;
	case 0x8:	/* Caching page, direct access */
		len = resp_caching_pg(ap, pcontrol, target);
		offset += len;
		break;
	case 0xa:	/* Control Mode page, all devices */
		len = resp_ctrl_m_pg(ap, pcontrol, target);
		offset += len;
		break;
	case 0x19:	/* if spc==1 then sas phy, control+discover */
		if ((subpcode > 0x2) && (subpcode < 0xff)) {
		        mk_sense_buffer(devip, ILLEGAL_REQUEST,
					INVALID_FIELD_IN_CDB, 0);
			return check_condition_result;
	        }
		len = 0;
		if ((0x0 == subpcode) || (0xff == subpcode))
			len += resp_sas_sf_m_pg(ap + len, pcontrol, target);
		if ((0x1 == subpcode) || (0xff == subpcode))
			len += resp_sas_pcd_m_spg(ap + len, pcontrol, target,
						  target_dev_id);
		if ((0x2 == subpcode) || (0xff == subpcode))
			len += resp_sas_sha_m_spg(ap + len, pcontrol);
		offset += len;
		break;
	case 0x1c:	/* Informational Exceptions Mode page, all devices */
		len = resp_iec_m_pg(ap, pcontrol, target);
		offset += len;
		break;
	case 0x3f:	/* Read all Mode pages */
		if ((0 == subpcode) || (0xff == subpcode)) {
			len = resp_err_recov_pg(ap, pcontrol, target);
			len += resp_disconnect_pg(ap + len, pcontrol, target);
			len += resp_format_pg(ap + len, pcontrol, target);
			len += resp_caching_pg(ap + len, pcontrol, target);
			len += resp_ctrl_m_pg(ap + len, pcontrol, target);
			len += resp_sas_sf_m_pg(ap + len, pcontrol, target);
			if (0xff == subpcode) {
				len += resp_sas_pcd_m_spg(ap + len, pcontrol,
						  target, target_dev_id);
				len += resp_sas_sha_m_spg(ap + len, pcontrol);
			}
			len += resp_iec_m_pg(ap + len, pcontrol, target);
		} else {
			mk_sense_buffer(devip, ILLEGAL_REQUEST,
					INVALID_FIELD_IN_CDB, 0);
			return check_condition_result;
                }
		offset += len;
		break;
	default:
		mk_sense_buffer(devip, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB,
			       	0);
		return check_condition_result;
	}
	if (msense_6)
		arr[0] = offset - 1;
	else {
		arr[0] = ((offset - 2) >> 8) & 0xff;
		arr[1] = (offset - 2) & 0xff;
	}
	return fill_from_dev_buffer(scp, arr, min(alloc_len, offset));
}