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
typedef  int u32 ;
struct controller {scalar_t__ pcix_support; scalar_t__ hpc_reg; } ;

/* Variables and functions */
 scalar_t__ NON_INT_INPUT ; 
 int PCI_SPEED_133MHz_PCIX ; 
 int PCI_SPEED_33MHz ; 
 int PCI_SPEED_66MHz ; 
 int PCI_SPEED_66MHz_PCIX ; 
 int /*<<< orphan*/  dbg (char*,int,int) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static inline u8 get_adapter_speed(struct controller *ctrl, u8 hp_slot)
{
	u32 temp_dword = readl(ctrl->hpc_reg + NON_INT_INPUT);
	dbg("slot: %d, PCIXCAP: %8x\n", hp_slot, temp_dword);
	if (ctrl->pcix_support) {
		if (temp_dword & (0x10000 << hp_slot))
			return PCI_SPEED_133MHz_PCIX;
		if (temp_dword & (0x100 << hp_slot))
			return PCI_SPEED_66MHz_PCIX;
	}

	if (temp_dword & (0x01 << hp_slot))
		return PCI_SPEED_66MHz;

	return PCI_SPEED_33MHz;
}