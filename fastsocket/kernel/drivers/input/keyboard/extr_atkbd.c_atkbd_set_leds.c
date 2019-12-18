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
struct input_dev {int /*<<< orphan*/  led; } ;
struct atkbd {int /*<<< orphan*/  ps2dev; scalar_t__ extra; struct input_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATKBD_CMD_EX_SETLEDS ; 
 int /*<<< orphan*/  ATKBD_CMD_SETLEDS ; 
 int /*<<< orphan*/  LED_CAPSL ; 
 int /*<<< orphan*/  LED_COMPOSE ; 
 int /*<<< orphan*/  LED_MISC ; 
 int /*<<< orphan*/  LED_MUTE ; 
 int /*<<< orphan*/  LED_NUML ; 
 int /*<<< orphan*/  LED_SCROLLL ; 
 int /*<<< orphan*/  LED_SLEEP ; 
 int /*<<< orphan*/  LED_SUSPEND ; 
 scalar_t__ ps2_command (int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atkbd_set_leds(struct atkbd *atkbd)
{
	struct input_dev *dev = atkbd->dev;
	unsigned char param[2];

	param[0] = (test_bit(LED_SCROLLL, dev->led) ? 1 : 0)
		 | (test_bit(LED_NUML,    dev->led) ? 2 : 0)
		 | (test_bit(LED_CAPSL,   dev->led) ? 4 : 0);
	if (ps2_command(&atkbd->ps2dev, param, ATKBD_CMD_SETLEDS))
		return -1;

	if (atkbd->extra) {
		param[0] = 0;
		param[1] = (test_bit(LED_COMPOSE, dev->led) ? 0x01 : 0)
			 | (test_bit(LED_SLEEP,   dev->led) ? 0x02 : 0)
			 | (test_bit(LED_SUSPEND, dev->led) ? 0x04 : 0)
			 | (test_bit(LED_MISC,    dev->led) ? 0x10 : 0)
			 | (test_bit(LED_MUTE,    dev->led) ? 0x20 : 0);
		if (ps2_command(&atkbd->ps2dev, param, ATKBD_CMD_EX_SETLEDS))
			return -1;
	}

	return 0;
}