#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  ss ;
typedef  scalar_t__ UINT ;
typedef  void* UCHAR ;
struct TYPE_10__ {scalar_t__ ipv6_scope_id; void** ipv6_addr; } ;
struct TYPE_9__ {int NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ IP ;

/* Variables and functions */
 int CheckIPItemStr6 (char*) ; 
 int /*<<< orphan*/  Copy (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ EndWith (char*,char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/  IPItemStrToChars6 (void**,char*) ; 
 int MAX_PATH ; 
 TYPE_1__* ParseTokenWithNullStr (char*,char*) ; 
 scalar_t__ SearchStrEx (char*,char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  StrCpyAllowOverlap (char*,int,char*) ; 
 scalar_t__ StrLen (char*) ; 
 scalar_t__ ToInt (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  ZeroIP6 (TYPE_2__*) ; 

bool StrToIP6(IP *ip, char *str)
{
	TOKEN_LIST *t;
	char tmp[MAX_PATH];
	IP a;
	UINT i;
	UINT scope_id = 0;
	// Validate arguments
	if (str == NULL || ip == NULL)
	{
		return false;
	}

	ZeroIP6(&a);

	StrCpy(tmp, sizeof(tmp), str);
	Trim(tmp);

	if (StartWith(tmp, "[") && EndWith(tmp, "]"))
	{
		// If the string is enclosed in square brackets, remove brackets
		StrCpyAllowOverlap(tmp, sizeof(tmp), &tmp[1]);

		if (StrLen(tmp) >= 1)
		{
			tmp[StrLen(tmp) - 1] = 0;
		}
	}

	// Remove the scope ID by analyzing if there is it
	i = SearchStrEx(tmp, "%", 0, false);
	if (i != INFINITE)
	{
		char ss[MAX_PATH];

		StrCpy(ss, sizeof(ss), &tmp[i + 1]);

		tmp[i] = 0;

		Trim(tmp);

		Trim(ss);

		scope_id = ToInt(ss);
	}

	// Tokenize
	t = ParseTokenWithNullStr(tmp, ":");
	if (t->NumTokens >= 3 && t->NumTokens <= 8)
	{
		UINT i, n;
		bool b = true;
		UINT k = 0;

		n = 0;

		for (i = 0;i < t->NumTokens;i++)
		{
			char *str = t->Token[i];

			if (i != 0 && i != (t->NumTokens - 1) && StrLen(str) == 0)
			{
				n++;
				if (n == 1)
				{
					k += 2 * (8 - t->NumTokens + 1);
				}
				else
				{
					b = false;
					break;
				}
			}
			else
			{
				UCHAR chars[2];

				if (CheckIPItemStr6(str) == false)
				{
					b = false;
					break;
				}

				IPItemStrToChars6(chars, str);

				a.ipv6_addr[k++] = chars[0];
				a.ipv6_addr[k++] = chars[1];
			}
		}

		if (n != 0 && n != 1)
		{
			b = false;
		}
		else if (n == 0 && t->NumTokens != 8)
		{
			b = false;
		}

		if (b == false)
		{
			FreeToken(t);
			return false;
		}
	}
	else
	{
		FreeToken(t);
		return false;
	}

	FreeToken(t);

	Copy(ip, &a, sizeof(IP));

	ip->ipv6_scope_id = scope_id;

	return true;
}