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
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_4__ {int NumTokens; int /*<<< orphan*/ ** Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  int UINT ;

/* Variables and functions */
 int MAX_SIZE ; 
 int /*<<< orphan*/  Print (char*) ; 
 int ToInt (char*) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UniFreeToken (TYPE_1__*) ; 
 TYPE_1__* UniParseToken (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,char*) ; 
 int UniToInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

bool CheckStrings()
{
	wchar_t *numstr = _UU("CHECK_TEST_123456789");
	char tmp[MAX_SIZE];
	wchar_t tmp2[MAX_SIZE];
	UINT i;
	UINT sum, sum2;
	UNI_TOKEN_LIST *t;

	UniStrCpy(tmp2, sizeof(tmp2), L"");

	sum2 = 0;
	for (i = 0;i < 64;i++)
	{
		sum2 += i;
		UniFormat(tmp2, sizeof(tmp2), L"%s,%u", tmp2, i);
	}

	t = UniParseToken(tmp2, L",");

	sum = 0;

	for (i = 0;i < t->NumTokens;i++)
	{
		wchar_t *s = t->Token[i];
		UINT n = UniToInt(s);

		sum += n;
	}

	UniFreeToken(t);

	if (sum != sum2)
	{
		Print("UniParseToken Failed.\n");
		return false;
	}

	if (UniToInt(numstr) != 123456789)
	{
		Print("UniToInt Failed.\n");
		return false;
	}

	UniToStr(tmp, sizeof(tmp), numstr);
	if (ToInt(tmp) != 123456789)
	{
		Print("UniToStr Failed.\n");
		return false;
	}

	return true;
}