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
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  hash ;
typedef  int UCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int*,int) ; 
 int /*<<< orphan*/  GenerateMachineUniqueHash (int*) ; 
 int MAX_SIZE ; 
 int SE_HUB_MAC_ADDR_SIGN ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 

void GenHubMacAddress(UCHAR *mac, char *name)
{
	char tmp1[MAX_SIZE];
	char tmp2[MAX_SIZE];
	UCHAR hash[SHA1_SIZE];
	// Validate arguments
	if (mac == NULL || name == NULL)
	{
		return;
	}

	StrCpy(tmp1, sizeof(tmp1), name);
	Trim(tmp1);
	GenerateMachineUniqueHash(hash);
	BinToStr(tmp2, sizeof(tmp2), hash, sizeof(hash));
	StrCat(tmp2, sizeof(tmp2), tmp1);
	StrUpper(tmp2);

	Sha0(hash, tmp2, StrLen(tmp2));

	mac[0] = 0x00;
	mac[1] = SE_HUB_MAC_ADDR_SIGN;
	mac[2] = hash[0];
	mac[3] = hash[1];
	mac[4] = hash[2];
	mac[5] = hash[3];
}