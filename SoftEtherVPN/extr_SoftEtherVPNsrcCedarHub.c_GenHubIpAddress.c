#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  hash ;
typedef  int UCHAR ;
struct TYPE_4__ {int* addr; } ;
typedef  TYPE_1__ IP ;

/* Variables and functions */
 int /*<<< orphan*/  BinToStr (char*,int,int*,int) ; 
 int /*<<< orphan*/  GenerateMachineUniqueHash (int*) ; 
 int MAX_SIZE ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void GenHubIpAddress(IP *ip, char *name)
{
	char tmp1[MAX_SIZE];
	char tmp2[MAX_SIZE];
	UCHAR hash[SHA1_SIZE];
	// Validate arguments
	if (ip == NULL || name == NULL)
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

	Zero(ip, sizeof(IP));
	ip->addr[0] = 172;
	ip->addr[1] = 31;
	ip->addr[2] = hash[0] % 254 + 1;
	ip->addr[3] = hash[1] % 254 + 1;
}