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
typedef  int /*<<< orphan*/  user_ssize_t ;
struct read_nocancel_args {int dummy; } ;
struct read_args {int dummy; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pthread_testcancel (int) ; 
 int read_nocancel (struct proc*,struct read_nocancel_args*,int /*<<< orphan*/ *) ; 

int
read(struct proc *p, struct read_args *uap, user_ssize_t *retval)
{
	__pthread_testcancel(1);
	return(read_nocancel(p, (struct read_nocancel_args *)uap, retval));
}