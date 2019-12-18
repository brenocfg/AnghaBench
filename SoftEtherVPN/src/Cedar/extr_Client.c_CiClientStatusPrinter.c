#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_6__ {int /*<<< orphan*/ * StatusWindow; } ;
struct TYPE_5__ {int Win32HideConnectWindow; TYPE_2__* Account; } ;
typedef  TYPE_1__ SESSION ;
typedef  TYPE_2__ ACCOUNT ;

/* Variables and functions */
 int /*<<< orphan*/  CncStatusPrinterWindowPrint (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CncStatusPrinterWindowStart (TYPE_1__*) ; 
 int /*<<< orphan*/  CncStatusPrinterWindowStop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniPrint (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ UniStrCmpi (int /*<<< orphan*/ *,char*) ; 

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