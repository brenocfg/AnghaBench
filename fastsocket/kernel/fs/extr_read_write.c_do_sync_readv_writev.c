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
struct kiocb {size_t ki_left; size_t ki_nbytes; int /*<<< orphan*/  ki_pos; } ;
struct iovec {int dummy; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  (* iov_fn_t ) (struct kiocb*,struct iovec const*,unsigned long,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  EIOCBQUEUED ; 
 int /*<<< orphan*/  EIOCBRETRY ; 
 int /*<<< orphan*/  init_sync_kiocb (struct kiocb*,struct file*) ; 
 int /*<<< orphan*/  wait_on_retry_sync_kiocb (struct kiocb*) ; 
 int /*<<< orphan*/  wait_on_sync_kiocb (struct kiocb*) ; 

ssize_t do_sync_readv_writev(struct file *filp, const struct iovec *iov,
		unsigned long nr_segs, size_t len, loff_t *ppos, iov_fn_t fn)
{
	struct kiocb kiocb;
	ssize_t ret;

	init_sync_kiocb(&kiocb, filp);
	kiocb.ki_pos = *ppos;
	kiocb.ki_left = len;
	kiocb.ki_nbytes = len;

	for (;;) {
		ret = fn(&kiocb, iov, nr_segs, kiocb.ki_pos);
		if (ret != -EIOCBRETRY)
			break;
		wait_on_retry_sync_kiocb(&kiocb);
	}

	if (ret == -EIOCBQUEUED)
		ret = wait_on_sync_kiocb(&kiocb);
	*ppos = kiocb.ki_pos;
	return ret;
}