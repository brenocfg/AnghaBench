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
struct killpg1_filtargs {TYPE_1__* curproc; scalar_t__ posix; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_3__ {int p_pid; int p_flag; } ;

/* Variables and functions */
 int P_SYSTEM ; 

__attribute__((used)) static int
killpg1_allfilt(proc_t p, void * arg)
{
	struct killpg1_filtargs * kfargp = (struct killpg1_filtargs *)arg;

	/*
	 * Don't signal initproc, a system process, or the current process if POSIX
	 * isn't specified.
	 */
	return (p->p_pid > 1 && !(p->p_flag & P_SYSTEM) &&
			(kfargp->posix ? true : p != kfargp->curproc));
}