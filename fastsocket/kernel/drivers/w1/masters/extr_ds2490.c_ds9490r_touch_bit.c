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
struct ds_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ds_touch_bit (struct ds_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 ds9490r_touch_bit(void *data, u8 bit)
{
	u8 ret;
	struct ds_device *dev = data;

	if (ds_touch_bit(dev, bit, &ret))
		return 0;

	return ret;
}