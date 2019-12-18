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
struct et131x_adapter {int* PermanentAddress; int* CurrentAddress; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 

void et131x_setup_hardware_properties(struct et131x_adapter *adapter)
{
	/* If have our default mac from registry and no mac address from
	 * EEPROM then we need to generate the last octet and set it on the
	 * device
	 */
	if (adapter->PermanentAddress[0] == 0x00 &&
	    adapter->PermanentAddress[1] == 0x00 &&
	    adapter->PermanentAddress[2] == 0x00 &&
	    adapter->PermanentAddress[3] == 0x00 &&
	    adapter->PermanentAddress[4] == 0x00 &&
	    adapter->PermanentAddress[5] == 0x00) {
		/*
		 * We need to randomly generate the last octet so we
		 * decrease our chances of setting the mac address to
		 * same as another one of our cards in the system
		 */
		get_random_bytes(&adapter->CurrentAddress[5], 1);
		/*
		 * We have the default value in the register we are
		 * working with so we need to copy the current
		 * address into the permanent address
		 */
		memcpy(adapter->PermanentAddress,
			adapter->CurrentAddress, ETH_ALEN);
	} else {
		/* We do not have an override address, so set the
		 * current address to the permanent address and add
		 * it to the device
		 */
		memcpy(adapter->CurrentAddress,
		       adapter->PermanentAddress, ETH_ALEN);
	}
}