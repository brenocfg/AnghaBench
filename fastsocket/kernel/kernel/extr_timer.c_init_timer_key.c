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
struct timer_list {int dummy; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __init_timer (struct timer_list*,char const*,struct lock_class_key*) ; 
 int /*<<< orphan*/  debug_init (struct timer_list*) ; 

void init_timer_key(struct timer_list *timer,
		    const char *name,
		    struct lock_class_key *key)
{
	debug_init(timer);
	__init_timer(timer, name, key);
}