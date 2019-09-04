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

/* Variables and functions */
 char* CopyUniToStr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Prompt (int /*<<< orphan*/ *) ; 

char *PromptA(wchar_t *prompt_str)
{
	wchar_t *str = Prompt(prompt_str);

	if (str == NULL)
	{
		return NULL;
	}
	else
	{
		char *ret = CopyUniToStr(str);

		Free(str);
		return ret;
	}
}