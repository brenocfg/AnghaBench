#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* ki_p; } ;
struct TYPE_4__ {int ki_flag; scalar_t__ ki_rssize; } ;
typedef  TYPE_2__ KINFO ;

/* Variables and functions */
 int P_INMEM ; 
 int donlist () ; 
 double mempages ; 
 int /*<<< orphan*/  nlistread ; 

__attribute__((used)) static double
getpmem(KINFO *k)
{
	static int failure;
	double fracmem;

	if (!nlistread)
		failure = donlist();
	if (failure)
		return (0.0);

	if ((k->ki_p->ki_flag & P_INMEM) == 0)
		return (0.0);
	/* XXX want pmap ptpages, segtab, etc. (per architecture) */
	/* XXX don't have info about shared */
	fracmem = ((double)k->ki_p->ki_rssize) / mempages;
	return (100.0 * fracmem);
}