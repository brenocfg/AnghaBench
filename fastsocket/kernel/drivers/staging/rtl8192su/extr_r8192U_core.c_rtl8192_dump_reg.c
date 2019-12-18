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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_PHY ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  read_nic_byte (struct net_device*,int) ; 

void rtl8192_dump_reg(struct net_device *dev)
{
	int i;
	int n;
	int max=0x1ff;

	RT_TRACE(COMP_PHY, "Dumping NIC register map");

	for(n=0;n<=max;)
	{
		printk( "\nD: %2x> ", n);
		for(i=0;i<16 && n<=max;i++,n++)
			printk("%2x ",read_nic_byte(dev,n));
	}
	printk("\n");
}