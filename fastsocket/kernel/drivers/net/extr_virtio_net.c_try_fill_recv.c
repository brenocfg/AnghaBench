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
struct virtnet_info {scalar_t__ num; scalar_t__ max; int /*<<< orphan*/  rvq; scalar_t__ big_packets; scalar_t__ mergeable_rx_bufs; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int add_recvbuf_big (struct virtnet_info*,int /*<<< orphan*/ ) ; 
 int add_recvbuf_mergeable (struct virtnet_info*,int /*<<< orphan*/ ) ; 
 int add_recvbuf_small (struct virtnet_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  virtqueue_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool try_fill_recv(struct virtnet_info *vi, gfp_t gfp)
{
	int err;
	bool oom;

	do {
		if (vi->mergeable_rx_bufs)
			err = add_recvbuf_mergeable(vi, gfp);
		else if (vi->big_packets)
			err = add_recvbuf_big(vi, gfp);
		else
			err = add_recvbuf_small(vi, gfp);

		oom = err == -ENOMEM;
		if (err < 0)
			break;
		++vi->num;
	} while (err > 0);
	if (unlikely(vi->num > vi->max))
		vi->max = vi->num;
	virtqueue_kick(vi->rvq);
	return !oom;
}