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
struct spider_net_card {int /*<<< orphan*/  aneg_timer; int /*<<< orphan*/  medium; scalar_t__ aneg_count; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM54XX_COPPER ; 
 scalar_t__ SPIDER_NET_ANEG_TIMER ; 
 int /*<<< orphan*/  SPIDER_NET_GMACINTEN ; 
 int /*<<< orphan*/  SPIDER_NET_GMACST ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct spider_net_card* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spider_net_read_reg (struct spider_net_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spider_net_setup_aneg (struct spider_net_card*) ; 
 int /*<<< orphan*/  spider_net_write_reg (struct spider_net_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
spider_net_link_reset(struct net_device *netdev)
{

	struct spider_net_card *card = netdev_priv(netdev);

	del_timer_sync(&card->aneg_timer);

	/* clear interrupt, block further interrupts */
	spider_net_write_reg(card, SPIDER_NET_GMACST,
			     spider_net_read_reg(card, SPIDER_NET_GMACST));
	spider_net_write_reg(card, SPIDER_NET_GMACINTEN, 0);

	/* reset phy and setup aneg */
	card->aneg_count = 0;
	card->medium = BCM54XX_COPPER;
	spider_net_setup_aneg(card);
	mod_timer(&card->aneg_timer, jiffies + SPIDER_NET_ANEG_TIMER);

}