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
struct TYPE_2__ {scalar_t__ ptr; } ;
struct pf_src_node {int af; int /*<<< orphan*/  addr; TYPE_1__ rule; } ;

/* Variables and functions */
 int pf_addr_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static __inline int
pf_src_compare(struct pf_src_node *a, struct pf_src_node *b)
{
	int	diff;

	if (a->rule.ptr > b->rule.ptr)
		return (1);
	if (a->rule.ptr < b->rule.ptr)
		return (-1);
	if ((diff = a->af - b->af) != 0)
		return (diff);
	if ((diff = pf_addr_compare(&a->addr, &b->addr, a->af)) != 0)
		return (diff);
	return (0);
}