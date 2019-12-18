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
struct scsi_cd {int /*<<< orphan*/  cdi; } ;
struct gendisk {int dummy; } ;

/* Variables and functions */
 int cdrom_media_changed (int /*<<< orphan*/ *) ; 
 struct scsi_cd* scsi_cd (struct gendisk*) ; 

__attribute__((used)) static int sr_block_media_changed(struct gendisk *disk)
{
	struct scsi_cd *cd = scsi_cd(disk);
	return cdrom_media_changed(&cd->cdi);
}