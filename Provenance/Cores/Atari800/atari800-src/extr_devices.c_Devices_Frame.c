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

/* Variables and functions */
 int /*<<< orphan*/  B_TABLE_ADDRESS ; 
 int /*<<< orphan*/  Devices_UpdateHATABSEntry (char,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Devices_enable_b_patch ; 
 scalar_t__ Devices_enable_h_patch ; 
 scalar_t__ Devices_enable_r_patch ; 
 int /*<<< orphan*/  H_TABLE_ADDRESS ; 
 int /*<<< orphan*/  R_TABLE_ADDRESS ; 
 int /*<<< orphan*/  b_entry_address ; 
 int /*<<< orphan*/  h_entry_address ; 
 int /*<<< orphan*/  r_entry_address ; 

void Devices_Frame(void)
{
	if (Devices_enable_h_patch)
		h_entry_address = Devices_UpdateHATABSEntry('H', h_entry_address, H_TABLE_ADDRESS);

#ifdef R_IO_DEVICE
	if (Devices_enable_r_patch)
		r_entry_address = Devices_UpdateHATABSEntry('R', r_entry_address, R_TABLE_ADDRESS);
#endif

	if (Devices_enable_b_patch)
		b_entry_address = Devices_UpdateHATABSEntry('B', b_entry_address, B_TABLE_ADDRESS);
}