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
typedef  int u8 ;
struct scsi_device {int /*<<< orphan*/  sdev_gendev; } ;
typedef  enum raid_level { ____Placeholder_raid_level } raid_level ;

/* Variables and functions */
#define  MPI2_RAID_VOL_TYPE_RAID0 131 
#define  MPI2_RAID_VOL_TYPE_RAID1 130 
#define  MPI2_RAID_VOL_TYPE_RAID10 129 
#define  MPI2_RAID_VOL_TYPE_RAID1E 128 
 int RAID_LEVEL_0 ; 
 int RAID_LEVEL_1 ; 
 int RAID_LEVEL_10 ; 
 int RAID_LEVEL_1E ; 
 int RAID_LEVEL_UNKNOWN ; 
 int /*<<< orphan*/  mpt2sas_raid_template ; 
 int /*<<< orphan*/  raid_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
_scsih_set_level(struct scsi_device *sdev, u8 volume_type)
{
	enum raid_level level = RAID_LEVEL_UNKNOWN;

	switch (volume_type) {
	case MPI2_RAID_VOL_TYPE_RAID0:
		level = RAID_LEVEL_0;
		break;
	case MPI2_RAID_VOL_TYPE_RAID10:
		level = RAID_LEVEL_10;
		break;
	case MPI2_RAID_VOL_TYPE_RAID1E:
		level = RAID_LEVEL_1E;
		break;
	case MPI2_RAID_VOL_TYPE_RAID1:
		level = RAID_LEVEL_1;
		break;
	}

	raid_set_level(mpt2sas_raid_template, &sdev->sdev_gendev, level);
}