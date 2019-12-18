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
 int /*<<< orphan*/ * Malloc (int) ; 
 int UniGetLine (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UniToStr (char*,int,int /*<<< orphan*/ *) ; 

bool GetLine(char *str, UINT size)
{
	bool ret;
	wchar_t *unistr;
	UINT unistr_size = (size + 1) * sizeof(wchar_t);

	unistr = Malloc(unistr_size);

	ret = UniGetLine(unistr, unistr_size);

	UniToStr(str, size, unistr);

	Free(unistr);

	return ret;
}