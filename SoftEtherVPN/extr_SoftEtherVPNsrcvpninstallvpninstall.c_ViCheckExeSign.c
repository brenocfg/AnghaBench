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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  GetFileNameFromFilePathW (char*,int,char*) ; 
 scalar_t__ IDOK ; 
 scalar_t__ IDS_SIGN_WARNING ; 
 scalar_t__ IDS_SIGN_WARNING_TITLE ; 
 int MAX_PATH ; 
 int MB_DEFBUTTON2 ; 
 int MB_ICONEXCLAMATION ; 
 int MB_OKCANCEL ; 
 scalar_t__ MessageBoxW (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ MsCheckFileDigitalSignatureW (int /*<<< orphan*/ *,char*,int*) ; 
 char* _U (scalar_t__) ; 
 scalar_t__ skip ; 
 int /*<<< orphan*/  swprintf (char*,int,char*,char*,char*,char*) ; 

bool ViCheckExeSign(HWND hWnd, wchar_t *exew)
{
	wchar_t tmp[2048];
	bool danger = true;
	wchar_t *warningMessage = _U(IDS_SIGN_WARNING+skip);
	wchar_t *warningMessageTitle = _U(IDS_SIGN_WARNING_TITLE+skip);
	// Validate arguments
	if (hWnd == NULL || exew == NULL)
	{
		return false;
	}

	if (MsCheckFileDigitalSignatureW(hWnd, exew, &danger))
	{
		if (danger == false)
		{
			// Safe
			return true;
		}
		else
		{
			wchar_t filename[MAX_PATH];

			GetFileNameFromFilePathW(filename, sizeof(filename), exew);

			// Show the message because there is potentially dangerous
			swprintf(tmp, sizeof(tmp) / 2, warningMessage,
				filename, filename, filename);

			if (MessageBoxW(hWnd, tmp, warningMessageTitle,
				MB_OKCANCEL | MB_DEFBUTTON2 | MB_ICONEXCLAMATION) == IDOK)
			{
				return true;
			}

			return false;
		}
	}
	else
	{
		// Danger
		return false;
	}
}