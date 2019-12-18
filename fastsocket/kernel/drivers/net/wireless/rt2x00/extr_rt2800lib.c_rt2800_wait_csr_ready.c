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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  MAC_CSR0 ; 
 unsigned int REGISTER_BUSY_COUNT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 

int rt2800_wait_csr_ready(struct rt2x00_dev *rt2x00dev)
{
	unsigned int i = 0;
	u32 reg;

	for (i = 0; i < REGISTER_BUSY_COUNT; i++) {
		rt2800_register_read(rt2x00dev, MAC_CSR0, &reg);
		if (reg && reg != ~0)
			return 0;
		msleep(1);
	}

	rt2x00_err(rt2x00dev, "Unstable hardware\n");
	return -EBUSY;
}