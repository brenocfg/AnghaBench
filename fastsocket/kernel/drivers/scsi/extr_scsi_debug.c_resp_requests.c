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
struct sdebug_dev_info {int reset; unsigned char* sense_buff; } ;
struct scsi_cmnd {scalar_t__ cmnd; } ;
typedef  int /*<<< orphan*/  arr ;

/* Variables and functions */
 int /*<<< orphan*/  NO_ADDITIONAL_SENSE ; 
 int SDEBUG_SENSE_LEN ; 
 unsigned char THRESHOLD_EXCEEDED ; 
 int fill_from_dev_buffer (struct scsi_cmnd*,unsigned char*,int) ; 
 int* iec_m_pg ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mk_sense_buffer (struct sdebug_dev_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ scsi_debug_dsense ; 

__attribute__((used)) static int resp_requests(struct scsi_cmnd * scp,
			 struct sdebug_dev_info * devip)
{
	unsigned char * sbuff;
	unsigned char *cmd = (unsigned char *)scp->cmnd;
	unsigned char arr[SDEBUG_SENSE_LEN];
	int want_dsense;
	int len = 18;

	memset(arr, 0, sizeof(arr));
	if (devip->reset == 1)
		mk_sense_buffer(devip, 0, NO_ADDITIONAL_SENSE, 0);
	want_dsense = !!(cmd[1] & 1) || scsi_debug_dsense;
	sbuff = devip->sense_buff;
	if ((iec_m_pg[2] & 0x4) && (6 == (iec_m_pg[3] & 0xf))) {
		if (want_dsense) {
			arr[0] = 0x72;
			arr[1] = 0x0;		/* NO_SENSE in sense_key */
			arr[2] = THRESHOLD_EXCEEDED;
			arr[3] = 0xff;		/* TEST set and MRIE==6 */
		} else {
			arr[0] = 0x70;
			arr[2] = 0x0;		/* NO_SENSE in sense_key */
			arr[7] = 0xa;   	/* 18 byte sense buffer */
			arr[12] = THRESHOLD_EXCEEDED;
			arr[13] = 0xff;		/* TEST set and MRIE==6 */
		}
	} else {
		memcpy(arr, sbuff, SDEBUG_SENSE_LEN);
		if ((cmd[1] & 1) && (! scsi_debug_dsense)) {
			/* DESC bit set and sense_buff in fixed format */
			memset(arr, 0, sizeof(arr));
			arr[0] = 0x72;
			arr[1] = sbuff[2];     /* sense key */
			arr[2] = sbuff[12];    /* asc */
			arr[3] = sbuff[13];    /* ascq */
			len = 8;
		}
	}
	mk_sense_buffer(devip, 0, NO_ADDITIONAL_SENSE, 0);
	return fill_from_dev_buffer(scp, arr, len);
}