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
typedef  int u16 ;
struct nic {int eeprom_wc; int /*<<< orphan*/  netdev; int /*<<< orphan*/ * eeprom; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  e100_eeprom_read (struct nic*,int*,int) ; 
 int /*<<< orphan*/  eeprom_bad_csum_allow ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  probe ; 

__attribute__((used)) static int e100_eeprom_load(struct nic *nic)
{
	u16 addr, addr_len = 8, checksum = 0;

	/* Try reading with an 8-bit addr len to discover actual addr len */
	e100_eeprom_read(nic, &addr_len, 0);
	nic->eeprom_wc = 1 << addr_len;

	for (addr = 0; addr < nic->eeprom_wc; addr++) {
		nic->eeprom[addr] = e100_eeprom_read(nic, &addr_len, addr);
		if (addr < nic->eeprom_wc - 1)
			checksum += le16_to_cpu(nic->eeprom[addr]);
	}

	/* The checksum, stored in the last word, is calculated such that
	 * the sum of words should be 0xBABA */
	if (cpu_to_le16(0xBABA - checksum) != nic->eeprom[nic->eeprom_wc - 1]) {
		netif_err(nic, probe, nic->netdev, "EEPROM corrupted\n");
		if (!eeprom_bad_csum_allow)
			return -EAGAIN;
	}

	return 0;
}