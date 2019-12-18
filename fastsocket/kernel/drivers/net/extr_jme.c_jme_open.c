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
struct net_device {int dummy; } ;
struct jme_adapter {int /*<<< orphan*/  old_ecmd; int /*<<< orphan*/  flags; int /*<<< orphan*/  rxempty_task; int /*<<< orphan*/  rxclean_task; int /*<<< orphan*/  txclean_task; int /*<<< orphan*/  linkch_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  JME_FLAG_SSET ; 
 int /*<<< orphan*/  JME_NAPI_ENABLE (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_clear_pm (struct jme_adapter*) ; 
 int jme_request_irq (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_reset_link (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_reset_phy_processor (struct jme_adapter*) ; 
 int /*<<< orphan*/  jme_set_settings (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jme_start_irq (struct jme_adapter*) ; 
 struct jme_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_hi_enable (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
jme_open(struct net_device *netdev)
{
	struct jme_adapter *jme = netdev_priv(netdev);
	int rc;

	jme_clear_pm(jme);
	JME_NAPI_ENABLE(jme);

	tasklet_enable(&jme->linkch_task);
	tasklet_enable(&jme->txclean_task);
	tasklet_hi_enable(&jme->rxclean_task);
	tasklet_hi_enable(&jme->rxempty_task);

	rc = jme_request_irq(jme);
	if (rc)
		goto err_out;

	jme_start_irq(jme);

	if (test_bit(JME_FLAG_SSET, &jme->flags))
		jme_set_settings(netdev, &jme->old_ecmd);
	else
		jme_reset_phy_processor(jme);

	jme_reset_link(jme);

	return 0;

err_out:
	netif_stop_queue(netdev);
	netif_carrier_off(netdev);
	return rc;
}