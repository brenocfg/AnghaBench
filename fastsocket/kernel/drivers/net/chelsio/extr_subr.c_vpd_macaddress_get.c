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
typedef  scalar_t__ u8 ;
struct chelsio_vpd_t {scalar_t__* mac_base_address; } ;
typedef  int /*<<< orphan*/  adapter_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ t1_eeprom_vpd_get (int /*<<< orphan*/ *,struct chelsio_vpd_t*) ; 

__attribute__((used)) static int vpd_macaddress_get(adapter_t *adapter, int index, u8 mac_addr[])
{
	struct chelsio_vpd_t vpd;

	if (t1_eeprom_vpd_get(adapter, &vpd))
		return 1;
	memcpy(mac_addr, vpd.mac_base_address, 5);
	mac_addr[5] = vpd.mac_base_address[5] + index;
	return 0;
}