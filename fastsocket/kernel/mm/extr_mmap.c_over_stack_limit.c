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
struct TYPE_4__ {unsigned long rlim_cur; } ;

/* Variables and functions */
 unsigned long EXEC_STACK_BIAS ; 
 size_t RLIMIT_STACK ; 
 TYPE_3__* current ; 

__attribute__((used)) static int over_stack_limit(unsigned long sz)
{
	if (sz < EXEC_STACK_BIAS)
		return 0;
	return (sz - EXEC_STACK_BIAS) >
			current->signal->rlim[RLIMIT_STACK].rlim_cur;
}