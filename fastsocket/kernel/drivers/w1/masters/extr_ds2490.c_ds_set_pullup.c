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
typedef  int u8 ;
struct ds_device {int spu_sleep; int /*<<< orphan*/  spu_bit; } ;

/* Variables and functions */
 int COMM_IM ; 
 int COMM_SET_DURATION ; 
 int /*<<< orphan*/  COMM_SPU ; 
 int ds_send_control (struct ds_device*,int,int) ; 

__attribute__((used)) static int ds_set_pullup(struct ds_device *dev, int delay)
{
	int err = 0;
	u8 del = 1 + (u8)(delay >> 4);
	/* Just storing delay would not get the trunication and roundup. */
	int ms = del<<4;

	/* Enable spu_bit if a delay is set. */
	dev->spu_bit = delay ? COMM_SPU : 0;
	/* If delay is zero, it has already been disabled, if the time is
	 * the same as the hardware was last programmed to, there is also
	 * nothing more to do.  Compare with the recalculated value ms
	 * rather than del or delay which can have a different value.
	 */
	if (delay == 0 || ms == dev->spu_sleep)
		return err;

	err = ds_send_control(dev, COMM_SET_DURATION | COMM_IM, del);
	if (err)
		return err;

	dev->spu_sleep = ms;

	return err;
}