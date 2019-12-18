#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARENT ;
struct TYPE_8__ {TYPE_2__* ki_p; } ;
struct TYPE_6__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_7__ {int ki_runtime; TYPE_1__ ki_childtime; } ;
typedef  TYPE_3__ KINFO ;

/* Variables and functions */
 char* printtime (TYPE_3__*,int /*<<< orphan*/ *,long,long) ; 
 scalar_t__ sumrusage ; 

char *
cputime(KINFO *k, VARENT *ve)
{
	long secs, psecs;

	/*
	 * This counts time spent handling interrupts.  We could
	 * fix this, but it is not 100% trivial (and interrupt
	 * time fractions only work on the sparc anyway).	XXX
	 */
	secs = k->ki_p->ki_runtime / 1000000;
	psecs = k->ki_p->ki_runtime % 1000000;
	if (sumrusage) {
		secs += k->ki_p->ki_childtime.tv_sec;
		psecs += k->ki_p->ki_childtime.tv_usec;
	}
	return (printtime(k, ve, secs, psecs));
}