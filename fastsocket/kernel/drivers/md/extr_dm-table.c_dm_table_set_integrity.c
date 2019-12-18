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
struct gendisk {int dummy; } ;
struct dm_table {int /*<<< orphan*/  md; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMWARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_get_integrity (struct gendisk*) ; 
 scalar_t__ blk_integrity_is_initialized (struct gendisk*) ; 
 int /*<<< orphan*/  blk_integrity_register (struct gendisk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_device_name (int /*<<< orphan*/ ) ; 
 struct gendisk* dm_disk (int /*<<< orphan*/ ) ; 
 struct gendisk* dm_table_get_integrity_disk (struct dm_table*,int) ; 

__attribute__((used)) static void dm_table_set_integrity(struct dm_table *t)
{
	struct gendisk *template_disk = NULL;

	if (!blk_get_integrity(dm_disk(t->md)))
		return;

	template_disk = dm_table_get_integrity_disk(t, true);
	if (template_disk)
		blk_integrity_register(dm_disk(t->md),
				       blk_get_integrity(template_disk));
	else if (blk_integrity_is_initialized(dm_disk(t->md)))
		DMWARN("%s: device no longer has a valid integrity profile",
		       dm_device_name(t->md));
	else
		DMWARN("%s: unable to establish an integrity profile",
		       dm_device_name(t->md));
}