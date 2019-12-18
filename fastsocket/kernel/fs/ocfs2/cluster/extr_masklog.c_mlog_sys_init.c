#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kset {int dummy; } ;
struct TYPE_9__ {struct kset* kset; } ;
struct TYPE_8__ {scalar_t__ mode; } ;
struct TYPE_7__ {TYPE_3__ attr; } ;
struct TYPE_6__ {TYPE_5__ kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_set_name (TYPE_5__*,char*) ; 
 int kset_register (TYPE_1__*) ; 
 TYPE_3__** mlog_attr_ptrs ; 
 TYPE_2__* mlog_attrs ; 
 TYPE_1__ mlog_kset ; 

int mlog_sys_init(struct kset *o2cb_kset)
{
	int i = 0;

	while (mlog_attrs[i].attr.mode) {
		mlog_attr_ptrs[i] = &mlog_attrs[i].attr;
		i++;
	}
	mlog_attr_ptrs[i] = NULL;

	kobject_set_name(&mlog_kset.kobj, "logmask");
	mlog_kset.kobj.kset = o2cb_kset;
	return kset_register(&mlog_kset);
}