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
struct proc {int dummy; } ;
struct kdebug_trace_args {int /*<<< orphan*/  arg4; int /*<<< orphan*/  arg3; int /*<<< orphan*/  arg2; int /*<<< orphan*/  arg1; int /*<<< orphan*/  code; } ;
struct kdebug_trace64_args {int /*<<< orphan*/  arg4; int /*<<< orphan*/  arg3; int /*<<< orphan*/  arg2; int /*<<< orphan*/  arg1; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int kdebug_trace64 (struct proc*,struct kdebug_trace64_args*,int /*<<< orphan*/ *) ; 

int
kdebug_trace(struct proc *p, struct kdebug_trace_args *uap, int32_t *retval)
{
	struct kdebug_trace64_args uap64;

	uap64.code = uap->code;
	uap64.arg1 = uap->arg1;
	uap64.arg2 = uap->arg2;
	uap64.arg3 = uap->arg3;
	uap64.arg4 = uap->arg4;

	return kdebug_trace64(p, &uap64, retval);
}