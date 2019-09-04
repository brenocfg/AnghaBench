#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Session; } ;
struct TYPE_3__ {int UserSelected; int /*<<< orphan*/  Expired; int /*<<< orphan*/  ServerX; TYPE_2__* Connection; int /*<<< orphan*/  (* CheckCertProc ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  Ok; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ CHECK_CERT_THREAD_PROC ;

/* Variables and functions */
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ClientCheckServerCertThread(THREAD *thread, void *param)
{
	CHECK_CERT_THREAD_PROC *p = (CHECK_CERT_THREAD_PROC *)param;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	// Notify the completion of initialization
	NoticeThreadInit(thread);

	// Query for the selection to the user
	p->Ok = p->CheckCertProc(p->Connection->Session, p->Connection, p->ServerX, &p->Expired);
	p->UserSelected = true;
}