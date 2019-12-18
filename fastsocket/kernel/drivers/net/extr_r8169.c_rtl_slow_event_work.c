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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct rtl8169_private {int event_slow; int mac_version; int /*<<< orphan*/  mmio_addr; TYPE_1__ wk; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int LinkChg ; 
 int /*<<< orphan*/  RTL_FLAG_TASK_RESET_PENDING ; 
#define  RTL_GIGA_MAC_VER_11 128 
 int RxFIFOOver ; 
 int SYSErr ; 
 int /*<<< orphan*/  __rtl8169_check_link_status (struct net_device*,struct rtl8169_private*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  rtl8169_pcierr_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  rtl_ack_events (struct rtl8169_private*,int) ; 
 int rtl_get_events (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_irq_enable_all (struct rtl8169_private*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void rtl_slow_event_work(struct rtl8169_private *tp)
{
	struct net_device *dev = tp->dev;
	u16 status;

	status = rtl_get_events(tp) & tp->event_slow;
	rtl_ack_events(tp, status);

	if (unlikely(status & RxFIFOOver)) {
		switch (tp->mac_version) {
		/* Work around for rx fifo overflow */
		case RTL_GIGA_MAC_VER_11:
			netif_stop_queue(dev);
			/* XXX - Hack alert. See rtl_task(). */
			set_bit(RTL_FLAG_TASK_RESET_PENDING, tp->wk.flags);
		default:
			break;
		}
	}

	if (unlikely(status & SYSErr))
		rtl8169_pcierr_interrupt(dev);

	if (status & LinkChg)
		__rtl8169_check_link_status(dev, tp, tp->mmio_addr, true);

	rtl_irq_enable_all(tp);
}