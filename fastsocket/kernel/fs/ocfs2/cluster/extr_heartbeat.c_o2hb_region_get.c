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
 int ENOENT ; 
 struct o2hb_region* o2hb_find_region (char const*) ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int o2nm_depend_item (int /*<<< orphan*/ *) ; 
 int o2nm_depend_this_node () ; 
 int /*<<< orphan*/  o2nm_undepend_this_node () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int o2hb_region_get(const char *region_uuid)
{
	int ret = 0;
	struct o2hb_region *reg;

	spin_lock(&o2hb_live_lock);

	reg = o2hb_find_region(region_uuid);
	if (!reg)
		ret = -ENOENT;
	spin_unlock(&o2hb_live_lock);

	if (ret)
		goto out;

	ret = o2nm_depend_this_node();
	if (ret)
		goto out;

	ret = o2nm_depend_item(&reg->hr_item);
	if (ret)
		o2nm_undepend_this_node();

out:
	return ret;
}