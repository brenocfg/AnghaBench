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
typedef  unsigned char u64 ;
struct adapter {unsigned char mcastmask; } ;

/* Variables and functions */
 unsigned char slic_mcast_get_mac_hash (char*) ; 

__attribute__((used)) static void slic_mcast_set_bit(struct adapter *adapter, char *address)
{
	unsigned char crcpoly;

	/* Get the CRC polynomial for the mac address */
	crcpoly = slic_mcast_get_mac_hash(address);

	/* We only have space on the SLIC for 64 entries.  Lop
	 * off the top two bits. (2^6 = 64)
	 */
	crcpoly &= 0x3F;

	/* OR in the new bit into our 64 bit mask. */
	adapter->mcastmask |= (u64) 1 << crcpoly;
}