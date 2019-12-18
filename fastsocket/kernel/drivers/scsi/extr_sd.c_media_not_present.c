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
struct scsi_sense_hdr {scalar_t__ sense_key; int asc; } ;
struct scsi_disk {int dummy; } ;

/* Variables and functions */
 scalar_t__ NOT_READY ; 
 scalar_t__ UNIT_ATTENTION ; 
 int /*<<< orphan*/  scsi_sense_valid (struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  set_media_not_present (struct scsi_disk*) ; 

__attribute__((used)) static int media_not_present(struct scsi_disk *sdkp,
			     struct scsi_sense_hdr *sshdr)
{

	if (!scsi_sense_valid(sshdr))
		return 0;
	/* not invoked for commands that could return deferred errors */
	if (sshdr->sense_key != NOT_READY &&
	    sshdr->sense_key != UNIT_ATTENTION)
		return 0;
	if (sshdr->asc != 0x3A) /* medium not present */
		return 0;

	set_media_not_present(sdkp);
	return 1;
}