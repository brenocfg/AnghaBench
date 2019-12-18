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
struct TYPE_4__ {int num; } ;
struct virtqueue {TYPE_2__ vring; TYPE_1__* dev; } ;
struct net_info {int /*<<< orphan*/  tunfd; } ;
struct iovec {int dummy; } ;
struct TYPE_3__ {struct net_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_used (struct virtqueue*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 unsigned int wait_for_vq_desc (struct virtqueue*,struct iovec*,unsigned int*,unsigned int*) ; 
 scalar_t__ writev (int /*<<< orphan*/ ,struct iovec*,unsigned int) ; 

__attribute__((used)) static void net_output(struct virtqueue *vq)
{
	struct net_info *net_info = vq->dev->priv;
	unsigned int head, out, in;
	struct iovec iov[vq->vring.num];

	/* We usually wait in here for the Guest to give us a packet. */
	head = wait_for_vq_desc(vq, iov, &out, &in);
	if (in)
		errx(1, "Input buffers in net output queue?");
	/*
	 * Send the whole thing through to /dev/net/tun.  It expects the exact
	 * same format: what a coincidence!
	 */
	if (writev(net_info->tunfd, iov, out) < 0)
		errx(1, "Write to tun failed?");

	/*
	 * Done with that one; wait_for_vq_desc() will send the interrupt if
	 * all packets are processed.
	 */
	add_used(vq, head, 0);
}