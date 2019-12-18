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
typedef  int /*<<< orphan*/  fmode_t ;

/* Variables and functions */
 int /*<<< orphan*/  cdrom_release (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct scsi_cd* scsi_cd (struct gendisk*) ; 
 int /*<<< orphan*/  scsi_cd_put (struct scsi_cd*) ; 

__attribute__((used)) static int sr_block_release(struct gendisk *disk, fmode_t mode)
{
	struct scsi_cd *cd = scsi_cd(disk);
	cdrom_release(&cd->cdi, mode);
	scsi_cd_put(cd);
	return 0;
}