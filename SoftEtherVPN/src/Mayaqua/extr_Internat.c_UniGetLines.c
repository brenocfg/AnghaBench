#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  int /*<<< orphan*/  UNI_TOKEN_LIST ;
typedef  size_t UINT ;
struct TYPE_6__ {scalar_t__ Buf; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClearBuf (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_1__*) ; 
 TYPE_1__* NewBuf () ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniCopyStr (int*) ; 
 int /*<<< orphan*/  UniFreeStrList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UniListToTokenList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UniNullToken () ; 
 size_t UniStrLen (int*) ; 
 int /*<<< orphan*/  WriteBuf (TYPE_1__*,int*,int) ; 

UNI_TOKEN_LIST *UniGetLines(wchar_t *str)
{
	UINT i, len;
	BUF *b = NULL;
	LIST *o;
	UNI_TOKEN_LIST *ret;
	// Validate arguments
	if (str == NULL)
	{
		return UniNullToken();
	}

	o = NewListFast(NULL);

	len = UniStrLen(str);

	b = NewBuf();

	for (i = 0;i < len;i++)
	{
		wchar_t c = str[i];
		bool f = false;

		if (c == L'\r')
		{
			if (str[i + 1] == L'\n')
			{
				i++;
			}
			f = true;
		}
		else if (c == L'\n')
		{
			f = true;
		}

		if (f)
		{
			wchar_t zero = 0;
			wchar_t *s;
			WriteBuf(b, &zero, sizeof(wchar_t));

			s = (wchar_t *)b->Buf;

			Add(o, UniCopyStr(s));

			ClearBuf(b);
		}
		else
		{
			WriteBuf(b, &c, sizeof(wchar_t));
		}
	}

	if (true)
	{
		wchar_t zero = 0;
		wchar_t *s;
		WriteBuf(b, &zero, sizeof(wchar_t));

		s = (wchar_t *)b->Buf;

		Add(o, UniCopyStr(s));

		ClearBuf(b);
	}

	FreeBuf(b);

	ret = UniListToTokenList(o);

	UniFreeStrList(o);

	return ret;
}