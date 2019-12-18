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
struct poch_group_info {scalar_t__ pg; } ;
struct channel_info {unsigned long group_count; int /*<<< orphan*/  group_size; struct poch_group_info* groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_pages (scalar_t__,unsigned int) ; 
 unsigned int get_order (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void poch_channel_free_groups(struct channel_info *channel)
{
	unsigned long i;

	for (i = 0; i < channel->group_count; i++) {
		struct poch_group_info *group;
		unsigned int order;

		group = &channel->groups[i];
		order = get_order(channel->group_size);
		if (group->pg)
			__free_pages(group->pg, order);
	}
}