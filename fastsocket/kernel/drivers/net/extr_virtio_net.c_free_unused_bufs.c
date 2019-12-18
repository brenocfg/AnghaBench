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
struct virtnet_info {scalar_t__ num; scalar_t__ big_packets; scalar_t__ mergeable_rx_bufs; int /*<<< orphan*/  rvq; int /*<<< orphan*/  svq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dev_kfree_skb (void*) ; 
 int /*<<< orphan*/  give_pages (struct virtnet_info*,void*) ; 
 void* virtqueue_detach_unused_buf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_unused_bufs(struct virtnet_info *vi)
{
	void *buf;
	while (1) {
		buf = virtqueue_detach_unused_buf(vi->svq);
		if (!buf)
			break;
		dev_kfree_skb(buf);
	}
	while (1) {
		buf = virtqueue_detach_unused_buf(vi->rvq);
		if (!buf)
			break;
		if (vi->mergeable_rx_bufs || vi->big_packets)
			give_pages(vi, buf);
		else
			dev_kfree_skb(buf);
		--vi->num;
	}
	BUG_ON(vi->num != 0);
}