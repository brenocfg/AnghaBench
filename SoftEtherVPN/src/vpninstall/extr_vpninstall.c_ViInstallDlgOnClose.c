#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int DialogCanceling; scalar_t__ NoClose; } ;
typedef  TYPE_1__ VI_INSTALL_DLG ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  Disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndDialog (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDCANCEL ; 
 int /*<<< orphan*/  ViDownloadThreadStop (TYPE_1__*) ; 

void ViInstallDlgOnClose(HWND hWnd, VI_INSTALL_DLG *d)
{
	// Validate arguments
	if (hWnd == NULL || d == NULL)
	{
		return;
	}

	if (d->DialogCanceling)
	{
		return;
	}
	if (d->NoClose)
	{
		return;
	}

	d->DialogCanceling = true;

	// Disable the cancel button
	Disable(hWnd, IDCANCEL);

	// Stop the download thread if it runs
	ViDownloadThreadStop(d);

	// Exit the dialog
	EndDialog(hWnd, 0);
}