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
struct kiocb {int /*<<< orphan*/  ki_left; int /*<<< orphan*/  ki_retry; TYPE_1__* ki_filp; } ;
struct iovec {int dummy; } ;
struct ep_data {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct ep_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ep_aio_read_retry ; 
 int /*<<< orphan*/  ep_aio_rwtail (struct kiocb*,char*,int /*<<< orphan*/ ,struct ep_data*,struct iovec const*,unsigned long) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int usb_endpoint_dir_in (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
ep_aio_read(struct kiocb *iocb, const struct iovec *iov,
		unsigned long nr_segs, loff_t o)
{
	struct ep_data		*epdata = iocb->ki_filp->private_data;
	char			*buf;

	if (unlikely(usb_endpoint_dir_in(&epdata->desc)))
		return -EINVAL;

	buf = kmalloc(iocb->ki_left, GFP_KERNEL);
	if (unlikely(!buf))
		return -ENOMEM;

	iocb->ki_retry = ep_aio_read_retry;
	return ep_aio_rwtail(iocb, buf, iocb->ki_left, epdata, iov, nr_segs);
}