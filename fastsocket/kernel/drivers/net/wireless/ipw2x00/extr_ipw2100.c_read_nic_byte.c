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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_REG_INDIRECT_ACCESS_ADDRESS ; 
 int /*<<< orphan*/  IPW_REG_INDIRECT_ACCESS_DATA ; 
 int IPW_REG_INDIRECT_ADDR_MASK ; 
 int /*<<< orphan*/  read_register_byte (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_register (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void read_nic_byte(struct net_device *dev, u32 addr, u8 * val)
{
	write_register(dev, IPW_REG_INDIRECT_ACCESS_ADDRESS,
		       addr & IPW_REG_INDIRECT_ADDR_MASK);
	read_register_byte(dev, IPW_REG_INDIRECT_ACCESS_DATA, val);
}