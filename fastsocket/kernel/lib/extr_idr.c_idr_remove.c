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
struct idr_layer {int count; int bitmap; struct idr_layer** ary; } ;
struct idr {int layers; scalar_t__ id_free_cnt; struct idr_layer* top; } ;

/* Variables and functions */
 int IDR_BITS ; 
 scalar_t__ IDR_FREE_MAX ; 
 int MAX_ID_MASK ; 
 int /*<<< orphan*/  free_layer (struct idr_layer*) ; 
 struct idr_layer* get_from_free_list (struct idr*) ; 
 int /*<<< orphan*/  idr_layer_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct idr_layer*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct idr_layer*,struct idr_layer*) ; 
 int /*<<< orphan*/  sub_remove (struct idr*,int,int) ; 

void idr_remove(struct idr *idp, int id)
{
	struct idr_layer *p;
	struct idr_layer *to_free;

	/* Mask off upper bits we don't use for the search. */
	id &= MAX_ID_MASK;

	sub_remove(idp, (idp->layers - 1) * IDR_BITS, id);
	if (idp->top && idp->top->count == 1 && (idp->layers > 1) &&
	    idp->top->ary[0]) {
		/*
		 * Single child at leftmost slot: we can shrink the tree.
		 * This level is not needed anymore since when layers are
		 * inserted, they are inserted at the top of the existing
		 * tree.
		 */
		to_free = idp->top;
		p = idp->top->ary[0];
		rcu_assign_pointer(idp->top, p);
		--idp->layers;
		to_free->bitmap = to_free->count = 0;
		free_layer(to_free);
	}
	while (idp->id_free_cnt >= IDR_FREE_MAX) {
		p = get_from_free_list(idp);
		/*
		 * Note: we don't call the rcu callback here, since the only
		 * layers that fall into the freelist are those that have been
		 * preallocated.
		 */
		kmem_cache_free(idr_layer_cache, p);
	}
	return;
}