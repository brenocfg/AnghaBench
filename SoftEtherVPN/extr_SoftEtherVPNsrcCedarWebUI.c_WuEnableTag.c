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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int MAX_SIZE ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WuUniReplace (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void WuEnableTag(wchar_t **buf, wchar_t *keyword)
{
	wchar_t tmp[MAX_SIZE];
	if(buf == NULL || keyword == NULL)
	{
		return;
	}

	UniFormat(tmp, sizeof(tmp), L"!--%s", keyword);
	WuUniReplace(buf, tmp, L"");

	UniFormat(tmp, sizeof(tmp), L"%s--", keyword);
	WuUniReplace(buf, tmp, L"");
	return;
}