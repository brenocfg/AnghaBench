#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tsk; } ;
struct kiocb {TYPE_1__ ki_obj; } ;

/* Variables and functions */
 scalar_t__ is_sync_kiocb (struct kiocb*) ; 
 int /*<<< orphan*/  kiocbSetKicked (struct kiocb*) ; 
 int /*<<< orphan*/  try_queue_kicked_iocb (struct kiocb*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void kick_iocb(struct kiocb *iocb)
{
	/* sync iocbs are easy: they can only ever be executing from a 
	 * single context. */
	if (is_sync_kiocb(iocb)) {
		kiocbSetKicked(iocb);
	        wake_up_process(iocb->ki_obj.tsk);
		return;
	}

	try_queue_kicked_iocb(iocb);
}