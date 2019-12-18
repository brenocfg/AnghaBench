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
struct vhost_poll {int /*<<< orphan*/  work; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  vhost_work_flush (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vhost_poll_flush(struct vhost_poll *poll)
{
	vhost_work_flush(poll->dev, &poll->work);
}