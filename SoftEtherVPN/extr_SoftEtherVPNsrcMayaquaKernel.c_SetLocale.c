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
typedef  int /*<<< orphan*/  LOCALE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int LoadLocale (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_locale ; 
 int /*<<< orphan*/ * default_locale_str ; 

void SetLocale(wchar_t *str)
{
	wchar_t *set_locale_str;
	LOCALE tmp;

	if (str != NULL)
	{
		set_locale_str = str;
	}
	else
	{
		set_locale_str = default_locale_str;
	}

	if (LoadLocale(&tmp, set_locale_str) == false)
	{
		if (LoadLocale(&tmp, default_locale_str) == false)
		{
			return;
		}
	}

	Copy(&current_locale, &tmp, sizeof(LOCALE));
}