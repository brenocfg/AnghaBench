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
struct scsi_sense_hdr {scalar_t__ sense_key; } ;
struct scsi_device {int changed; scalar_t__ removable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NOT_READY ; 
 char TEST_UNIT_READY ; 
 scalar_t__ UNIT_ATTENTION ; 
 int /*<<< orphan*/  kfree (struct scsi_sense_hdr*) ; 
 struct scsi_sense_hdr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int scsi_execute_req (struct scsi_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct scsi_sense_hdr*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_sense_valid (struct scsi_sense_hdr*) ; 

int
scsi_test_unit_ready(struct scsi_device *sdev, int timeout, int retries,
		     struct scsi_sense_hdr *sshdr_external)
{
	char cmd[] = {
		TEST_UNIT_READY, 0, 0, 0, 0, 0,
	};
	struct scsi_sense_hdr *sshdr;
	int result;

	if (!sshdr_external)
		sshdr = kzalloc(sizeof(*sshdr), GFP_KERNEL);
	else
		sshdr = sshdr_external;

	/* try to eat the UNIT_ATTENTION if there are enough retries */
	do {
		result = scsi_execute_req(sdev, cmd, DMA_NONE, NULL, 0, sshdr,
					  timeout, retries, NULL);
		if (sdev->removable && scsi_sense_valid(sshdr) &&
		    sshdr->sense_key == UNIT_ATTENTION)
			sdev->changed = 1;
	} while (scsi_sense_valid(sshdr) &&
		 sshdr->sense_key == UNIT_ATTENTION && --retries);

	if (!sshdr)
		/* could not allocate sense buffer, so can't process it */
		return result;

	if (sdev->removable && scsi_sense_valid(sshdr) &&
	    (sshdr->sense_key == UNIT_ATTENTION ||
	     sshdr->sense_key == NOT_READY)) {
		sdev->changed = 1;
		result = 0;
	}
	if (!sshdr_external)
		kfree(sshdr);
	return result;
}