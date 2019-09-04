#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_3__ {scalar_t__ Halt; } ;
typedef  TYPE_1__ VI_INSTALL_DLG ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  SMTO_BLOCK ; 
 int /*<<< orphan*/  SendMessageTimeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM_VI_SETTEXT ; 

void ViInstallDlgSetText(VI_INSTALL_DLG *d, HWND hWnd, UINT id, wchar_t *text)
{
	DWORD value = 0;
	// Validate arguments
	if (d == NULL)
	{
		return;
	}

	if (d->Halt)
	{
		return;
	}

	SendMessageTimeout(hWnd, WM_VI_SETTEXT, id, (LPARAM)text, SMTO_BLOCK, 200, &value);
}