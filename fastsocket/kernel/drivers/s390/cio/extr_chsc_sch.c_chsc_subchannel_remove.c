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
struct subchannel {int /*<<< orphan*/  dev; struct chsc_private* private; } ;
struct chsc_private {TYPE_1__* request; } ;
struct TYPE_2__ {int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  cio_disable_subchannel (struct subchannel*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct chsc_private*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int chsc_subchannel_remove(struct subchannel *sch)
{
	struct chsc_private *private;

	cio_disable_subchannel(sch);
	private = sch->private;
	sch->private = NULL;
	if (private->request) {
		complete(&private->request->completion);
		put_device(&sch->dev);
	}
	kfree(private);
	return 0;
}