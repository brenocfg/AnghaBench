#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {int /*<<< orphan*/  Unknown; } ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  TYPE_1__ LOCALE ;

/* Variables and functions */
 int /*<<< orphan*/  GetDateStrEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ LocalToSystem64 (int /*<<< orphan*/ ) ; 
 scalar_t__ SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT64ToSystem (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ current_locale ; 

void GetDateStrEx64(wchar_t *str, UINT size, UINT64 sec64, LOCALE *locale)
{
	SYSTEMTIME st;
	if (locale == NULL)
	{
		locale = &current_locale;
	}
	if (sec64 == 0 || SystemToLocal64(sec64) == 0 || LocalToSystem64(sec64) == 0)
	{
		UniStrCpy(str, size, locale->Unknown);
		return;
	}
	UINT64ToSystem(&st, sec64);
	GetDateStrEx(str, size, &st, locale);
}