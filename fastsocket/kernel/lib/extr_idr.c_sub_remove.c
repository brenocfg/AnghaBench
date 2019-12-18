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
struct idr_layer {int /*<<< orphan*/  count; struct idr_layer** ary; int /*<<< orphan*/  bitmap; } ;
struct idr {scalar_t__ layers; struct idr_layer* top; } ;

/* Variables and functions */
 scalar_t__ IDR_BITS ; 
 int IDR_MASK ; 
 int MAX_LEVEL ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_layer (struct idr_layer*) ; 
 int /*<<< orphan*/  idr_remove_warning (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct idr_layer*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sub_remove(struct idr *idp, int shift, int id)
{
	struct idr_layer *p = idp->top;
	struct idr_layer **pa[MAX_LEVEL];
	struct idr_layer ***paa = &pa[0];
	struct idr_layer *to_free;
	int n;

	*paa = NULL;
	*++paa = &idp->top;

	while ((shift > 0) && p) {
		n = (id >> shift) & IDR_MASK;
		__clear_bit(n, &p->bitmap);
		*++paa = &p->ary[n];
		p = p->ary[n];
		shift -= IDR_BITS;
	}
	n = id & IDR_MASK;
	if (likely(p != NULL && test_bit(n, &p->bitmap))){
		__clear_bit(n, &p->bitmap);
		rcu_assign_pointer(p->ary[n], NULL);
		to_free = NULL;
		while(*paa && ! --((**paa)->count)){
			if (to_free)
				free_layer(to_free);
			to_free = **paa;
			**paa-- = NULL;
		}
		if (!*paa)
			idp->layers = 0;
		if (to_free)
			free_layer(to_free);
	} else
		idr_remove_warning(id);
}