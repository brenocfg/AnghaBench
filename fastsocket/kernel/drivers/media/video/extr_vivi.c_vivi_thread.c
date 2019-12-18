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
struct vivi_fh {struct vivi_dev* dev; } ;
struct vivi_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (struct vivi_dev*,int,char*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  vivi_sleep (struct vivi_fh*) ; 

__attribute__((used)) static int vivi_thread(void *data)
{
	struct vivi_fh  *fh = data;
	struct vivi_dev *dev = fh->dev;

	dprintk(dev, 1, "thread started\n");

	set_freezable();

	for (;;) {
		vivi_sleep(fh);

		if (kthread_should_stop())
			break;
	}
	dprintk(dev, 1, "thread: exit\n");
	return 0;
}