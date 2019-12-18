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
typedef  size_t u32 ;
typedef  int u16 ;
struct t10_alua_tg_pt_gp_member {int /*<<< orphan*/  tg_pt_gp_mem_lock; struct t10_alua_tg_pt_gp* tg_pt_gp; } ;
struct t10_alua_tg_pt_gp {int tg_pt_gp_id; } ;
struct t10_alua_lu_gp_member {int /*<<< orphan*/  lu_gp_mem_lock; struct t10_alua_lu_gp* lu_gp; } ;
struct t10_alua_lu_gp {int lu_gp_id; } ;
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_port {int sep_rtpi; struct t10_alua_tg_pt_gp_member* sep_alua_tg_pt_gp_mem; struct se_portal_group* sep_tpg; } ;
struct se_lun {struct se_port* lun_sep; } ;
struct TYPE_4__ {unsigned char* model; unsigned char* unit_serial; } ;
struct se_device {int dev_flags; struct t10_alua_lu_gp_member* dev_alua_lu_gp_mem; TYPE_2__ t10_wwn; } ;
struct se_cmd {struct se_lun* se_lun; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_3__ {int (* get_fabric_proto_ident ) (struct se_portal_group*) ;unsigned char* (* tpg_get_wwn ) (struct se_portal_group*) ;int (* tpg_get_tag ) (struct se_portal_group*) ;} ;

/* Variables and functions */
 int DF_EMULATED_VPD_UNIT_SERIAL ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char*,int) ; 
 int /*<<< orphan*/  spc_parse_naa_6h_vendor_specific (struct se_device*,unsigned char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 size_t sprintf (unsigned char*,char*,unsigned char*,...) ; 
 size_t strlen (unsigned char*) ; 
 int stub1 (struct se_portal_group*) ; 
 int stub2 (struct se_portal_group*) ; 
 unsigned char* stub3 (struct se_portal_group*) ; 
 int stub4 (struct se_portal_group*) ; 
 int stub5 (struct se_portal_group*) ; 
 unsigned char* stub6 (struct se_portal_group*) ; 
 char* stub7 (struct se_portal_group*) ; 

sense_reason_t
spc_emulate_evpd_83(struct se_cmd *cmd, unsigned char *buf)
{
	struct se_device *dev = cmd->se_dev;
	struct se_lun *lun = cmd->se_lun;
	struct se_port *port = NULL;
	struct se_portal_group *tpg = NULL;
	struct t10_alua_lu_gp_member *lu_gp_mem;
	struct t10_alua_tg_pt_gp *tg_pt_gp;
	struct t10_alua_tg_pt_gp_member *tg_pt_gp_mem;
	unsigned char *prod = &dev->t10_wwn.model[0];
	u32 prod_len;
	u32 unit_serial_len, off = 0;
	u16 len = 0, id_len;

	off = 4;

	/*
	 * NAA IEEE Registered Extended Assigned designator format, see
	 * spc4r17 section 7.7.3.6.5
	 *
	 * We depend upon a target_core_mod/ConfigFS provided
	 * /sys/kernel/config/target/core/$HBA/$DEV/wwn/vpd_unit_serial
	 * value in order to return the NAA id.
	 */
	if (!(dev->dev_flags & DF_EMULATED_VPD_UNIT_SERIAL))
		goto check_t10_vend_desc;

	/* CODE SET == Binary */
	buf[off++] = 0x1;

	/* Set ASSOCIATION == addressed logical unit: 0)b */
	buf[off] = 0x00;

	/* Identifier/Designator type == NAA identifier */
	buf[off++] |= 0x3;
	off++;

	/* Identifier/Designator length */
	buf[off++] = 0x10;

	/*
	 * Start NAA IEEE Registered Extended Identifier/Designator
	 */
	buf[off++] = (0x6 << 4);

	/*
	 * Use OpenFabrics IEEE Company ID: 00 14 05
	 */
	buf[off++] = 0x01;
	buf[off++] = 0x40;
	buf[off] = (0x5 << 4);

	/*
	 * Return ConfigFS Unit Serial Number information for
	 * VENDOR_SPECIFIC_IDENTIFIER and
	 * VENDOR_SPECIFIC_IDENTIFIER_EXTENTION
	 */
	spc_parse_naa_6h_vendor_specific(dev, &buf[off]);

	len = 20;
	off = (len + 4);

check_t10_vend_desc:
	/*
	 * T10 Vendor Identifier Page, see spc4r17 section 7.7.3.4
	 */
	id_len = 8; /* For Vendor field */
	prod_len = 4; /* For VPD Header */
	prod_len += 8; /* For Vendor field */
	prod_len += strlen(prod);
	prod_len++; /* For : */

	if (dev->dev_flags & DF_EMULATED_VPD_UNIT_SERIAL) {
		unit_serial_len = strlen(&dev->t10_wwn.unit_serial[0]);
		unit_serial_len++; /* For NULL Terminator */

		id_len += sprintf(&buf[off+12], "%s:%s", prod,
				&dev->t10_wwn.unit_serial[0]);
	}
	buf[off] = 0x2; /* ASCII */
	buf[off+1] = 0x1; /* T10 Vendor ID */
	buf[off+2] = 0x0;
	memcpy(&buf[off+4], "LIO-ORG", 8);
	/* Extra Byte for NULL Terminator */
	id_len++;
	/* Identifier Length */
	buf[off+3] = id_len;
	/* Header size for Designation descriptor */
	len += (id_len + 4);
	off += (id_len + 4);
	/*
	 * struct se_port is only set for INQUIRY VPD=1 through $FABRIC_MOD
	 */
	port = lun->lun_sep;
	if (port) {
		struct t10_alua_lu_gp *lu_gp;
		u32 padding, scsi_name_len;
		u16 lu_gp_id = 0;
		u16 tg_pt_gp_id = 0;
		u16 tpgt;

		tpg = port->sep_tpg;
		/*
		 * Relative target port identifer, see spc4r17
		 * section 7.7.3.7
		 *
		 * Get the PROTOCOL IDENTIFIER as defined by spc4r17
		 * section 7.5.1 Table 362
		 */
		buf[off] =
			(tpg->se_tpg_tfo->get_fabric_proto_ident(tpg) << 4);
		buf[off++] |= 0x1; /* CODE SET == Binary */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == target port: 01b */
		buf[off] |= 0x10;
		/* DESIGNATOR TYPE == Relative target port identifer */
		buf[off++] |= 0x4;
		off++; /* Skip over Reserved */
		buf[off++] = 4; /* DESIGNATOR LENGTH */
		/* Skip over Obsolete field in RTPI payload
		 * in Table 472 */
		off += 2;
		buf[off++] = ((port->sep_rtpi >> 8) & 0xff);
		buf[off++] = (port->sep_rtpi & 0xff);
		len += 8; /* Header size + Designation descriptor */
		/*
		 * Target port group identifier, see spc4r17
		 * section 7.7.3.8
		 *
		 * Get the PROTOCOL IDENTIFIER as defined by spc4r17
		 * section 7.5.1 Table 362
		 */
		tg_pt_gp_mem = port->sep_alua_tg_pt_gp_mem;
		if (!tg_pt_gp_mem)
			goto check_lu_gp;

		spin_lock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);
		tg_pt_gp = tg_pt_gp_mem->tg_pt_gp;
		if (!tg_pt_gp) {
			spin_unlock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);
			goto check_lu_gp;
		}
		tg_pt_gp_id = tg_pt_gp->tg_pt_gp_id;
		spin_unlock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);

		buf[off] =
			(tpg->se_tpg_tfo->get_fabric_proto_ident(tpg) << 4);
		buf[off++] |= 0x1; /* CODE SET == Binary */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == target port: 01b */
		buf[off] |= 0x10;
		/* DESIGNATOR TYPE == Target port group identifier */
		buf[off++] |= 0x5;
		off++; /* Skip over Reserved */
		buf[off++] = 4; /* DESIGNATOR LENGTH */
		off += 2; /* Skip over Reserved Field */
		buf[off++] = ((tg_pt_gp_id >> 8) & 0xff);
		buf[off++] = (tg_pt_gp_id & 0xff);
		len += 8; /* Header size + Designation descriptor */
		/*
		 * Logical Unit Group identifier, see spc4r17
		 * section 7.7.3.8
		 */
