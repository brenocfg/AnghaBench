#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sdebug_dev_info {int dummy; } ;
struct scsi_cmnd {scalar_t__ cmnd; } ;

/* Variables and functions */
 int SDEBUG_READCAP16_ARR_SZ ; 
 int check_readiness (struct scsi_cmnd*,int,struct sdebug_dev_info*) ; 
 int fill_from_dev_buffer (struct scsi_cmnd*,unsigned char*,int /*<<< orphan*/ ) ; 
 int get_sdebug_capacity () ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min (int,int) ; 
 int scsi_debug_dif ; 
 scalar_t__ scsi_debug_lbp () ; 
 int scsi_debug_lowest_aligned ; 
 int scsi_debug_physblk_exp ; 
 int scsi_debug_sector_size ; 
 int sdebug_capacity ; 

__attribute__((used)) static int resp_readcap16(struct scsi_cmnd * scp,
			  struct sdebug_dev_info * devip)
{
	unsigned char *cmd = (unsigned char *)scp->cmnd;
	unsigned char arr[SDEBUG_READCAP16_ARR_SZ];
	unsigned long long capac;
	int errsts, k, alloc_len;

	if ((errsts = check_readiness(scp, 1, devip)))
		return errsts;
	alloc_len = ((cmd[10] << 24) + (cmd[11] << 16) + (cmd[12] << 8)
		     + cmd[13]);
	/* following just in case virtual_gb changed */
	sdebug_capacity = get_sdebug_capacity();
	memset(arr, 0, SDEBUG_READCAP16_ARR_SZ);
	capac = sdebug_capacity - 1;
	for (k = 0; k < 8; ++k, capac >>= 8)
		arr[7 - k] = capac & 0xff;
	arr[8] = (scsi_debug_sector_size >> 24) & 0xff;
	arr[9] = (scsi_debug_sector_size >> 16) & 0xff;
	arr[10] = (scsi_debug_sector_size >> 8) & 0xff;
	arr[11] = scsi_debug_sector_size & 0xff;
	arr[13] = scsi_debug_physblk_exp & 0xf;
	arr[14] = (scsi_debug_lowest_aligned >> 8) & 0x3f;

	if (scsi_debug_lbp())
		arr[14] |= 0x80; /* LBPME */

	arr[15] = scsi_debug_lowest_aligned & 0xff;

	if (scsi_debug_dif) {
		arr[12] = (scsi_debug_dif - 1) << 1; /* P_TYPE */
		arr[12] |= 1; /* PROT_EN */
	}

	return fill_from_dev_buffer(scp, arr,
				    min(alloc_len, SDEBUG_READCAP16_ARR_SZ));
}