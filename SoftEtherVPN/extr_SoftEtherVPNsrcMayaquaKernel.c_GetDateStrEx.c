#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/ * DayOfWeek; int /*<<< orphan*/  DayStr; int /*<<< orphan*/  MonthStr; int /*<<< orphan*/  YearStr; } ;
struct TYPE_6__ {size_t wDayOfWeek; int /*<<< orphan*/  wDay; int /*<<< orphan*/  wMonth; int /*<<< orphan*/  wYear; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  TYPE_2__ LOCALE ;

/* Variables and functions */
 scalar_t__ SE_LANG_CHINESE_ZH ; 
 scalar_t__ SE_LANG_JAPANESE ; 
 int /*<<< orphan*/  UniFormat (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ _GETLANG () ; 
 TYPE_2__ current_locale ; 

void GetDateStrEx(wchar_t *str, UINT size, SYSTEMTIME *st, LOCALE *locale)
{
	wchar_t *tag = L"%04u%s%02u%s%02u%s (%s)";
	// Validate arguments
	if (str == NULL || st == NULL)
	{
		return;
	}

	if (_GETLANG() == SE_LANG_JAPANESE || _GETLANG() == SE_LANG_CHINESE_ZH)
	{
		tag = L"%4u%s%2u%s%2u%s(%s)";
	}

	locale = (locale != NULL ? locale : &current_locale);
	UniFormat(str, size,
		tag,
		st->wYear, locale->YearStr,
		st->wMonth, locale->MonthStr,
		st->wDay, locale->DayStr,
		locale->DayOfWeek[st->wDayOfWeek]);
}