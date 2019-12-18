#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ classid; } ;
struct cbq_class {scalar_t__ defmap; struct cbq_class* split; TYPE_1__ common; struct cbq_class* tparent; } ;

/* Variables and functions */
 int /*<<< orphan*/  cbq_sync_defmap (struct cbq_class*) ; 

__attribute__((used)) static void cbq_change_defmap(struct cbq_class *cl, u32 splitid, u32 def, u32 mask)
{
	struct cbq_class *split = NULL;

	if (splitid == 0) {
		if ((split = cl->split) == NULL)
			return;
		splitid = split->common.classid;
	}

	if (split == NULL || split->common.classid != splitid) {
		for (split = cl->tparent; split; split = split->tparent)
			if (split->common.classid == splitid)
				break;
	}

	if (split == NULL)
		return;

	if (cl->split != split) {
		cl->defmap = 0;
		cbq_sync_defmap(cl);
		cl->split = split;
		cl->defmap = def&mask;
	} else
		cl->defmap = (cl->defmap&~mask)|(def&mask);

	cbq_sync_defmap(cl);
}