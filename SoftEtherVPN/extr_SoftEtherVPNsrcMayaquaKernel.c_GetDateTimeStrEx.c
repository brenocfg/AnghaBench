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
typedef  int /*<<< orphan*/  tmp2 ;
typedef  int /*<<< orphan*/  tmp1 ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  LOCALE ;

/* Variables and functions */
 int /*<<< orphan*/  GetDateStrEx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetTimeStrEx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void GetDateTimeStrEx(wchar_t *str, UINT size, SYSTEMTIME *st, LOCALE *locale)
{
	wchar_t tmp1[MAX_SIZE];
	wchar_t tmp2[MAX_SIZE];
	// Validate arguments
	if (str == NULL || st == NULL)
	{
		return;
	}

	GetDateStrEx(tmp1, sizeof(tmp1), st, locale);
	GetTimeStrEx(tmp2, sizeof(tmp2), st, locale);
	UniFormat(str, size, L"%s %s", tmp1, tmp2);
}