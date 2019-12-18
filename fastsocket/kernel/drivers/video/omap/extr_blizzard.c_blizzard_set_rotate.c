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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BLIZZARD_PANEL_CONFIGURATION ; 
 int EINVAL ; 
 int blizzard_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blizzard_write_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int blizzard_set_rotate(int angle)
{
	u32 l;

	l = blizzard_read_reg(BLIZZARD_PANEL_CONFIGURATION);
	l &= ~0x03;

	switch (angle) {
	case 0:
		l = l | 0x00;
		break;
	case 90:
		l = l | 0x03;
		break;
	case 180:
		l = l | 0x02;
		break;
	case 270:
		l = l | 0x01;
		break;
	default:
		return -EINVAL;
	}

	blizzard_write_reg(BLIZZARD_PANEL_CONFIGURATION, l);

	return 0;
}