#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dds_inconsistent; int /*<<< orphan*/  dds_is_snapshot; int /*<<< orphan*/  dds_num_clones; } ;
struct TYPE_4__ {TYPE_2__ zc_objset_stats; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  TYPE_2__ dmu_objset_stats_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyDict_SetItemString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fakepropval (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_ds_props(zfs_cmd_t *zc, PyObject *nvl)
{
	dmu_objset_stats_t *s = &zc->zc_objset_stats;
	PyDict_SetItemString(nvl, "numclones",
	    fakepropval(s->dds_num_clones));
	PyDict_SetItemString(nvl, "issnap",
	    fakepropval(s->dds_is_snapshot));
	PyDict_SetItemString(nvl, "inconsistent",
	    fakepropval(s->dds_inconsistent));
}