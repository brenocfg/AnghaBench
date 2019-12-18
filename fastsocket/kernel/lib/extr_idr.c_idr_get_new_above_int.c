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
struct idr_layer {int /*<<< orphan*/  count; int /*<<< orphan*/ * ary; } ;
struct idr {int dummy; } ;

/* Variables and functions */
 int IDR_MASK ; 
 int MAX_LEVEL ; 
 int idr_get_empty_slot (struct idr*,int,struct idr_layer**) ; 
 int /*<<< orphan*/  idr_mark_full (struct idr_layer**,int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct idr_layer*) ; 

__attribute__((used)) static int idr_get_new_above_int(struct idr *idp, void *ptr, int starting_id)
{
	struct idr_layer *pa[MAX_LEVEL];
	int id;

	id = idr_get_empty_slot(idp, starting_id, pa);
	if (id >= 0) {
		/*
		 * Successfully found an empty slot.  Install the user
		 * pointer and mark the slot full.
		 */
		rcu_assign_pointer(pa[0]->ary[id & IDR_MASK],
				(struct idr_layer *)ptr);
		pa[0]->count++;
		idr_mark_full(pa, id);
	}

	return id;
}