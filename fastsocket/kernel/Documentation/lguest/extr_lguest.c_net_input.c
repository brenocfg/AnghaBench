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
struct TYPE_3__ {int num; } ;
struct virtqueue {scalar_t__ pending_used; TYPE_2__* dev; TYPE_1__ vring; } ;
struct net_info {int /*<<< orphan*/  tunfd; } ;
struct iovec {int dummy; } ;
struct TYPE_4__ {struct net_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_used (struct virtqueue*,unsigned int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int readv (int /*<<< orphan*/ ,struct iovec*,unsigned int) ; 
 int /*<<< orphan*/  trigger_irq (struct virtqueue*) ; 
 unsigned int wait_for_vq_desc (struct virtqueue*,struct iovec*,unsigned int*,unsigned int*) ; 
 scalar_t__ will_block (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void net_input(struct virtqueue *vq)
{
	int len;
	unsigned int head, out, in;
	struct iovec iov[vq->vring.num];
	struct net_info *net_info = vq->dev->priv;

	/*
	 * Get a descriptor to write an incoming packet into.  This will also
	 * send an interrupt if they're out of descriptors.
	 */
	head = wait_for_vq_desc(vq, iov, &out, &in);
	if (out)
		errx(1, "Output buffers in net input queue?");

	/*
	 * If it looks like we'll block reading from the tun device, send them
	 * an interrupt.
	 */
	if (vq->pending_used && will_block(net_info->tunfd))
		trigger_irq(vq);

	/*
	 * Read in the packet.  This is where we normally wait (when there's no
	 * incoming network traffic).
	 */
	len = readv(net_info->tunfd, iov, in);
	if (len <= 0)
		err(1, "Failed to read from tun.");

	/*
	 * Mark that packet buffer as used, but don't interrupt here.  We want
	 * to wait until we've done as much work as we can.
	 */
	add_used(vq, head, len);
}