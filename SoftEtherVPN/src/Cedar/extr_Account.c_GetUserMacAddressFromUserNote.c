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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  macstr_a ;
typedef  int /*<<< orphan*/  macstr2 ;
struct TYPE_4__ {int NumTokens; int /*<<< orphan*/ ** Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  size_t UINT ;
typedef  int /*<<< orphan*/  UCHAR ;

/* Variables and functions */
 size_t INFINITE ; 
 int MAX_SIZE ; 
 int StrToMac (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  USER_MAC_STR_PREFIX ; 
 int /*<<< orphan*/  UniFreeToken (TYPE_1__*) ; 
 int UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 TYPE_1__* UniParseToken (int /*<<< orphan*/ *,char*) ; 
 size_t UniSearchStrEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 size_t UniStrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniTrim (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool GetUserMacAddressFromUserNote(UCHAR *mac, wchar_t *note)
{
	bool ret = false;
	UINT i;

	Zero(mac, 6);
	if (mac == NULL || note == NULL)
	{
		return false;
	}

	i = UniSearchStrEx(note, USER_MAC_STR_PREFIX, 0, false);
	if (i != INFINITE)
	{
		wchar_t *macstr_start = &note[i + UniStrLen(USER_MAC_STR_PREFIX)];
		wchar_t macstr2[MAX_SIZE];
		UNI_TOKEN_LIST *tokens;

		UniStrCpy(macstr2, sizeof(macstr2), macstr_start);

		UniTrim(macstr2);

		tokens = UniParseToken(macstr2, L" ,/()[].");
		if (tokens != NULL)
		{
			if (tokens->NumTokens >= 1)
			{
				wchar_t *macstr = tokens->Token[0];

				if (UniIsEmptyStr(macstr) == false)
				{
					char macstr_a[MAX_SIZE];

					UniToStr(macstr_a, sizeof(macstr_a), macstr);

					ret = StrToMac(mac, macstr_a);
				}
			}

			UniFreeToken(tokens);
		}
	}

	return ret;
}