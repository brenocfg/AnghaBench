#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARENT ;
struct TYPE_12__ {TYPE_4__* ki_p; } ;
struct TYPE_10__ {scalar_t__ tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_8__ {long tv_sec; long tv_usec; } ;
struct TYPE_9__ {TYPE_1__ ru_stime; } ;
struct TYPE_11__ {TYPE_3__ ki_childstime; TYPE_2__ ki_rusage; } ;
typedef  TYPE_5__ KINFO ;

/* Variables and functions */
 char* printtime (TYPE_5__*,int /*<<< orphan*/ *,long,long) ; 
 scalar_t__ sumrusage ; 

char *
systime(KINFO *k, VARENT *ve)
{
	long secs, psecs;

	secs = k->ki_p->ki_rusage.ru_stime.tv_sec;
	psecs = k->ki_p->ki_rusage.ru_stime.tv_usec;
	if (sumrusage) {
		secs += k->ki_p->ki_childstime.tv_sec;
		psecs += k->ki_p->ki_childstime.tv_usec;
	}
	return (printtime(k, ve, secs, psecs));
}