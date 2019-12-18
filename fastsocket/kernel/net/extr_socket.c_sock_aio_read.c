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
struct sock_iocb {int /*<<< orphan*/  async_msg; } ;
struct kiocb {scalar_t__ ki_left; int /*<<< orphan*/  ki_filp; } ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ESPIPE ; 
 struct sock_iocb* alloc_sock_iocb (struct kiocb*,struct sock_iocb*) ; 
 int /*<<< orphan*/  do_sock_read (int /*<<< orphan*/ *,struct kiocb*,int /*<<< orphan*/ ,struct iovec const*,unsigned long) ; 

ssize_t sock_aio_read(struct kiocb *iocb, const struct iovec *iov,
				unsigned long nr_segs, loff_t pos)
{
	struct sock_iocb siocb, *x;

	if (pos != 0)
		return -ESPIPE;

	if (iocb->ki_left == 0)	/* Match SYS5 behaviour */
		return 0;


	x = alloc_sock_iocb(iocb, &siocb);
	if (!x)
		return -ENOMEM;
	return do_sock_read(&x->async_msg, iocb, iocb->ki_filp, iov, nr_segs);
}