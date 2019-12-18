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
struct macvtap_queue {int dummy; } ;
struct kiocb {struct file* ki_filp; } ;
struct iovec {int dummy; } ;
struct file {int f_flags; struct macvtap_queue* private_data; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOLINK ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  iov_length (struct iovec const*,unsigned long) ; 
 int /*<<< orphan*/  macvtap_get_user (struct macvtap_queue*,int /*<<< orphan*/ *,struct iovec const*,int /*<<< orphan*/ ,unsigned long,int) ; 

__attribute__((used)) static ssize_t macvtap_aio_write(struct kiocb *iocb, const struct iovec *iv,
				 unsigned long count, loff_t pos)
{
	struct file *file = iocb->ki_filp;
	ssize_t result = -ENOLINK;
	struct macvtap_queue *q = file->private_data;

	result = macvtap_get_user(q, NULL, iv, iov_length(iv, count), count,
				  file->f_flags & O_NONBLOCK);
	return result;
}