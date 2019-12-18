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
typedef  scalar_t__ u64 ;
struct hfsc_class {scalar_t__ cl_cfmin; scalar_t__ level; scalar_t__ cl_vt; TYPE_1__* cl_parent; } ;
struct TYPE_2__ {scalar_t__ cl_cvtmin; } ;

/* Variables and functions */
 struct hfsc_class* vttree_firstfit (struct hfsc_class*,scalar_t__) ; 

__attribute__((used)) static struct hfsc_class *
vttree_get_minvt(struct hfsc_class *cl, u64 cur_time)
{
	/* if root-class's cfmin is bigger than cur_time nothing to do */
	if (cl->cl_cfmin > cur_time)
		return NULL;

	while (cl->level > 0) {
		cl = vttree_firstfit(cl, cur_time);
		if (cl == NULL)
			return NULL;
		/*
		 * update parent's cl_cvtmin.
		 */
		if (cl->cl_parent->cl_cvtmin < cl->cl_vt)
			cl->cl_parent->cl_cvtmin = cl->cl_vt;
	}
	return cl;
}