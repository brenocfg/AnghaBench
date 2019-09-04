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
typedef  int wchar_t ;
struct TYPE_4__ {int NumTokens; int** Token; } ;
typedef  TYPE_1__ UNI_TOKEN_LIST ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  CopyUniStr (char*) ; 
 int /*<<< orphan*/  Free (int*) ; 
 int GetNextWordWidth (int*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int* LIST_DATA (int /*<<< orphan*/ *,int) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniCopyStr (int*) ; 
 TYPE_1__* UniNullToken () ; 
 int UniStrLen (int*) ; 
 int UniStrWidth (int*) ; 
 int /*<<< orphan*/  UniTrimLeft (int*) ; 
 void* ZeroMalloc (int) ; 

UNI_TOKEN_LIST *SeparateStringByWidth(wchar_t *str, UINT width)
{
	UINT wp;
	wchar_t *tmp;
	UINT len, i;
	LIST *o;
	UNI_TOKEN_LIST *ret;
	// Validate arguments
	if (str == NULL)
	{
		return UniNullToken();
	}
	if (width == 0)
	{
		width = 1;
	}

	o = NewListFast(NULL);

	len = UniStrLen(str);
	tmp = ZeroMalloc(sizeof(wchar_t) * (len + 32));
	wp = 0;

	for (i = 0;i < (len + 1);i++)
	{
		wchar_t c = str[i];
		UINT next_word_width;
		UINT remain_width;

		switch (c)
		{
		case 0:
		case L'\r':
		case L'\n':
			if (c == L'\r')
			{
				if (str[i + 1] == L'\n')
				{
					i++;
				}
			}

			tmp[wp++] = 0;
			wp = 0;

			Insert(o, UniCopyStr(tmp));
			break;

		default:
			next_word_width = GetNextWordWidth(&str[i]);
			remain_width = (width - UniStrWidth(tmp));

			if ((remain_width >= 1) && (next_word_width > remain_width) && (next_word_width <= width))
			{
				tmp[wp++] = 0;
				wp = 0;

				Insert(o, UniCopyStr(tmp));
			}

			tmp[wp++] = c;
			tmp[wp] = 0;
			if (UniStrWidth(tmp) >= width)
			{
				tmp[wp++] = 0;
				wp = 0;

				Insert(o, UniCopyStr(tmp));
			}
			break;
		}
	}

	if (LIST_NUM(o) == 0)
	{
		Insert(o, CopyUniStr(L""));
	}

	ret = ZeroMalloc(sizeof(UNI_TOKEN_LIST));
	ret->NumTokens = LIST_NUM(o);
	ret->Token = ZeroMalloc(sizeof(wchar_t *) * ret->NumTokens);

	for (i = 0;i < LIST_NUM(o);i++)
	{
		wchar_t *s = LIST_DATA(o, i);

		UniTrimLeft(s);

		ret->Token[i] = s;
	}

	ReleaseList(o);
	Free(tmp);

	return ret;
}