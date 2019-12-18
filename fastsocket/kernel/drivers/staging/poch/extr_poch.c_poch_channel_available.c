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
struct channel_info {int group_count; int /*<<< orphan*/  group_offsets_lock; TYPE_1__* header; } ;
struct TYPE_2__ {int* group_offsets; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int poch_channel_available(struct channel_info *channel)
{
	int i;

	spin_lock_irq(&channel->group_offsets_lock);

	for (i = 0; i < channel->group_count; i++) {
		if (channel->header->group_offsets[i] != -1) {
			spin_unlock_irq(&channel->group_offsets_lock);
			return 1;
		}
	}

	spin_unlock_irq(&channel->group_offsets_lock);

	return 0;
}