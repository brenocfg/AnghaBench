#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* var; } ;
typedef  TYPE_2__ VARENT ;
struct TYPE_10__ {int off; } ;
typedef  TYPE_3__ VAR ;
struct TYPE_11__ {TYPE_1__* ki_p; int /*<<< orphan*/  ki_valid; } ;
struct TYPE_8__ {int /*<<< orphan*/  ki_rusage; } ;
typedef  TYPE_4__ KINFO ;

/* Variables and functions */
 char* printval (char*,TYPE_3__*) ; 

char *
rvar(KINFO *k, VARENT *ve)
{
	VAR *v;

	v = ve->var;
	if (!k->ki_valid)
		return (NULL);
	return (printval((char *)((char *)(&k->ki_p->ki_rusage) + v->off), v));
}