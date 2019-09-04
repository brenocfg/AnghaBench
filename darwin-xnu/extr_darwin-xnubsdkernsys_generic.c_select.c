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
struct select_nocancel_args {int dummy; } ;
struct select_args {int dummy; } ;
struct proc {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pthread_testcancel (int) ; 
 int select_nocancel (struct proc*,struct select_nocancel_args*,int /*<<< orphan*/ *) ; 

int
select(struct proc *p, struct select_args *uap, int32_t *retval)
{
	__pthread_testcancel(1);
	return select_nocancel(p, (struct select_nocancel_args *)uap, retval);
}