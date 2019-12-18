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
struct slot_dt9812 {int /*<<< orphan*/  mutex; scalar_t__ usb; } ;

/* Variables and functions */
 int ENODEV ; 
 int F020_SFR_P1 ; 
 int F020_SFR_P3 ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 int dt9812_read_multiple_registers (scalar_t__,int,int*,int*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dt9812_digital_in(struct slot_dt9812 *slot, u8 * bits)
{
	int result = -ENODEV;

	down(&slot->mutex);
	if (slot->usb) {
		u8 reg[2] = { F020_SFR_P3, F020_SFR_P1 };
		u8 value[2];

		result = dt9812_read_multiple_registers(slot->usb, 2, reg,
							value);
		if (result == 0) {
			/*
			 * bits 0-6 in F020_SFR_P3 are bits 0-6 in the digital
			 * input port bit 3 in F020_SFR_P1 is bit 7 in the
			 * digital input port
			 */
			*bits = (value[0] & 0x7f) | ((value[1] & 0x08) << 4);
			/* printk("%2.2x, %2.2x -> %2.2x\n",
			   value[0], value[1], *bits); */
		}
	}
	up(&slot->mutex);

	return result;
}