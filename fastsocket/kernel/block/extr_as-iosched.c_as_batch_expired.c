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
struct as_data {scalar_t__ batch_data_dir; scalar_t__ current_write_count; int /*<<< orphan*/  current_batch_expires; scalar_t__ new_batch; scalar_t__ changed_batch; } ;

/* Variables and functions */
 scalar_t__ BLK_RW_SYNC ; 
 int /*<<< orphan*/  jiffies ; 
 int time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int as_batch_expired(struct as_data *ad)
{
	if (ad->changed_batch || ad->new_batch)
		return 0;

	if (ad->batch_data_dir == BLK_RW_SYNC)
		/* TODO! add a check so a complete fifo gets written? */
		return time_after(jiffies, ad->current_batch_expires);

	return time_after(jiffies, ad->current_batch_expires)
		|| ad->current_write_count == 0;
}