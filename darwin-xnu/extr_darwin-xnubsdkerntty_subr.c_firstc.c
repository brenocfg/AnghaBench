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
struct clist {scalar_t__ c_cc; int* c_cf; int* c_cs; scalar_t__* c_cq; } ;

/* Variables and functions */
 int TTY_QUOTE ; 
 scalar_t__ cc ; 

u_char *
firstc(struct clist *clp, int *c)
{
	u_char *cp;

	cc = clp->c_cc;
	if (cc == 0)
		return NULL;
	cp = clp->c_cf;
	*c = *cp & 0xff;
	if(clp->c_cq) {
#ifdef QBITS
		if (isset(clp->c_cq, cp - clp->c_cs))
			*c |= TTY_QUOTE;
#else
		if (*(cp - clp->c_cs + clp->c_cq))
			*c |= TTY_QUOTE;
#endif
	}
	return clp->c_cf;
}