#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UINT ;

/* Variables and functions */
 int /*<<< orphan*/  CalcStrToUni (char*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 scalar_t__ Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WuUniReplace (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void WuUniStrReplace(wchar_t **buf, wchar_t *from, char *to)
{
	UINT unisize;
	wchar_t *tmp;

	if(buf == NULL || *buf == NULL || from == NULL || to == NULL)
	{
		return;
	}

	unisize = CalcStrToUni(to);
	tmp = (wchar_t*)Malloc(unisize);
	StrToUni(tmp, unisize, to);
	WuUniReplace(buf, from, tmp);
	Free(tmp);
}