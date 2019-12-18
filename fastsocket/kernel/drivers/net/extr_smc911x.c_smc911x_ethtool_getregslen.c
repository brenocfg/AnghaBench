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
struct net_device {int dummy; } ;

/* Variables and functions */
 int E2P_CMD ; 
 int ID_REV ; 
 int MAC_CR ; 
 int WUCSR ; 

__attribute__((used)) static int smc911x_ethtool_getregslen(struct net_device *dev)
{
	/* System regs + MAC regs + PHY regs */
	return (((E2P_CMD - ID_REV)/4 + 1) +
			(WUCSR - MAC_CR)+1 + 32) * sizeof(u32);
}