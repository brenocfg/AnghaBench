#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* var; } ;
typedef  TYPE_1__ VARENT ;
struct TYPE_8__ {int off; } ;
typedef  TYPE_2__ VAR ;
struct TYPE_9__ {scalar_t__ ki_p; } ;
typedef  TYPE_3__ KINFO ;

/* Variables and functions */
 char* printval (char*,TYPE_2__*) ; 

char *
kvar(KINFO *k, VARENT *ve)
{
	VAR *v;

	v = ve->var;
	return (printval((char *)((char *)k->ki_p + v->off), v));
}