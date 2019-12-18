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
struct rtl8169_private {int /*<<< orphan*/  mmio_addr; int /*<<< orphan*/  napi; scalar_t__ RxDescArray; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NUM_RX_DESC ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  rtl8169_check_link_status (struct net_device*,struct rtl8169_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8169_hw_reset (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169_init_ring_indexes (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169_mark_to_asic (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8169_tx_clear (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start (struct net_device*) ; 
 int /*<<< orphan*/  rx_buf_sz ; 
 int /*<<< orphan*/  synchronize_sched () ; 

__attribute__((used)) static void rtl_reset_work(struct rtl8169_private *tp)
{
	struct net_device *dev = tp->dev;
	int i;

	napi_disable(&tp->napi);
	netif_stop_queue(dev);
	synchronize_sched();

	rtl8169_hw_reset(tp);

	for (i = 0; i < NUM_RX_DESC; i++)
		rtl8169_mark_to_asic(tp->RxDescArray + i, rx_buf_sz);

	rtl8169_tx_clear(tp);
	rtl8169_init_ring_indexes(tp);

	napi_enable(&tp->napi);
	rtl_hw_start(dev);
	netif_wake_queue(dev);
	rtl8169_check_link_status(dev, tp, tp->mmio_addr);
}