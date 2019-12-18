#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dd_object; } ;
typedef  TYPE_1__ dsl_dir_t ;
struct TYPE_6__ {int /*<<< orphan*/  dd_clones; int /*<<< orphan*/  dd_props_zapobj; int /*<<< orphan*/  dd_deleg_zapobj; int /*<<< orphan*/  dd_child_dir_zapobj; } ;

/* Variables and functions */
 TYPE_2__* dsl_dir_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  mos_obj_refd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
count_dir_mos_objects(dsl_dir_t *dd)
{
	mos_obj_refd(dd->dd_object);
	mos_obj_refd(dsl_dir_phys(dd)->dd_child_dir_zapobj);
	mos_obj_refd(dsl_dir_phys(dd)->dd_deleg_zapobj);
	mos_obj_refd(dsl_dir_phys(dd)->dd_props_zapobj);
	mos_obj_refd(dsl_dir_phys(dd)->dd_clones);
}