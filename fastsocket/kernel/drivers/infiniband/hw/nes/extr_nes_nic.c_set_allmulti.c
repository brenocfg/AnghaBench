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
struct nes_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NES_IDX_NIC_MULTICAST_ALL ; 
 int /*<<< orphan*/  NES_IDX_NIC_UNICAST_ALL ; 
 int /*<<< orphan*/  nes_read_indexed (struct nes_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_write_indexed (struct nes_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_allmulti(struct nes_device *nesdev, u32 nic_active_bit)
{
	u32 nic_active;

	nic_active = nes_read_indexed(nesdev, NES_IDX_NIC_MULTICAST_ALL);
	nic_active |= nic_active_bit;
	nes_write_indexed(nesdev, NES_IDX_NIC_MULTICAST_ALL, nic_active);
	nic_active = nes_read_indexed(nesdev, NES_IDX_NIC_UNICAST_ALL);
	nic_active &= ~nic_active_bit;
	nes_write_indexed(nesdev, NES_IDX_NIC_UNICAST_ALL, nic_active);
}