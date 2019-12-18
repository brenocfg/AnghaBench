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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ *,int) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NS_MAC_ADDRESS_BYTE_1 ; 
 int /*<<< orphan*/  NsGenMacAddressSignatureForMachine (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrLower (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

void NsGenMacAddress(void *dest, char *mac_address_seed, char *device_name)
{
	char tmp[MAX_SIZE];
	UCHAR mac[6];
	UCHAR hash[SHA1_SIZE];

	Zero(tmp, sizeof(tmp));

	StrCat(tmp, sizeof(tmp), mac_address_seed);
	StrCat(tmp, sizeof(tmp), "@");
	StrCat(tmp, sizeof(tmp), device_name);

	Trim(tmp);

	StrLower(tmp);

	Sha1(hash, tmp, StrLen(tmp));

	mac[0] = NS_MAC_ADDRESS_BYTE_1;
	mac[1] = hash[1];
	mac[2] = hash[2];
	mac[3] = hash[3];
	mac[4] = hash[4];
	mac[5] = hash[5];

	NsGenMacAddressSignatureForMachine(mac + 4, mac);

	Copy(dest, mac, 6);
}