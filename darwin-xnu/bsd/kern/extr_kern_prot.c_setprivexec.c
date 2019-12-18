#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct setprivexec_args {scalar_t__ flag; } ;
typedef  TYPE_1__* proc_t ;
typedef  int int32_t ;
struct TYPE_3__ {int p_debugger; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  value32 ; 

int
setprivexec(proc_t p, struct setprivexec_args *uap, int32_t *retval)
{
	AUDIT_ARG(value32, uap->flag);
	*retval = p->p_debugger;
	p->p_debugger = (uap->flag != 0);
	return(0);
}