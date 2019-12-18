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
struct srp_event_struct {int dummy; } ;
struct event_pool {int size; struct srp_event_struct* events; } ;

/* Variables and functions */

__attribute__((used)) static int valid_event_struct(struct event_pool *pool,
				struct srp_event_struct *evt)
{
	int index = evt - pool->events;
	if (index < 0 || index >= pool->size)	/* outside of bounds */
		return 0;
	if (evt != pool->events + index)	/* unaligned */
		return 0;
	return 1;
}