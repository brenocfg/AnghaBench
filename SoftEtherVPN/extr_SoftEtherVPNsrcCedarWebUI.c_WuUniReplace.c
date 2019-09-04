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
 int UniCalcReplaceStrEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UniReplaceStr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void WuUniReplace(wchar_t **buf, wchar_t *from, wchar_t *to)
{
	UINT dstsize;
	wchar_t *oldbuf;

	if(buf == NULL || from == NULL || to == NULL)
	{
		return;
	}

	oldbuf = *buf;

	dstsize = (UniCalcReplaceStrEx(*buf, from, to, true) + 1) * sizeof(wchar_t);
	*buf = (wchar_t*)Malloc(dstsize);
	UniReplaceStr(*buf, dstsize, oldbuf, from, to);
	Free(oldbuf);
}