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
typedef  int u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mii_getbit (struct net_device*) ; 
 int /*<<< orphan*/  mii_send_bits (struct net_device*,int,int) ; 

__attribute__((used)) static void miiport_write(struct net_device *dev, int phy_id, int reg, u16 data)
{
	u32 cmd;

	/* Ensure sync */
	mii_send_bits (dev, 0xffffffff, 32);
	/* ST(2), OP(2), ADDR(5), REG#(5), TA(2), Data(16) total 32 bits */
	/* ST,OP,AAAAA,RRRRR,TA = 0101xxxxxxxxxx10'b = 0x5002 for write */
	cmd = (0x5002 << 16) | (phy_id << 23) | (reg << 18) | data;
	mii_send_bits (dev, cmd, 32);
	/* End cycle */
	mii_getbit (dev);
}