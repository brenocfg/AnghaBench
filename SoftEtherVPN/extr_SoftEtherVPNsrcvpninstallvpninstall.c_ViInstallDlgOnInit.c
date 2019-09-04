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
struct TYPE_3__ {int /*<<< orphan*/ * hWnd; } ;
typedef  TYPE_1__ VI_INSTALL_DLG ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  DlgFont (int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 scalar_t__ IDCANCEL ; 
 int /*<<< orphan*/  IDI_MAIN ; 
 scalar_t__ IDS_DLG_TITLE ; 
 scalar_t__ IDS_INSTALL_CANCEL ; 
 scalar_t__ IDS_INSTALL_DLG__STATUS_INIT ; 
 int /*<<< orphan*/  P_PROGRESS ; 
 scalar_t__ S_STATUS ; 
 scalar_t__ S_TITLE ; 
 int /*<<< orphan*/  SetIcon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRange (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetText (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTimer (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _U (scalar_t__) ; 
 scalar_t__ skip ; 

void ViInstallDlgOnInit(HWND hWnd, VI_INSTALL_DLG *d)
{
	// Validate arguments
	if (hWnd == NULL || d == NULL)
	{
		return;
	}

	d->hWnd = hWnd;

	SetIcon(hWnd, 0, IDI_MAIN);

	SetText(hWnd, 0, _U(IDS_DLG_TITLE+skip));
	SetText(hWnd, S_TITLE, _U(IDS_DLG_TITLE+skip));

	SetText(hWnd, S_STATUS, _U(IDS_INSTALL_DLG__STATUS_INIT+skip));
	SetText(hWnd, IDCANCEL, _U(IDS_INSTALL_CANCEL+skip));

	DlgFont(hWnd, S_TITLE+skip, 12, true);
	SetRange(hWnd, P_PROGRESS, 0, 100);
	SetPos(hWnd, P_PROGRESS, 0);

	SetTimer(hWnd, 1, 22, NULL);
}