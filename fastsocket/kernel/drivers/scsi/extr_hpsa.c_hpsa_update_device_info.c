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
struct hpsa_scsi_dev_t {unsigned char devtype; int /*<<< orphan*/  raid_level; int /*<<< orphan*/  device_id; int /*<<< orphan*/  model; int /*<<< orphan*/  vendor; int /*<<< orphan*/  scsi3addr; } ;
struct ctlr_info {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OBDR_SIG_LEN ; 
 size_t OBDR_SIG_OFFSET ; 
 scalar_t__ OBDR_TAPE_INQ_SIZE ; 
 int /*<<< orphan*/  OBDR_TAPE_SIG ; 
 int /*<<< orphan*/  RAID_UNKNOWN ; 
 unsigned char TYPE_DISK ; 
 unsigned char TYPE_ROM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hpsa_get_device_id (struct ctlr_info*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hpsa_get_raid_level (struct ctlr_info*,unsigned char*,int /*<<< orphan*/ *) ; 
 scalar_t__ hpsa_scsi_do_inquiry (struct ctlr_info*,unsigned char*,int /*<<< orphan*/ ,unsigned char*,unsigned char) ; 
 scalar_t__ is_logical_dev_addr_mode (unsigned char*) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strncmp (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hpsa_update_device_info(struct ctlr_info *h,
	unsigned char scsi3addr[], struct hpsa_scsi_dev_t *this_device,
	unsigned char *is_OBDR_device)
{

#define OBDR_SIG_OFFSET 43
#define OBDR_TAPE_SIG "$DR-10"
#define OBDR_SIG_LEN (sizeof(OBDR_TAPE_SIG) - 1)
#define OBDR_TAPE_INQ_SIZE (OBDR_SIG_OFFSET + OBDR_SIG_LEN)

	unsigned char *inq_buff;
	unsigned char *obdr_sig;

	inq_buff = kzalloc(OBDR_TAPE_INQ_SIZE, GFP_KERNEL);
	if (!inq_buff)
		goto bail_out;

	/* Do an inquiry to the device to see what it is. */
	if (hpsa_scsi_do_inquiry(h, scsi3addr, 0, inq_buff,
		(unsigned char) OBDR_TAPE_INQ_SIZE) != 0) {
		/* Inquiry failed (msg printed already) */
		dev_err(&h->pdev->dev,
			"hpsa_update_device_info: inquiry failed\n");
		goto bail_out;
	}

	this_device->devtype = (inq_buff[0] & 0x1f);
	memcpy(this_device->scsi3addr, scsi3addr, 8);
	memcpy(this_device->vendor, &inq_buff[8],
		sizeof(this_device->vendor));
	memcpy(this_device->model, &inq_buff[16],
		sizeof(this_device->model));
	memset(this_device->device_id, 0,
		sizeof(this_device->device_id));
	hpsa_get_device_id(h, scsi3addr, this_device->device_id,
		sizeof(this_device->device_id));

	if (this_device->devtype == TYPE_DISK &&
		is_logical_dev_addr_mode(scsi3addr))
		hpsa_get_raid_level(h, scsi3addr, &this_device->raid_level);
	else
		this_device->raid_level = RAID_UNKNOWN;

	if (is_OBDR_device) {
		/* See if this is a One-Button-Disaster-Recovery device
		 * by looking for "$DR-10" at offset 43 in inquiry data.
		 */
		obdr_sig = &inq_buff[OBDR_SIG_OFFSET];
		*is_OBDR_device = (this_device->devtype == TYPE_ROM &&
					strncmp(obdr_sig, OBDR_TAPE_SIG,
						OBDR_SIG_LEN) == 0);
	}

	kfree(inq_buff);
	return 0;

bail_out:
	kfree(inq_buff);
	return 1;
}