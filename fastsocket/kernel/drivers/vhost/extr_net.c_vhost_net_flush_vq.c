#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* vqs; } ;
struct vhost_net {TYPE_2__ dev; int /*<<< orphan*/ * poll; } ;
struct TYPE_3__ {int /*<<< orphan*/  poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  vhost_poll_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vhost_net_flush_vq(struct vhost_net *n, int index)
{
	vhost_poll_flush(n->poll + index);
	vhost_poll_flush(&n->dev.vqs[index].poll);
}