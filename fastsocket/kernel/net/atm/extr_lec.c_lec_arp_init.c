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
struct lec_priv {int /*<<< orphan*/  lec_arp_work; int /*<<< orphan*/  lec_arp_lock; int /*<<< orphan*/  mcast_fwds; int /*<<< orphan*/  lec_no_forward; int /*<<< orphan*/  lec_arp_empty_ones; int /*<<< orphan*/ * lec_arp_tables; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LEC_ARP_REFRESH_INTERVAL ; 
 unsigned short LEC_ARP_TABLE_SIZE ; 
 int /*<<< orphan*/  lec_arp_check_expire ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lec_arp_init(struct lec_priv *priv)
{
	unsigned short i;

	for (i = 0; i < LEC_ARP_TABLE_SIZE; i++) {
		INIT_HLIST_HEAD(&priv->lec_arp_tables[i]);
	}
	INIT_HLIST_HEAD(&priv->lec_arp_empty_ones);
	INIT_HLIST_HEAD(&priv->lec_no_forward);
	INIT_HLIST_HEAD(&priv->mcast_fwds);
	spin_lock_init(&priv->lec_arp_lock);
	INIT_DELAYED_WORK(&priv->lec_arp_work, lec_arp_check_expire);
	schedule_delayed_work(&priv->lec_arp_work, LEC_ARP_REFRESH_INTERVAL);
}