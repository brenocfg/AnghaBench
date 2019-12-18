#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  Thread; } ;
struct TYPE_7__ {scalar_t__ Param; } ;
typedef  TYPE_1__ SOCK ;
typedef  TYPE_2__ CNC_STATUS_PRINTER_WINDOW_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  Disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CncStatusPrinterWindowStop(SOCK *s)
{
	CNC_STATUS_PRINTER_WINDOW_PARAM *param;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	param = (CNC_STATUS_PRINTER_WINDOW_PARAM *)s->Param;

	// Disconnect the client socket 
	Disconnect(s);

	// Terminate the thread
	WaitThread(param->Thread, INFINITE);
	ReleaseThread(param->Thread);

	Free(param);
	ReleaseSock(s);
}