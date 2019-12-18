#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* signal; } ;
struct TYPE_5__ {TYPE_1__* rlim; } ;
struct TYPE_4__ {scalar_t__ rlim_cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_IPC_LOCK ; 
 size_t RLIMIT_MEMLOCK ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 TYPE_3__* current ; 

int can_do_mlock(void)
{
	if (capable(CAP_IPC_LOCK))
		return 1;
	if (current->signal->rlim[RLIMIT_MEMLOCK].rlim_cur != 0)
		return 1;
	return 0;
}