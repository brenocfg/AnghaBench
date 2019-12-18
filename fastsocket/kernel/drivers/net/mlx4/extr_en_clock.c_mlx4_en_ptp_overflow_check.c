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
struct mlx4_en_dev {scalar_t__ last_overflow_check; int /*<<< orphan*/  clock; scalar_t__ overflow_period; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int time_is_before_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  timecounter_read (int /*<<< orphan*/ *) ; 

void mlx4_en_ptp_overflow_check(struct mlx4_en_dev *mdev)
{
	bool timeout = time_is_before_jiffies(mdev->last_overflow_check +
					      mdev->overflow_period);

	if (timeout) {
		timecounter_read(&mdev->clock);
		mdev->last_overflow_check = jiffies;
	}
}