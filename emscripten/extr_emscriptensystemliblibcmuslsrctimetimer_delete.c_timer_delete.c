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
typedef  scalar_t__ timer_t ;
typedef  TYPE_1__* pthread_t ;
struct TYPE_2__ {int timer_id; } ;

/* Variables and functions */
 int INT_MIN ; 
 int /*<<< orphan*/  SYS_timer_delete ; 
 int __syscall (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __wake (int*,int,int) ; 
 int /*<<< orphan*/  a_store (int*,int) ; 

int timer_delete(timer_t t)
{
	if ((intptr_t)t < 0) {
		pthread_t td = (void *)((uintptr_t)t << 1);
		a_store(&td->timer_id, td->timer_id | INT_MIN);
		__wake(&td->timer_id, 1, 1);
		return 0;
	}
	return __syscall(SYS_timer_delete, t);
}