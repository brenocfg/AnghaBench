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
typedef  int /*<<< orphan*/  VI_INSTALL_DLG ;
typedef  int /*<<< orphan*/ * HWND ;

/* Variables and functions */
 int /*<<< orphan*/  ViDownloadThreadStart (int /*<<< orphan*/ *) ; 

void ViInstallDlgOnStart(HWND hWnd, VI_INSTALL_DLG *d)
{
	// Validate arguments
	if (hWnd == NULL || d == NULL)
	{
		return;
	}

	// Start the download thread
	ViDownloadThreadStart(d);
}