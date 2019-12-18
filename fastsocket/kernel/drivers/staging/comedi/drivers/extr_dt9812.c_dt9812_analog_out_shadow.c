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
typedef  int /*<<< orphan*/  u16 ;
struct slot_dt9812 {int /*<<< orphan*/  mutex; TYPE_1__* usb; } ;
struct TYPE_2__ {int /*<<< orphan*/ * analog_out_shadow; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dt9812_analog_out_shadow(struct slot_dt9812 *slot, int channel,
				    u16 * value)
{
	int result = -ENODEV;

	down(&slot->mutex);
	if (slot->usb) {
		*value = slot->usb->analog_out_shadow[channel];
		result = 0;
	}
	up(&slot->mutex);

	return result;
}