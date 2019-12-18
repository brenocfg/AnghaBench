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
typedef  size_t u8 ;
struct ath_gen_timer_table {struct ath_gen_timer** timers; } ;
struct ath_hw {struct ath_gen_timer_table hw_gen_timers; } ;
struct ath_gen_timer {size_t index; void (* trigger ) (void*) ;void (* overflow ) (void*) ;void* arg; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ath_gen_timer* kzalloc (int,int /*<<< orphan*/ ) ; 

struct ath_gen_timer *ath_gen_timer_alloc(struct ath_hw *ah,
					  void (*trigger)(void *),
					  void (*overflow)(void *),
					  void *arg,
					  u8 timer_index)
{
	struct ath_gen_timer_table *timer_table = &ah->hw_gen_timers;
	struct ath_gen_timer *timer;

	timer = kzalloc(sizeof(struct ath_gen_timer), GFP_KERNEL);
	if (timer == NULL)
		return NULL;

	/* allocate a hardware generic timer slot */
	timer_table->timers[timer_index] = timer;
	timer->index = timer_index;
	timer->trigger = trigger;
	timer->overflow = overflow;
	timer->arg = arg;

	return timer;
}