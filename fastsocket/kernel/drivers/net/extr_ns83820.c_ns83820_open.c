#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_3__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct ns83820 {TYPE_1__ tx_watchdog; scalar_t__ base; scalar_t__ tx_phy_descs; scalar_t__ tx_done_idx; scalar_t__ tx_idx; int /*<<< orphan*/ * tx_descs; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int DESC_LINK ; 
 int DESC_SIZE ; 
 int HZ ; 
 int NR_TX_DESC ; 
 scalar_t__ PQCR ; 
 struct ns83820* PRIV (struct net_device*) ; 
 scalar_t__ TXDP ; 
 scalar_t__ TXDP_HI ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mod_timer (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int ns83820_setup_rx (struct net_device*) ; 
 int /*<<< orphan*/  ns83820_stop (struct net_device*) ; 
 int /*<<< orphan*/  ns83820_tx_watch ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int ns83820_open(struct net_device *ndev)
{
	struct ns83820 *dev = PRIV(ndev);
	unsigned i;
	u32 desc;
	int ret;

	dprintk("ns83820_open\n");

	writel(0, dev->base + PQCR);

	ret = ns83820_setup_rx(ndev);
	if (ret)
		goto failed;

	memset(dev->tx_descs, 0, 4 * NR_TX_DESC * DESC_SIZE);
	for (i=0; i<NR_TX_DESC; i++) {
		dev->tx_descs[(i * DESC_SIZE) + DESC_LINK]
				= cpu_to_le32(
				  dev->tx_phy_descs
				  + ((i+1) % NR_TX_DESC) * DESC_SIZE * 4);
	}

	dev->tx_idx = 0;
	dev->tx_done_idx = 0;
	desc = dev->tx_phy_descs;
	writel(0, dev->base + TXDP_HI);
	writel(desc, dev->base + TXDP);

	init_timer(&dev->tx_watchdog);
	dev->tx_watchdog.data = (unsigned long)ndev;
	dev->tx_watchdog.function = ns83820_tx_watch;
	mod_timer(&dev->tx_watchdog, jiffies + 2*HZ);

	netif_start_queue(ndev);	/* FIXME: wait for phy to come up */

	return 0;

failed:
	ns83820_stop(ndev);
	return ret;
}