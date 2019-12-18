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
struct il_sleep_notification {int /*<<< orphan*/  pm_wakeup_src; int /*<<< orphan*/  pm_sleep_mode; } ;
struct TYPE_2__ {struct il_sleep_notification sleep_notif; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_RX (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

void
il_hdl_pm_sleep(struct il_priv *il, struct il_rx_buf *rxb)
{
#ifdef CONFIG_IWLEGACY_DEBUG
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_sleep_notification *sleep = &(pkt->u.sleep_notif);
	D_RX("sleep mode: %d, src: %d\n",
	     sleep->pm_sleep_mode, sleep->pm_wakeup_src);
#endif
}