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
typedef  int u_char ;
struct clist {scalar_t__ c_cc; int* c_cl; int* c_cs; int* c_ce; int* c_cf; scalar_t__* c_cq; } ;

/* Variables and functions */
 unsigned int TTY_QUOTE ; 

int
unputc(struct clist *clp)
{
	unsigned int c = -1;

	if (clp->c_cc == 0)
		goto out;

	if (clp->c_cl == clp->c_cs)
		clp->c_cl = clp->c_ce - 1;
	else
		--clp->c_cl;
	clp->c_cc--;

	c = *clp->c_cl & 0xff;
	if (clp->c_cq) {
#ifdef QBITS
		if (isset(clp->c_cq, clp->c_cl - clp->c_cs))
			c |= TTY_QUOTE;
#else
		if (*(clp->c_cf - clp->c_cs + clp->c_cq))
			c |= TTY_QUOTE;
#endif
	}
	if (clp->c_cc == 0)
		clp->c_cf = clp->c_cl = (u_char *)0;
out:
	return c;
}