check_lu_gp:
		lu_gp_mem = dev->dev_alua_lu_gp_mem;
		if (!lu_gp_mem)
			goto check_scsi_name;

		spin_lock(&lu_gp_mem->lu_gp_mem_lock);
		lu_gp = lu_gp_mem->lu_gp;
		if (!lu_gp) {
			spin_unlock(&lu_gp_mem->lu_gp_mem_lock);
			goto check_scsi_name;
		}
		lu_gp_id = lu_gp->lu_gp_id;
		spin_unlock(&lu_gp_mem->lu_gp_mem_lock);

		buf[off++] |= 0x1; /* CODE SET == Binary */
		/* DESIGNATOR TYPE == Logical Unit Group identifier */
		buf[off++] |= 0x6;
		off++; /* Skip over Reserved */
		buf[off++] = 4; /* DESIGNATOR LENGTH */
		off += 2; /* Skip over Reserved Field */
		buf[off++] = ((lu_gp_id >> 8) & 0xff);
		buf[off++] = (lu_gp_id & 0xff);
		len += 8; /* Header size + Designation descriptor */
		/*
		 * SCSI name string designator, see spc4r17
		 * section 7.7.3.11
		 *
		 * Get the PROTOCOL IDENTIFIER as defined by spc4r17
		 * section 7.5.1 Table 362
		 */
