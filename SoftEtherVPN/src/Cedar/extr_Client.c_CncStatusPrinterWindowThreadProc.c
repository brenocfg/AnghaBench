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
struct TYPE_6__ {int /*<<< orphan*/  Session; TYPE_1__* Thread; int /*<<< orphan*/ * Sock; } ;
struct TYPE_5__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ THREAD ;
typedef  int /*<<< orphan*/  SOCK ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_2__ CNC_STATUS_PRINTER_WINDOW_PARAM ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NoticeThreadInit (TYPE_1__*) ; 
 int /*<<< orphan*/ * RecvPack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopSessionEx (int /*<<< orphan*/ ,int) ; 

void CncStatusPrinterWindowThreadProc(THREAD *thread, void *param)
{
	CNC_STATUS_PRINTER_WINDOW_PARAM *pp;
	SOCK *sock;
	PACK *p;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	pp = (CNC_STATUS_PRINTER_WINDOW_PARAM *)param;
	sock = pp->Sock;
	pp->Thread = thread;
	AddRef(pp->Thread->ref);

	NoticeThreadInit(thread);

	p = RecvPack(sock);
	if (p != NULL)
	{
		// Stop the session
		StopSessionEx(pp->Session, true);

		FreePack(p);
	}
}