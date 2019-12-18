#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int addr; int data; } ;

/* Variables and functions */
 int /*<<< orphan*/  in_le32 (int /*<<< orphan*/ *) ; 
 TYPE_1__* mv64x60_pci_cfgio ; 
 int /*<<< orphan*/  out_le32 (int /*<<< orphan*/ *,int) ; 

u32 mv64x60_cfg_read(u8 *bridge_base, u8 hose, u8 bus, u8 devfn, u8 offset)
{
	out_le32((u32 *)(bridge_base + mv64x60_pci_cfgio[hose].addr),
			(1 << 31) | (bus << 16) | (devfn << 8) | offset);
	return in_le32((u32 *)(bridge_base + mv64x60_pci_cfgio[hose].data));
}