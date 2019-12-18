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
struct se_device {int dummy; } ;
struct fd_dev {int /*<<< orphan*/ * fd_file; } ;

/* Variables and functions */
 struct fd_dev* FD_DEV (struct se_device*) ; 
 int /*<<< orphan*/  filp_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct fd_dev*) ; 

__attribute__((used)) static void fd_free_device(struct se_device *dev)
{
	struct fd_dev *fd_dev = FD_DEV(dev);

	if (fd_dev->fd_file) {
		filp_close(fd_dev->fd_file, NULL);
		fd_dev->fd_file = NULL;
	}

	kfree(fd_dev);
}