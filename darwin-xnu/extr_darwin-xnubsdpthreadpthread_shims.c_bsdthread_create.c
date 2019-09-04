#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_addr_t ;
struct proc {int dummy; } ;
struct bsdthread_create_args {int /*<<< orphan*/  flags; int /*<<< orphan*/  pthread; int /*<<< orphan*/  stack; int /*<<< orphan*/  func_arg; int /*<<< orphan*/  func; } ;
struct TYPE_2__ {int (* bsdthread_create ) (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 TYPE_1__* pthread_functions ; 
 int stub1 (struct proc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
bsdthread_create(struct proc *p, struct bsdthread_create_args *uap, user_addr_t *retval)
{
	return pthread_functions->bsdthread_create(p, uap->func, uap->func_arg, uap->stack, uap->pthread, uap->flags, retval);
}