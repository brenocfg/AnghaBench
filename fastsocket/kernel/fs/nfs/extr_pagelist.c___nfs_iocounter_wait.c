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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct nfs_io_counter {int /*<<< orphan*/  flags; int /*<<< orphan*/  io_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT_BIT (TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFS_IO_INPROGRESS ; 
 int /*<<< orphan*/  TASK_KILLABLE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bit_waitqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfs_wait_bit_killable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ q ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
__nfs_iocounter_wait(struct nfs_io_counter *c)
{
	wait_queue_head_t *wq = bit_waitqueue(&c->flags, NFS_IO_INPROGRESS);
	DEFINE_WAIT_BIT(q, &c->flags, NFS_IO_INPROGRESS);
	int ret = 0;

	do {
		prepare_to_wait(wq, &q.wait, TASK_KILLABLE);
		set_bit(NFS_IO_INPROGRESS, &c->flags);
		if (atomic_read(&c->io_count) == 0)
			break;
		ret = nfs_wait_bit_killable(&c->flags);
	} while (atomic_read(&c->io_count) != 0);
	finish_wait(wq, &q.wait);
	return ret;
}