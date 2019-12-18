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
typedef  int /*<<< orphan*/  u_char ;
struct clist {int /*<<< orphan*/ * c_cq; int /*<<< orphan*/ * c_cs; int /*<<< orphan*/  c_cn; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_ZONE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TTYS ; 
 int /*<<< orphan*/  QMEM (int /*<<< orphan*/ ) ; 

void
clfree(struct clist *clp)
{
	if(clp->c_cs)
		FREE_ZONE(clp->c_cs, clp->c_cn, M_TTYS);
	if(clp->c_cq)
		FREE_ZONE(clp->c_cq, QMEM(clp->c_cn), M_TTYS);
	clp->c_cs = clp->c_cq = (u_char *)0;
}