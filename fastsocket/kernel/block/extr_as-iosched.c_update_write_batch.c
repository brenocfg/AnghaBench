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
struct as_data {unsigned long* batch_expire; unsigned long current_batch_expires; int write_batch_count; scalar_t__ current_write_count; int /*<<< orphan*/  write_batch_idled; } ;

/* Variables and functions */
 size_t BLK_RW_ASYNC ; 
 unsigned long jiffies ; 

__attribute__((used)) static void update_write_batch(struct as_data *ad)
{
	unsigned long batch = ad->batch_expire[BLK_RW_ASYNC];
	long write_time;

	write_time = (jiffies - ad->current_batch_expires) + batch;
	if (write_time < 0)
		write_time = 0;

	if (write_time > batch && !ad->write_batch_idled) {
		if (write_time > batch * 3)
			ad->write_batch_count /= 2;
		else
			ad->write_batch_count--;
	} else if (write_time < batch && ad->current_write_count == 0) {
		if (batch > write_time * 3)
			ad->write_batch_count *= 2;
		else
			ad->write_batch_count++;
	}

	if (ad->write_batch_count < 1)
		ad->write_batch_count = 1;
}