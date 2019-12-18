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
struct inode {int dummy; } ;
struct file {int f_flags; TYPE_1__* private_data; } ;
struct TYPE_3__ {scalar_t__ data_pool_bytes_allocated; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int ENODEV ; 
 int O_NDELAY ; 
 TYPE_1__* sep_dev ; 
 int /*<<< orphan*/  sep_event ; 
 scalar_t__ sep_try_open (TYPE_1__*) ; 
 scalar_t__ wait_event_interruptible (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sep_open(struct inode *inode, struct file *filp)
{
	if (sep_dev == NULL)
		return -ENODEV;

	/* check the blocking mode */
	if (filp->f_flags & O_NDELAY) {
		if (sep_try_open(sep_dev) == 0)
			return -EAGAIN;
	} else
		if (wait_event_interruptible(sep_event, sep_try_open(sep_dev)) < 0)
			return -EINTR;

	/* Bind to the device, we only have one which makes it easy */
	filp->private_data = sep_dev;
	/* release data pool allocations */
	sep_dev->data_pool_bytes_allocated = 0;
	return 0;
}