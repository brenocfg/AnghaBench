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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/ * mos_refd_objs ; 
 int /*<<< orphan*/  range_tree_add (int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static void
mos_obj_refd(uint64_t obj)
{
	if (obj != 0 && mos_refd_objs != NULL)
		range_tree_add(mos_refd_objs, obj, 1);
}