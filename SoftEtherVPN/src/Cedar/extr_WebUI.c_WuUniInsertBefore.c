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
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 scalar_t__ Malloc (int) ; 
 int /*<<< orphan*/  UniStrCat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int UniStrLen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WuUniReplace (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void WuUniInsertBefore(wchar_t **buf, wchar_t *insert, wchar_t *before)
{
	UINT tmpsize;
	wchar_t *tmp;

	if(buf == NULL || insert == NULL || before == NULL)
	{
		return;
	}

	tmpsize = (UniStrLen(insert)+UniStrLen(before)+1)*sizeof(wchar_t);
	tmp = (wchar_t*)Malloc(tmpsize);
	UniStrCpy(tmp, tmpsize, insert);
	UniStrCat(tmp, tmpsize, before);
	WuUniReplace(buf, before, tmp);
	Free(tmp);
}