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
typedef  int /*<<< orphan*/  SESSION ;

/* Variables and functions */
 int /*<<< orphan*/  UniPrint (char*,int /*<<< orphan*/ *) ; 

void CiClientStatusPrinter(SESSION *s, wchar_t *status)
{
#ifdef	OS_WIN32
	ACCOUNT *a;
	// Validate arguments
	if (s == NULL || status == NULL)
	{
		return;
	}

	a = s->Account;
	if (a == NULL)
	{
		return;
	}

	if (UniStrCmpi(status, L"init") == 0)
	{
		if (a->StatusWindow == NULL && s->Win32HideConnectWindow == false)
		{
			a->StatusWindow = CncStatusPrinterWindowStart(s);
		}
	}
	else if (UniStrCmpi(status, L"free") == 0)
	{
		if (a->StatusWindow != NULL)
		{
			CncStatusPrinterWindowStop(a->StatusWindow);
			a->StatusWindow = NULL;
		}
	}
	else
	{
		if (a->StatusWindow != NULL)
		{
			CncStatusPrinterWindowPrint(a->StatusWindow, status);
		}
	}
#else	// OS_WIN32
	UniPrint(L"Status: %s\n", status);
#endif	// OS_WIN32
}