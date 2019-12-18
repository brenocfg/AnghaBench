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
struct list_head {int dummy; } ;

/* Variables and functions */
 int parse_events__modifier_event (struct list_head*,char*,int) ; 

int parse_events__modifier_group(struct list_head *list,
				 char *event_mod)
{
	return parse_events__modifier_event(list, event_mod, true);
}