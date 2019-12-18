#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctlr_info_t ;
struct TYPE_5__ {int /*<<< orphan*/ * data_byte; } ;
typedef  TYPE_1__ InquiryData_struct ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_INQUIRY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IO_OK ; 
 size_t MODEL_LEN ; 
 size_t REV_LEN ; 
 int /*<<< orphan*/  TYPE_CMD ; 
 size_t VENDOR_LEN ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_unit_to_scsi3addr (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int sendcmd_withirq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cciss_get_device_descr(ctlr_info_t *h, int logvol, char *vendor,
	char *model, char *rev)
{
	int rc;
	InquiryData_struct *inq_buf;
	unsigned char scsi3addr[8];

	*vendor = '\0';
	*model = '\0';
	*rev = '\0';

	inq_buf = kzalloc(sizeof(InquiryData_struct), GFP_KERNEL);
	if (!inq_buf)
		return;

	log_unit_to_scsi3addr(h, scsi3addr, logvol);
	rc = sendcmd_withirq(h, CISS_INQUIRY, inq_buf,
			     sizeof(InquiryData_struct), 0,
				scsi3addr, TYPE_CMD);
	if (rc == IO_OK) {
		memcpy(vendor, &inq_buf->data_byte[8], VENDOR_LEN);
		vendor[VENDOR_LEN] = '\0';
		memcpy(model, &inq_buf->data_byte[16], MODEL_LEN);
		model[MODEL_LEN] = '\0';
		memcpy(rev, &inq_buf->data_byte[32], REV_LEN);
		rev[REV_LEN] = '\0';
	}

	kfree(inq_buf);
	return;
}