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
struct sem_wait_nocancel_args {int dummy; } ;
struct sem_wait_args {int dummy; } ;
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  __pthread_testcancel (int) ; 
 int sem_wait_nocancel (int /*<<< orphan*/ ,struct sem_wait_nocancel_args*,int /*<<< orphan*/ *) ; 

int
sem_wait(proc_t p, struct sem_wait_args *uap, int32_t *retval)
{
	__pthread_testcancel(1);
	return(sem_wait_nocancel(p, (struct sem_wait_nocancel_args *)uap, retval));
}