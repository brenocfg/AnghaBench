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
struct mapped_device {int dummy; } ;
struct gendisk {int /*<<< orphan*/  disk_name; } ;
struct dm_table {int integrity_supported; int /*<<< orphan*/  md; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_integrity_compare (struct gendisk*,struct gendisk*) ; 
 scalar_t__ blk_integrity_is_initialized (struct gendisk*) ; 
 int blk_integrity_register (struct gendisk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 struct gendisk* dm_disk (struct mapped_device*) ; 
 struct gendisk* dm_table_get_integrity_disk (struct dm_table*,int) ; 

__attribute__((used)) static int dm_table_prealloc_integrity(struct dm_table *t, struct mapped_device *md)
{
	struct gendisk *template_disk = NULL;

	template_disk = dm_table_get_integrity_disk(t, false);
	if (!template_disk)
		return 0;

	if (!blk_integrity_is_initialized(dm_disk(md))) {
		t->integrity_supported = 1;
		return blk_integrity_register(dm_disk(md), NULL);
	}

	/*
	 * If DM device already has an initalized integrity
	 * profile the new profile should not conflict.
	 */
	if (blk_integrity_is_initialized(template_disk) &&
	    blk_integrity_compare(dm_disk(md), template_disk) < 0) {
		DMWARN("%s: conflict with existing integrity profile: "
		       "%s profile mismatch",
		       dm_device_name(t->md),
		       template_disk->disk_name);
		return 1;
	}

	/* Preserve existing initialized integrity profile */
	t->integrity_supported = 1;
	return 0;
}