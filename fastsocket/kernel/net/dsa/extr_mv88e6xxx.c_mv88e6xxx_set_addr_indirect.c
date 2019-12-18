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
struct dsa_switch {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_GLOBAL2 ; 
 int REG_READ (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int,int) ; 

int mv88e6xxx_set_addr_indirect(struct dsa_switch *ds, u8 *addr)
{
	int i;
	int ret;

	for (i = 0; i < 6; i++) {
		int j;

		/*
		 * Write the MAC address byte.
		 */
		REG_WRITE(REG_GLOBAL2, 0x0d, 0x8000 | (i << 8) | addr[i]);

		/*
		 * Wait for the write to complete.
		 */
		for (j = 0; j < 16; j++) {
			ret = REG_READ(REG_GLOBAL2, 0x0d);
			if ((ret & 0x8000) == 0)
				break;
		}
		if (j == 16)
			return -ETIMEDOUT;
	}

	return 0;
}