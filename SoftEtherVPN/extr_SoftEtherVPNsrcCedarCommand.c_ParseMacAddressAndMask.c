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
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int IsEmptyStr (char*) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 int StrToMac (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool ParseMacAddressAndMask(char *src, bool *check_mac, UCHAR *mac_bin, UCHAR *mask_bin)
{
	TOKEN_LIST *t;
	char *macstr, *maskstr;
	UCHAR mac[6], mask[6];
	bool ok = false;

	// Validate arguments
	if (src == NULL)
	{
		return false;
	}

	//Zero(mac, sizeof(mac));
	//Zero(mask, sizeof(mask));

	if(check_mac != NULL && mac_bin != NULL && mask_bin != NULL)
	{
		ok = true;
	}
	if(IsEmptyStr(src) != false)
	{
		if(ok != false)
		{
			*check_mac = false;
			Zero(mac_bin, 6);
			Zero(mask_bin, 6);
		}
		return true;
	}

	t = ParseToken(src, "/");
	if(t->NumTokens != 2)
	{
		FreeToken(t);
		return false;
	}

	macstr = t->Token[0];
	maskstr = t->Token[1];

	Trim(macstr);
	Trim(maskstr);

	if(StrToMac(mac, macstr) == false || StrToMac(mask, maskstr) == false)
	{
		FreeToken(t);
		return false;
	}
	else
	{
		if(ok != false)
		{
			Copy(mac_bin, mac, 6);
			Copy(mask_bin, mask, 6);
			*check_mac = true;
		}
	}
	FreeToken(t);

	return true;
}