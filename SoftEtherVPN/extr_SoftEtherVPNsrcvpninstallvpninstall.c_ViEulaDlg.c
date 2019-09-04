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
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  D_EULA ; 
 scalar_t__ Dialog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ViEulaDlgProc ; 

bool ViEulaDlg(HWND hWnd, wchar_t *text)
{
	// Validate arguments
	if (text == NULL)
	{
		return false;
	}

	if (Dialog(hWnd, D_EULA, ViEulaDlgProc, text) == 0)
	{
		return false;
	}

	return true;
}