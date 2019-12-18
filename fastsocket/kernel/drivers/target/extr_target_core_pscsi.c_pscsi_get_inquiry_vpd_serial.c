#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct t10_wwn {TYPE_1__* t10_dev; int /*<<< orphan*/ * unit_serial; } ;
struct scsi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DF_FIRMWARE_VPD_UNIT_SERIAL ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 unsigned char INQUIRY ; 
 int INQUIRY_VPD_SERIAL_LEN ; 
 int MAX_COMMAND_SIZE ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int scsi_execute_req (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,unsigned char*) ; 

__attribute__((used)) static int
pscsi_get_inquiry_vpd_serial(struct scsi_device *sdev, struct t10_wwn *wwn)
{
	unsigned char cdb[MAX_COMMAND_SIZE], *buf;
	int ret;

	buf = kzalloc(INQUIRY_VPD_SERIAL_LEN, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	memset(cdb, 0, MAX_COMMAND_SIZE);
	cdb[0] = INQUIRY;
	cdb[1] = 0x01; /* Query VPD */
	cdb[2] = 0x80; /* Unit Serial Number */
	cdb[3] = (INQUIRY_VPD_SERIAL_LEN >> 8) & 0xff;
	cdb[4] = (INQUIRY_VPD_SERIAL_LEN & 0xff);

	ret = scsi_execute_req(sdev, cdb, DMA_FROM_DEVICE, buf,
			      INQUIRY_VPD_SERIAL_LEN, NULL, HZ, 1, NULL);
	if (ret)
		goto out_free;

	snprintf(&wwn->unit_serial[0], INQUIRY_VPD_SERIAL_LEN, "%s", &buf[4]);

	wwn->t10_dev->dev_flags |= DF_FIRMWARE_VPD_UNIT_SERIAL;

	kfree(buf);
	return 0;

out_free:
	kfree(buf);
	return -EPERM;
}