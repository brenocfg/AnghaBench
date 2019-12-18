#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  ip_and_mask ;
typedef  int /*<<< orphan*/  gateway ;
struct TYPE_8__ {int Exists; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  Network; int /*<<< orphan*/  Gateway; int /*<<< orphan*/  SubnetMaskLen; } ;
struct TYPE_7__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ DHCP_CLASSLESS_ROUTE ;

/* Variables and functions */
 int /*<<< orphan*/  Format (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 int /*<<< orphan*/  IPAnd4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ ParseIpAndSubnetMask46 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ParseTokenWithoutNullStr (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ StrToIP (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SubnetMaskToInt4 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool ParseClasslessRouteStr(DHCP_CLASSLESS_ROUTE *r, char *str)
{
	TOKEN_LIST *t;
	bool ret = false;
	char tmp[MAX_PATH];
	// Validate arguments
	if (r == NULL || str == NULL)
	{
		return false;
	}

	StrCpy(tmp, sizeof(tmp), str);
	Trim(tmp);

	t = ParseTokenWithoutNullStr(str, "/");
	if (t == NULL)
	{
		return false;
	}

	if (t->NumTokens == 3)
	{
		char ip_and_mask[MAX_PATH];
		char gateway[MAX_PATH];

		Zero(r, sizeof(DHCP_CLASSLESS_ROUTE));

		Format(ip_and_mask, sizeof(ip_and_mask), "%s/%s", t->Token[0], t->Token[1]);
		StrCpy(gateway, sizeof(gateway), t->Token[2]);

		if (ParseIpAndSubnetMask46(ip_and_mask, &r->Network, &r->SubnetMask))
		{
			r->SubnetMaskLen = SubnetMaskToInt4(&r->SubnetMask);

			if (StrToIP(&r->Gateway, gateway))
			{
				if (IsIP4(&r->Gateway) && IsIP4(&r->Network) && IsIP4(&r->SubnetMask))
				{
					r->Exists = true;

					IPAnd4(&r->Network, &r->Network, &r->SubnetMask);

					ret = true;
				}
			}
		}
	}

	FreeToken(t);

	return ret;
}