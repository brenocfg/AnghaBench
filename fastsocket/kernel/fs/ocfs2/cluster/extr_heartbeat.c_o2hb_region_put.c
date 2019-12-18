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
struct o2hb_region {int /*<<< orphan*/  hr_item; } ;

/* Variables and functions */
 struct o2hb_region* o2hb_find_region (char const*) ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  o2nm_undepend_item (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  o2nm_undepend_this_node () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2hb_region_put(const char *region_uuid)
{
	struct o2hb_region *reg;

	spin_lock(&o2hb_live_lock);

	reg = o2hb_find_region(region_uuid);

	spin_unlock(&o2hb_live_lock);

	if (reg) {
		o2nm_undepend_item(&reg->hr_item);
		o2nm_undepend_this_node();
	}
}