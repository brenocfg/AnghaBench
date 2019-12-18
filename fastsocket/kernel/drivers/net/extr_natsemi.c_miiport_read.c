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
struct net_device {int dummy; } ;

/* Variables and functions */
 int mii_getbit (struct net_device*) ; 
 int /*<<< orphan*/  mii_send_bits (struct net_device*,int,int) ; 

__attribute__((used)) static int miiport_read(struct net_device *dev, int phy_id, int reg)
{
	u32 cmd;
	int i;
	u32 retval = 0;

	/* Ensure sync */
	mii_send_bits (dev, 0xffffffff, 32);
	/* ST(2), OP(2), ADDR(5), REG#(5), TA(2), Data(16) total 32 bits */
	/* ST,OP = 0110'b for read operation */
	cmd = (0x06 << 10) | (phy_id << 5) | reg;
	mii_send_bits (dev, cmd, 14);
	/* Turnaround */
	if (mii_getbit (dev))
		return 0;
	/* Read data */
	for (i = 0; i < 16; i++) {
		retval <<= 1;
		retval |= mii_getbit (dev);
	}
	/* End cycle */
	mii_getbit (dev);
	return retval;
}