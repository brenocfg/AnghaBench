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
struct vtimer_list {int dummy; } ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int __mod_vtimer (struct vtimer_list*,int /*<<< orphan*/ ,int) ; 

int mod_virt_timer_periodic(struct vtimer_list *timer, __u64 expires)
{
	return __mod_vtimer(timer, expires, 1);
}