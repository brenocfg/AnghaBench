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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int set_beacon_interval (struct zd_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int zd_set_beacon_interval(struct zd_chip *chip, u16 interval, u8 dtim_period,
			   int type)
{
	int r;

	mutex_lock(&chip->mutex);
	r = set_beacon_interval(chip, interval, dtim_period, type);
	mutex_unlock(&chip->mutex);
	return r;
}