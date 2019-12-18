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
struct TYPE_4__ {int pl_prop; struct TYPE_4__* pl_next; int /*<<< orphan*/  pl_all; int /*<<< orphan*/  pl_fixed; int /*<<< orphan*/  pl_width; } ;
typedef  TYPE_1__ zprop_list_t ;
struct TYPE_5__ {TYPE_1__** last; int /*<<< orphan*/  type; int /*<<< orphan*/  hdl; } ;
typedef  TYPE_2__ expand_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int ZPROP_CONT ; 
 int ZPROP_INVAL ; 
 TYPE_1__* zfs_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zprop_width (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
zprop_expand_list_cb(int prop, void *cb)
{
	zprop_list_t *entry;
	expand_data_t *edp = cb;

	if ((entry = zfs_alloc(edp->hdl, sizeof (zprop_list_t))) == NULL)
		return (ZPROP_INVAL);

	entry->pl_prop = prop;
	entry->pl_width = zprop_width(prop, &entry->pl_fixed, edp->type);
	entry->pl_all = B_TRUE;

	*(edp->last) = entry;
	edp->last = &entry->pl_next;

	return (ZPROP_CONT);
}