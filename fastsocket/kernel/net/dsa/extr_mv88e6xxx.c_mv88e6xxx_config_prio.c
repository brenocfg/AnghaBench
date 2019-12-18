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
 int /*<<< orphan*/  REG_GLOBAL ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int,int) ; 

int mv88e6xxx_config_prio(struct dsa_switch *ds)
{
	/*
	 * Configure the IP ToS mapping registers.
	 */
	REG_WRITE(REG_GLOBAL, 0x10, 0x0000);
	REG_WRITE(REG_GLOBAL, 0x11, 0x0000);
	REG_WRITE(REG_GLOBAL, 0x12, 0x5555);
	REG_WRITE(REG_GLOBAL, 0x13, 0x5555);
	REG_WRITE(REG_GLOBAL, 0x14, 0xaaaa);
	REG_WRITE(REG_GLOBAL, 0x15, 0xaaaa);
	REG_WRITE(REG_GLOBAL, 0x16, 0xffff);
	REG_WRITE(REG_GLOBAL, 0x17, 0xffff);

	/*
	 * Configure the IEEE 802.1p priority mapping register.
	 */
	REG_WRITE(REG_GLOBAL, 0x18, 0xfa41);

	return 0;
}