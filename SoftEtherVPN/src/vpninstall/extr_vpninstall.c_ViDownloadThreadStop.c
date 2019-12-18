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
struct TYPE_3__ {int DownloadStarted; int Halt; int /*<<< orphan*/  DownloadThread; } ;
typedef  TYPE_1__ VI_INSTALL_DLG ;

/* Variables and functions */
 int /*<<< orphan*/  DoEvents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 scalar_t__ WaitThread (int /*<<< orphan*/ ,int) ; 

void ViDownloadThreadStop(VI_INSTALL_DLG *d)
{
	// Validate arguments
	if (d == NULL)
	{
		return;
	}

	if (d->DownloadStarted == false)
	{
		return;
	}

	d->DownloadStarted = false;
	d->Halt = true;

	while (true)
	{
		if (WaitThread(d->DownloadThread, 50))
		{
			break;
		}

		DoEvents(NULL);
	}

	ReleaseThread(d->DownloadThread);
}