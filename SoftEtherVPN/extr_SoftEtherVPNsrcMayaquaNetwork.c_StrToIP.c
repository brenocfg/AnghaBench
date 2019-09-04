#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  scalar_t__ UCHAR ;
struct TYPE_9__ {scalar_t__* addr; } ;
struct TYPE_8__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ IP ;

/* Variables and functions */
 char* CopyStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 scalar_t__ StrToIP6 (TYPE_2__*,char*) ; 
 int ToInt (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool StrToIP(IP *ip, char *str)
{
	TOKEN_LIST *token;
	char *tmp;
	UINT i;
	// Validate arguments
	if (ip == NULL || str == NULL)
	{
		return false;
	}

	if (StrToIP6(ip, str))
	{
		return true;
	}

	Zero(ip, sizeof(IP));

	tmp = CopyStr(str);
	Trim(tmp);
	token = ParseToken(tmp, ".");
	Free(tmp);

	if (token->NumTokens != 4)
	{
		FreeToken(token);
		return false;
	}
	for (i = 0;i < 4;i++)
	{
		char *s = token->Token[i];
		if (s[0] < '0' || s[0] > '9' ||
			(ToInt(s) >= 256))
		{
			FreeToken(token);
			return false;
		}
	}
	Zero(ip, sizeof(IP));
	for (i = 0;i < 4;i++)
	{
		ip->addr[i] = (UCHAR)ToInt(token->Token[i]);
	}

	FreeToken(token);

	return true;
}