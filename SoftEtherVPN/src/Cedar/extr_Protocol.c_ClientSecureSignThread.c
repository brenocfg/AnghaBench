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
struct TYPE_3__ {int UserFinished; int /*<<< orphan*/  SecureSign; TYPE_2__* Connection; int /*<<< orphan*/  (* SecureSignProc ) (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  Ok; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_1__ SECURE_SIGN_THREAD_PROC ;

/* Variables and functions */
 int /*<<< orphan*/  NoticeThreadInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

void ClientSecureSignThread(THREAD *thread, void *param)
{
	SECURE_SIGN_THREAD_PROC *p = (SECURE_SIGN_THREAD_PROC *)param;
	// Validate arguments
	if (thread == NULL || param == NULL)
	{
		return;
	}

	NoticeThreadInit(thread);

	p->Ok = p->SecureSignProc(p->Connection->Session, p->Connection, p->SecureSign);
	p->UserFinished = true;
}