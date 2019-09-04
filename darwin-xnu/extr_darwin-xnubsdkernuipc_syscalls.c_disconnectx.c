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
struct disconnectx_args {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pthread_testcancel (int) ; 
 int disconnectx_nocancel (struct proc*,struct disconnectx_args*,int*) ; 

int
disconnectx(struct proc *p, struct disconnectx_args *uap, int *retval)
{
	/*
	 * Due to similiarity with a POSIX interface, define as
	 * an unofficial cancellation point.
	 */
	__pthread_testcancel(1);
	return (disconnectx_nocancel(p, uap, retval));
}