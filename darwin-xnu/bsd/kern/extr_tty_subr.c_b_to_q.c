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
struct clist {scalar_t__ c_cc; scalar_t__ c_cs; scalar_t__ c_cf; scalar_t__ c_cl; scalar_t__ c_cn; int c_ce; int c_cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  bzero (int,int) ; 
 scalar_t__ clalloc (struct clist*,int,int) ; 
 int /*<<< orphan*/  clrbits (int,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int
b_to_q(const u_char *cp, int count, struct clist *clp)
{
	int cc;
	const u_char *p = cp;

	if (count <= 0)
		return 0;


	if (clp->c_cc == 0) {
		if (!clp->c_cs) {
#if DIAGNOSTIC
			printf("b_to_q: required clalloc\n");
#endif
			if(clalloc(clp, 1024, 1))
				goto out;
		}
		clp->c_cf = clp->c_cl = clp->c_cs;
	}

	if (clp->c_cc == clp->c_cn)
		goto out;

	/* optimize this while loop */
	while (count > 0 && clp->c_cc < clp->c_cn) {
		cc = clp->c_ce - clp->c_cl;
		if (clp->c_cf > clp->c_cl)
			cc = clp->c_cf - clp->c_cl;
		if (cc > count)
			cc = count;
		bcopy(p, clp->c_cl, cc);
		if (clp->c_cq) {
#ifdef QBITS
			clrbits(clp->c_cq, clp->c_cl - clp->c_cs, cc);
#else
			bzero(clp->c_cl - clp->c_cs + clp->c_cq, cc);
#endif
		}
		p += cc;
		count -= cc;
		clp->c_cc += cc;
		clp->c_cl += cc;
		if (clp->c_cl == clp->c_ce)
			clp->c_cl = clp->c_cs;
	}
out:
	return count;
}