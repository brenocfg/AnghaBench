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
 scalar_t__ INFINITE ; 
 scalar_t__ UniIsEmptyStr (int /*<<< orphan*/ *) ; 
 scalar_t__ UniSearchStrEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bool UniInStrEx(wchar_t *str, wchar_t *keyword, bool case_sensitive)
{
	// Validate arguments
	if (UniIsEmptyStr(str) || UniIsEmptyStr(keyword))
	{
		return false;
	}

	if (UniSearchStrEx(str, keyword, 0, case_sensitive) == INFINITE)
	{
		return false;
	}

	return true;
}