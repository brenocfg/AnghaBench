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
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_GLOBAL ; 
 int /*<<< orphan*/  REG_PORT (int) ; 
 int REG_READ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int mv88e6060_switch_reset(struct dsa_switch *ds)
{
	int i;
	int ret;

	/*
	 * Set all ports to the disabled state.
	 */
	for (i = 0; i < 6; i++) {
		ret = REG_READ(REG_PORT(i), 0x04);
		REG_WRITE(REG_PORT(i), 0x04, ret & 0xfffc);
	}

	/*
	 * Wait for transmit queues to drain.
	 */
	msleep(2);

	/*
	 * Reset the switch.
	 */
	REG_WRITE(REG_GLOBAL, 0x0a, 0xa130);

	/*
	 * Wait up to one second for reset to complete.
	 */
	for (i = 0; i < 1000; i++) {
		ret = REG_READ(REG_GLOBAL, 0x00);
		if ((ret & 0x8000) == 0x0000)
			break;

		msleep(1);
	}
	if (i == 1000)
		return -ETIMEDOUT;

	return 0;
}