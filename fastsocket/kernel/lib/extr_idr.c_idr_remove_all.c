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
struct idr_layer {struct idr_layer** ary; } ;
struct idr {int layers; struct idr_layer* top; } ;

/* Variables and functions */
 int IDR_BITS ; 
 int IDR_MASK ; 
 int MAX_LEVEL ; 
 int fls (int) ; 
 int /*<<< orphan*/  free_layer (struct idr_layer*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct idr_layer*,int /*<<< orphan*/ *) ; 

void idr_remove_all(struct idr *idp)
{
	int n, id, max;
	struct idr_layer *p;
	struct idr_layer *pa[MAX_LEVEL];
	struct idr_layer **paa = &pa[0];

	n = idp->layers * IDR_BITS;
	p = idp->top;
	rcu_assign_pointer(idp->top, NULL);
	max = 1 << n;

	id = 0;
	while (id < max) {
		while (n > IDR_BITS && p) {
			n -= IDR_BITS;
			*paa++ = p;
			p = p->ary[(id >> n) & IDR_MASK];
		}

		id += 1 << n;
		while (n < fls(id)) {
			if (p)
				free_layer(p);
			n += IDR_BITS;
			p = *--paa;
		}
	}
	idp->layers = 0;
}