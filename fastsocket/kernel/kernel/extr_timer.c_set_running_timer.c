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
struct tvec_base {struct timer_list* running_timer; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void set_running_timer(struct tvec_base *base,
					struct timer_list *timer)
{
#ifdef CONFIG_SMP
	base->running_timer = timer;
#endif
}