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
struct kiocb {int /*<<< orphan*/  ki_left; TYPE_1__* ki_filp; } ;
struct iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
struct ep_data {int /*<<< orphan*/  desc; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {struct ep_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ copy_from_user (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ep_aio_rwtail (struct kiocb*,char*,size_t,struct ep_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_endpoint_dir_in (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
ep_aio_write(struct kiocb *iocb, const struct iovec *iov,
		unsigned long nr_segs, loff_t o)
{
	struct ep_data		*epdata = iocb->ki_filp->private_data;
	char			*buf;
	size_t			len = 0;
	int			i = 0;

	if (unlikely(!usb_endpoint_dir_in(&epdata->desc)))
		return -EINVAL;

	buf = kmalloc(iocb->ki_left, GFP_KERNEL);
	if (unlikely(!buf))
		return -ENOMEM;

	for (i=0; i < nr_segs; i++) {
		if (unlikely(copy_from_user(&buf[len], iov[i].iov_base,
				iov[i].iov_len) != 0)) {
			kfree(buf);
			return -EFAULT;
		}
		len += iov[i].iov_len;
	}
	return ep_aio_rwtail(iocb, buf, len, epdata, NULL, 0);
}