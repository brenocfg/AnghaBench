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
struct TYPE_4__ {size_t NumTokens; int /*<<< orphan*/ ** Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  size_t UINT ;

/* Variables and functions */
 int IsEmptyUniStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniFreeToken (TYPE_1__*) ; 
 TYPE_1__* UniParseToken (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ UniStartWith (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  UniToStr (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniTrim (int /*<<< orphan*/ *) ; 

bool IsURLMsg(wchar_t *str, char *url, UINT url_size)
{
	UNI_TOKEN_LIST *t;
	bool ret = false;
	UINT i;
	UINT n = 0;
	// Validate arguments
	if (str == NULL)
	{
		return false;
	}

	t = UniParseToken(str, L"\r\n");

	for (i = 0;i < t->NumTokens;i++)
	{
		wchar_t *str = t->Token[i];

		if (IsEmptyUniStr(str) == false)
		{
			n++;

			UniTrim(str);

			if (n == 1)
			{
				if (UniStartWith(str, L"http://") ||
					UniStartWith(str, L"https://") ||
					UniStartWith(str, L"ftp://"))
				{
					ret = true;

					UniToStr(url, url_size, str);
				}
			}
		}
	}

	if (n != 1)
	{
		ret = false;
	}

	UniFreeToken(t);

	return ret;
}