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
struct poch_group_info {int user_offset; } ;
struct channel_info {int group_count; scalar_t__ dir; struct poch_group_info* groups; TYPE_1__* header; int /*<<< orphan*/  group_offsets_lock; int /*<<< orphan*/  group_size; } ;
typedef  int s32 ;
struct TYPE_2__ {int group_count; int* group_offsets; int /*<<< orphan*/  group_size_bytes; } ;

/* Variables and functions */
 scalar_t__ CHANNEL_DIR_RX ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void poch_channel_init_header(struct channel_info *channel)
{
	int i;
	struct poch_group_info *groups;
	s32 *group_offsets;

	channel->header->group_size_bytes = channel->group_size;
	channel->header->group_count = channel->group_count;

	spin_lock_init(&channel->group_offsets_lock);

	group_offsets = channel->header->group_offsets;
	groups = channel->groups;

	for (i = 0; i < channel->group_count; i++) {
		if (channel->dir == CHANNEL_DIR_RX)
			group_offsets[i] = -1;
		else
			group_offsets[i] = groups[i].user_offset;
	}
}