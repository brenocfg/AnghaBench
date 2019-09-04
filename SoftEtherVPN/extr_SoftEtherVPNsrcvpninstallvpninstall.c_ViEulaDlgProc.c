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
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  Center (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DlgFont (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EM_SETSEL ; 
 int E_EULA ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Focus (int /*<<< orphan*/ *,int) ; 
#define  IDCANCEL 132 
#define  IDOK 131 
 scalar_t__ IDS_DLG_TITLE ; 
 scalar_t__ IDS_EULA_AGREE ; 
 scalar_t__ IDS_EULA_DISAGREE ; 
 scalar_t__ IDS_EULA_NOTICE1 ; 
 scalar_t__ IDS_EULA_NOTICE2 ; 
 scalar_t__ IDS_EULA_NOTICE3 ; 
 int S_BOLD ; 
 int S_EULA_NOTICE1 ; 
 int S_EULA_NOTICE3 ; 
 int /*<<< orphan*/  SendMsg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetText (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
#define  WM_CLOSE 130 
#define  WM_COMMAND 129 
#define  WM_INITDIALOG 128 
 int /*<<< orphan*/ * _U (scalar_t__) ; 
 scalar_t__ skip ; 

UINT ViEulaDlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, void *param)
{
	wchar_t *text = (wchar_t *)param;
	// Validate arguments
	if (hWnd == NULL)
	{
		return 0;
	}

	switch (msg)
	{
	case WM_INITDIALOG:
		SetText(hWnd, 0, _U(IDS_DLG_TITLE+skip));
		SetText(hWnd, S_EULA_NOTICE1, _U(IDS_EULA_NOTICE1+skip));
		SetText(hWnd, S_BOLD, _U(IDS_EULA_NOTICE2+skip));
		SetText(hWnd, S_EULA_NOTICE3, _U(IDS_EULA_NOTICE3+skip));
		SetText(hWnd, IDOK, _U(IDS_EULA_AGREE+skip));
		SetText(hWnd, IDCANCEL, _U(IDS_EULA_DISAGREE+skip));

		DlgFont(hWnd, S_BOLD, 0, true);
		SetText(hWnd, E_EULA, text);
		Focus(hWnd, E_EULA);
		SendMsg(hWnd, E_EULA, EM_SETSEL, 0, 0);
		Center(hWnd);
		break;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			EndDialog(hWnd, 1);
			break;

		case IDCANCEL:
			Close(hWnd);
			break;
		}
		break;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	}

	return 0;
}