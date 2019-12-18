#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int pps; int /*<<< orphan*/  enable; int /*<<< orphan*/  settime; int /*<<< orphan*/  gettime; int /*<<< orphan*/  adjtime; int /*<<< orphan*/  adjfreq; scalar_t__ n_per_out; scalar_t__ n_ext_ts; scalar_t__ n_alarm; int /*<<< orphan*/  max_adj; int /*<<< orphan*/  name; int /*<<< orphan*/  owner; } ;
struct TYPE_8__ {int /*<<< orphan*/  rx_filter; int /*<<< orphan*/  tx_type; scalar_t__ flags; } ;
struct efx_ptp_data {int nic_ts_enabled; int /*<<< orphan*/  start; void* workwq; int /*<<< orphan*/  phc_clock; void* pps_workwq; int /*<<< orphan*/  pps_work; TYPE_6__ phc_clock_info; int /*<<< orphan*/  evt_free_list; TYPE_3__* rx_evts; int /*<<< orphan*/  evt_lock; int /*<<< orphan*/  evt_list; TYPE_2__ config; int /*<<< orphan*/  work; int /*<<< orphan*/  txq; int /*<<< orphan*/  rxq; struct efx_channel* channel; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; TYPE_5__* pci_dev; TYPE_4__* net_dev; } ;
struct TYPE_7__ {scalar_t__ core_index; } ;
struct efx_channel {TYPE_1__ rx_queue; scalar_t__ irq_moderation; struct efx_nic* efx; } ;
struct TYPE_11__ {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  perm_addr; } ;
struct TYPE_9__ {int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWTSTAMP_FILTER_NONE ; 
 int /*<<< orphan*/  HWTSTAMP_TX_OFF ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PPB ; 
 unsigned int MAX_RECEIVE_EVENTS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 void* create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (void*) ; 
 int efx_nic_alloc_buffer (struct efx_nic*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  efx_nic_free_buffer (struct efx_nic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_phc_adjfreq ; 
 int /*<<< orphan*/  efx_phc_adjtime ; 
 int /*<<< orphan*/  efx_phc_enable ; 
 int /*<<< orphan*/  efx_phc_gettime ; 
 int /*<<< orphan*/  efx_phc_settime ; 
 int /*<<< orphan*/  efx_ptp_pps_worker ; 
 int /*<<< orphan*/  efx_ptp_worker ; 
 int /*<<< orphan*/  kfree (struct efx_ptp_data*) ; 
 struct efx_ptp_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptp_clock_register (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_ptp_probe_channel(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;
	struct efx_ptp_data *ptp;
	int rc = 0;
	unsigned int pos;

	channel->irq_moderation = 0;
	channel->rx_queue.core_index = 0;

	ptp = kzalloc(sizeof(struct efx_ptp_data), GFP_KERNEL);
	efx->ptp_data = ptp;
	if (!efx->ptp_data)
		return -ENOMEM;

	rc = efx_nic_alloc_buffer(efx, &ptp->start, sizeof(int));
	if (rc != 0)
		goto fail1;

	ptp->channel = channel;
	skb_queue_head_init(&ptp->rxq);
	skb_queue_head_init(&ptp->txq);
	ptp->workwq = create_singlethread_workqueue("sfc_ptp");
	if (!ptp->workwq) {
		rc = -ENOMEM;
		goto fail2;
	}

	INIT_WORK(&ptp->work, efx_ptp_worker);
	ptp->config.flags = 0;
	ptp->config.tx_type = HWTSTAMP_TX_OFF;
	ptp->config.rx_filter = HWTSTAMP_FILTER_NONE;
	INIT_LIST_HEAD(&ptp->evt_list);
	INIT_LIST_HEAD(&ptp->evt_free_list);
	spin_lock_init(&ptp->evt_lock);
	for (pos = 0; pos < MAX_RECEIVE_EVENTS; pos++)
		list_add(&ptp->rx_evts[pos].link, &ptp->evt_free_list);

	ptp->phc_clock_info.owner = THIS_MODULE;
	snprintf(ptp->phc_clock_info.name,
		 sizeof(ptp->phc_clock_info.name),
		 "%pm", efx->net_dev->perm_addr);
	ptp->phc_clock_info.max_adj = MAX_PPB;
	ptp->phc_clock_info.n_alarm = 0;
	ptp->phc_clock_info.n_ext_ts = 0;
	ptp->phc_clock_info.n_per_out = 0;
	ptp->phc_clock_info.pps = 1;
	ptp->phc_clock_info.adjfreq = efx_phc_adjfreq;
	ptp->phc_clock_info.adjtime = efx_phc_adjtime;
	ptp->phc_clock_info.gettime = efx_phc_gettime;
	ptp->phc_clock_info.settime = efx_phc_settime;
	ptp->phc_clock_info.enable = efx_phc_enable;

	ptp->phc_clock = ptp_clock_register(&ptp->phc_clock_info,
					    &efx->pci_dev->dev);
	if (IS_ERR(ptp->phc_clock)) {
		rc = PTR_ERR(ptp->phc_clock);
		goto fail3;
	}

	INIT_WORK(&ptp->pps_work, efx_ptp_pps_worker);
	ptp->pps_workwq = create_singlethread_workqueue("sfc_pps");
	if (!ptp->pps_workwq) {
		rc = -ENOMEM;
		goto fail4;
	}
	ptp->nic_ts_enabled = false;

	return 0;
fail4:
	ptp_clock_unregister(efx->ptp_data->phc_clock);

fail3:
	destroy_workqueue(efx->ptp_data->workwq);

fail2:
	efx_nic_free_buffer(efx, &ptp->start);

fail1:
	kfree(efx->ptp_data);
	efx->ptp_data = NULL;

	return rc;
}