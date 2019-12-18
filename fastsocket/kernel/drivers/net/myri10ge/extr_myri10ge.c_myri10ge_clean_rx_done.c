#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct net_device {int features; } ;
struct TYPE_7__ {scalar_t__ fill_cnt; scalar_t__ cnt; } ;
struct TYPE_6__ {unsigned long rx_packets; unsigned long rx_bytes; } ;
struct myri10ge_rx_done {int idx; int cnt; int /*<<< orphan*/  lro_mgr; TYPE_1__* entry; } ;
struct myri10ge_slice_state {TYPE_3__ rx_big; TYPE_3__ rx_small; TYPE_2__ stats; struct myri10ge_priv* mgp; struct myri10ge_rx_done rx_done; } ;
struct myri10ge_priv {scalar_t__ small_bytes; scalar_t__ big_bytes; int max_intr_slots; struct net_device* dev; } ;
typedef  int /*<<< orphan*/  __wsum ;
struct TYPE_5__ {scalar_t__ length; int /*<<< orphan*/  checksum; } ;

/* Variables and functions */
 scalar_t__ MXGEFW_PAD ; 
 int NETIF_F_LRO ; 
 int /*<<< orphan*/  csum_unfold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lro_flush_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  myri10ge_alloc_rx_pages (struct myri10ge_priv*,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ myri10ge_fill_thresh ; 
 unsigned long myri10ge_rx_done (struct myri10ge_slice_state*,TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (scalar_t__) ; 

__attribute__((used)) static inline int
myri10ge_clean_rx_done(struct myri10ge_slice_state *ss, int budget)
{
	struct myri10ge_rx_done *rx_done = &ss->rx_done;
	struct myri10ge_priv *mgp = ss->mgp;
	struct net_device *netdev = mgp->dev;
	unsigned long rx_bytes = 0;
	unsigned long rx_packets = 0;
	unsigned long rx_ok;

	int idx = rx_done->idx;
	int cnt = rx_done->cnt;
	int work_done = 0;
	u16 length;
	__wsum checksum;

	while (rx_done->entry[idx].length != 0 && work_done < budget) {
		length = ntohs(rx_done->entry[idx].length);
		rx_done->entry[idx].length = 0;
		checksum = csum_unfold(rx_done->entry[idx].checksum);
		if (length <= mgp->small_bytes)
			rx_ok = myri10ge_rx_done(ss, &ss->rx_small,
						 mgp->small_bytes,
						 length, checksum);
		else
			rx_ok = myri10ge_rx_done(ss, &ss->rx_big,
						 mgp->big_bytes,
						 length, checksum);
		rx_packets += rx_ok;
		rx_bytes += rx_ok * (unsigned long)length;
		cnt++;
		idx = cnt & (mgp->max_intr_slots - 1);
		work_done++;
	}
	rx_done->idx = idx;
	rx_done->cnt = cnt;
	ss->stats.rx_packets += rx_packets;
	ss->stats.rx_bytes += rx_bytes;

	if (netdev->features & NETIF_F_LRO)
		lro_flush_all(&rx_done->lro_mgr);

	/* restock receive rings if needed */
	if (ss->rx_small.fill_cnt - ss->rx_small.cnt < myri10ge_fill_thresh)
		myri10ge_alloc_rx_pages(mgp, &ss->rx_small,
					mgp->small_bytes + MXGEFW_PAD, 0);
	if (ss->rx_big.fill_cnt - ss->rx_big.cnt < myri10ge_fill_thresh)
		myri10ge_alloc_rx_pages(mgp, &ss->rx_big, mgp->big_bytes, 0);

	return work_done;
}