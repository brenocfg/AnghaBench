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
struct wiphy {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * spy_data; } ;
struct orinoco_private {int (* hard_reset ) (struct orinoco_private*) ;int (* stop_fw ) (struct orinoco_private*,int) ;int hw_unavailable; int last_linkstatus; int /*<<< orphan*/ * cached_fw; int /*<<< orphan*/ * cached_pri_fw; int /*<<< orphan*/  process_scan; int /*<<< orphan*/  scan_list; int /*<<< orphan*/  scan_lock; int /*<<< orphan*/  rx_tasklet; int /*<<< orphan*/  rx_list; int /*<<< orphan*/  wevent_work; int /*<<< orphan*/  join_work; int /*<<< orphan*/  reset_work; scalar_t__ open; int /*<<< orphan*/  lock; int /*<<< orphan*/  spy_data; TYPE_1__ wireless_data; int /*<<< orphan*/ * card; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  orinoco_cfg_ops ; 
 int /*<<< orphan*/  orinoco_join_ap ; 
 int /*<<< orphan*/  orinoco_process_scan_results ; 
 int /*<<< orphan*/  orinoco_register_pm_notifier (struct orinoco_private*) ; 
 int /*<<< orphan*/  orinoco_reset ; 
 int /*<<< orphan*/  orinoco_rx_isr_tasklet ; 
 int /*<<< orphan*/  orinoco_send_wevents ; 
 int /*<<< orphan*/  orinoco_wiphy_init (struct wiphy*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 struct wiphy* wiphy_new (int /*<<< orphan*/ *,int) ; 
 struct orinoco_private* wiphy_priv (struct wiphy*) ; 

struct orinoco_private
*alloc_orinocodev(int sizeof_card,
		  struct device *device,
		  int (*hard_reset)(struct orinoco_private *),
		  int (*stop_fw)(struct orinoco_private *, int))
{
	struct orinoco_private *priv;
	struct wiphy *wiphy;

	/* allocate wiphy
	 * NOTE: We only support a single virtual interface
	 *       but this may change when monitor mode is added
	 */
	wiphy = wiphy_new(&orinoco_cfg_ops,
			  sizeof(struct orinoco_private) + sizeof_card);
	if (!wiphy)
		return NULL;

	priv = wiphy_priv(wiphy);
	priv->dev = device;

	if (sizeof_card)
		priv->card = (void *)((unsigned long)priv
				      + sizeof(struct orinoco_private));
	else
		priv->card = NULL;

	orinoco_wiphy_init(wiphy);

#ifdef WIRELESS_SPY
	priv->wireless_data.spy_data = &priv->spy_data;
#endif

	/* Set up default callbacks */
	priv->hard_reset = hard_reset;
	priv->stop_fw = stop_fw;

	spin_lock_init(&priv->lock);
	priv->open = 0;
	priv->hw_unavailable = 1; /* orinoco_init() must clear this
				   * before anything else touches the
				   * hardware */
	INIT_WORK(&priv->reset_work, orinoco_reset);
	INIT_WORK(&priv->join_work, orinoco_join_ap);
	INIT_WORK(&priv->wevent_work, orinoco_send_wevents);

	INIT_LIST_HEAD(&priv->rx_list);
	tasklet_init(&priv->rx_tasklet, orinoco_rx_isr_tasklet,
		     (unsigned long) priv);

	spin_lock_init(&priv->scan_lock);
	INIT_LIST_HEAD(&priv->scan_list);
	INIT_WORK(&priv->process_scan, orinoco_process_scan_results);

	priv->last_linkstatus = 0xffff;

#if defined(CONFIG_HERMES_CACHE_FW_ON_INIT) || defined(CONFIG_PM_SLEEP)
	priv->cached_pri_fw = NULL;
	priv->cached_fw = NULL;
#endif

	/* Register PM notifiers */
	orinoco_register_pm_notifier(priv);

	return priv;
}