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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_5__ {int dev_flags; scalar_t__ capacity64; int /*<<< orphan*/ * id; int /*<<< orphan*/  probed_capacity; } ;
typedef  TYPE_1__ ide_drive_t ;

/* Variables and functions */
 int IDE_DFLAG_LBA ; 
 int IDE_DFLAG_NOHPA ; 
 scalar_t__ ata_id_hpa_enabled (int /*<<< orphan*/ *) ; 
 int ata_id_lba48_enabled (int /*<<< orphan*/ *) ; 
 scalar_t__ ide_disk_hpa_get_native_capacity (TYPE_1__*,int) ; 
 scalar_t__ ide_disk_hpa_set_capacity (TYPE_1__*,scalar_t__,int) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 ide_disk_set_capacity(ide_drive_t *drive, u64 capacity)
{
	u64 set = min(capacity, drive->probed_capacity);
	u16 *id = drive->id;
	int lba48 = ata_id_lba48_enabled(id);

	if ((drive->dev_flags & IDE_DFLAG_LBA) == 0 ||
	    ata_id_hpa_enabled(id) == 0)
		goto out;

	/*
	 * according to the spec the SET MAX ADDRESS command shall be
	 * immediately preceded by a READ NATIVE MAX ADDRESS command
	 */
	capacity = ide_disk_hpa_get_native_capacity(drive, lba48);
	if (capacity == 0)
		goto out;

	set = ide_disk_hpa_set_capacity(drive, set, lba48);
	if (set) {
		/* needed for ->resume to disable HPA */
		drive->dev_flags |= IDE_DFLAG_NOHPA;
		return set;
	}
out:
	return drive->capacity64;
}