check_scsi_name:
		scsi_name_len = strlen(tpg->se_tpg_tfo->tpg_get_wwn(tpg));
		/* UTF-8 ",t,0x<16-bit TPGT>" + NULL Terminator */
		scsi_name_len += 10;
		/* Check for 4-byte padding */
		padding = ((-scsi_name_len) & 3);
		if (padding != 0)
			scsi_name_len += padding;
		/* Header size + Designation descriptor */
		scsi_name_len += 4;

		buf[off] =
			(tpg->se_tpg_tfo->get_fabric_proto_ident(tpg) << 4);
		buf[off++] |= 0x3; /* CODE SET == UTF-8 */
		buf[off] = 0x80; /* Set PIV=1 */
		/* Set ASSOCIATION == target port: 01b */
		buf[off] |= 0x10;
		/* DESIGNATOR TYPE == SCSI name string */
		buf[off++] |= 0x8;
		off += 2; /* Skip over Reserved and length */
		/*
		 * SCSI name string identifer containing, $FABRIC_MOD
		 * dependent information.  For LIO-Target and iSCSI
		 * Target Port, this means "<iSCSI name>,t,0x<TPGT> in
		 * UTF-8 encoding.
		 */
		tpgt = tpg->se_tpg_tfo->tpg_get_tag(tpg);
		scsi_name_len = sprintf(&buf[off], "%s,t,0x%04x",
					tpg->se_tpg_tfo->tpg_get_wwn(tpg), tpgt);
		scsi_name_len += 1 /* Include  NULL terminator */;
		/*
		 * The null-terminated, null-padded (see 4.4.2) SCSI
		 * NAME STRING field contains a UTF-8 format string.
		 * The number of bytes in the SCSI NAME STRING field
		 * (i.e., the value in the DESIGNATOR LENGTH field)
		 * shall be no larger than 256 and shall be a multiple
		 * of four.
		 */
		if (padding)
			scsi_name_len += padding;

		buf[off-1] = scsi_name_len;
		off += scsi_name_len;
		/* Header size + Designation descriptor */
		len += (scsi_name_len + 4);
	}
	buf[2] = ((len >> 8) & 0xff);
	buf[3] = (len & 0xff); /* Page Length for VPD 0x83 */
	return 0;
}