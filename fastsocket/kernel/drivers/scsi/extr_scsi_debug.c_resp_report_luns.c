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
struct scsi_lun {int* scsi_lun; } ;
struct scsi_cmnd {scalar_t__ cmnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  INVALID_FIELD_IN_CDB ; 
 int SAM2_LUN_ADDRESS_METHOD ; 
 int SAM2_WLUN_REPORT_LUNS ; 
 int SDEBUG_RLUN_ARR_SZ ; 
 int check_condition_result ; 
 int fill_from_dev_buffer (struct scsi_cmnd*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mk_sense_buffer (struct sdebug_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int scsi_debug_max_luns ; 
 scalar_t__ scsi_debug_no_lun_0 ; 

__attribute__((used)) static int resp_report_luns(struct scsi_cmnd * scp,
			    struct sdebug_dev_info * devip)
{
	unsigned int alloc_len;
	int lun_cnt, i, upper, num, n, wlun, lun;
	unsigned char *cmd = (unsigned char *)scp->cmnd;
	int select_report = (int)cmd[2];
	struct scsi_lun *one_lun;
	unsigned char arr[SDEBUG_RLUN_ARR_SZ];
	unsigned char * max_addr;

	alloc_len = cmd[9] + (cmd[8] << 8) + (cmd[7] << 16) + (cmd[6] << 24);
	if ((alloc_len < 4) || (select_report > 2)) {
		mk_sense_buffer(devip, ILLEGAL_REQUEST, INVALID_FIELD_IN_CDB,
			       	0);
		return check_condition_result;
	}
	/* can produce response with up to 16k luns (lun 0 to lun 16383) */
	memset(arr, 0, SDEBUG_RLUN_ARR_SZ);
	lun_cnt = scsi_debug_max_luns;
	if (1 == select_report)
		lun_cnt = 0;
	else if (scsi_debug_no_lun_0 && (lun_cnt > 0))
		--lun_cnt;
	wlun = (select_report > 0) ? 1 : 0;
	num = lun_cnt + wlun;
	arr[2] = ((sizeof(struct scsi_lun) * num) >> 8) & 0xff;
	arr[3] = (sizeof(struct scsi_lun) * num) & 0xff;
	n = min((int)((SDEBUG_RLUN_ARR_SZ - 8) /
			    sizeof(struct scsi_lun)), num);
	if (n < num) {
		wlun = 0;
		lun_cnt = n;
	}
	one_lun = (struct scsi_lun *) &arr[8];
	max_addr = arr + SDEBUG_RLUN_ARR_SZ;
	for (i = 0, lun = (scsi_debug_no_lun_0 ? 1 : 0);
             ((i < lun_cnt) && ((unsigned char *)(one_lun + i) < max_addr));
	     i++, lun++) {
		upper = (lun >> 8) & 0x3f;
		if (upper)
			one_lun[i].scsi_lun[0] =
			    (upper | (SAM2_LUN_ADDRESS_METHOD << 6));
		one_lun[i].scsi_lun[1] = lun & 0xff;
	}
	if (wlun) {
		one_lun[i].scsi_lun[0] = (SAM2_WLUN_REPORT_LUNS >> 8) & 0xff;
		one_lun[i].scsi_lun[1] = SAM2_WLUN_REPORT_LUNS & 0xff;
		i++;
	}
	alloc_len = (unsigned char *)(one_lun + i) - arr;
	return fill_from_dev_buffer(scp, arr,
				    min((int)alloc_len, SDEBUG_RLUN_ARR_SZ));
}