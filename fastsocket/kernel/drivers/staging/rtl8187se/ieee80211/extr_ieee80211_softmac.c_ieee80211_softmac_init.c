#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_network {int dummy; } ;
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct TYPE_3__ {int /*<<< orphan*/ * txb; } ;
struct ieee80211_device {int rate; int ps; int bInactivePs; int actscanning; int ListenInterval; int beinretry; int bHwRadioOff; int /*<<< orphan*/  pDot11dInfo; int /*<<< orphan*/  ps_task; int /*<<< orphan*/  beacon_lock; int /*<<< orphan*/  mgmt_tx_lock; int /*<<< orphan*/  scan_sem; int /*<<< orphan*/  wx_sem; int /*<<< orphan*/  wx_sync_scan_wq; int /*<<< orphan*/  associate_retry_wq; int /*<<< orphan*/  softmac_scan_wq; int /*<<< orphan*/  associate_procedure_wq; int /*<<< orphan*/  associate_complete_wq; int /*<<< orphan*/  start_ibss_wq; void* wq; TYPE_2__ beacon_timer; TYPE_2__ associate_timer; TYPE_1__ tx_pending; scalar_t__ NumRxUnicast; scalar_t__ NumRxOkTotal; scalar_t__ NumRxBcnInPeriod; scalar_t__ NumRxDataInPeriod; scalar_t__ sta_sleep; int /*<<< orphan*/  basic_rate; scalar_t__ proto_started; scalar_t__ ssid_set; scalar_t__ wap_set; scalar_t__ softmac_features; scalar_t__ scanning; scalar_t__ queue_stop; scalar_t__ assoc_id; scalar_t__* seq_ctrl; scalar_t__ sync_scan_hurryup; int /*<<< orphan*/  state; int /*<<< orphan*/  current_network; } ;
typedef  int /*<<< orphan*/  RT_DOT11D_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IEEE80211_DEFAULT_BASIC_RATE ; 
 int /*<<< orphan*/  IEEE80211_NOLINK ; 
 int IEEE80211_PS_MBCAST ; 
 int IEEE80211_PS_UNICAST ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void*) ; 
 void* create_workqueue (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ieee80211_associate_abort_cb ; 
 scalar_t__ ieee80211_associate_complete_wq ; 
 scalar_t__ ieee80211_associate_procedure_wq ; 
 scalar_t__ ieee80211_associate_retry_wq ; 
 int /*<<< orphan*/  ieee80211_send_beacon_cb ; 
 scalar_t__ ieee80211_softmac_scan_wq ; 
 scalar_t__ ieee80211_sta_ps ; 
 scalar_t__ ieee80211_start_ibss_wq ; 
 scalar_t__ ieee80211_wx_sync_scan_wq ; 
 int /*<<< orphan*/  init_mgmt_queue (struct ieee80211_device*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,void (*) (unsigned long),unsigned long) ; 

void ieee80211_softmac_init(struct ieee80211_device *ieee)
{
	int i;
	memset(&ieee->current_network, 0, sizeof(struct ieee80211_network));

	ieee->state = IEEE80211_NOLINK;
	ieee->sync_scan_hurryup = 0;
	for(i = 0; i < 5; i++) {
	  ieee->seq_ctrl[i] = 0;
	}

	ieee->assoc_id = 0;
	ieee->queue_stop = 0;
	ieee->scanning = 0;
	ieee->softmac_features = 0; //so IEEE2100-like driver are happy
	ieee->wap_set = 0;
	ieee->ssid_set = 0;
	ieee->proto_started = 0;
	ieee->basic_rate = IEEE80211_DEFAULT_BASIC_RATE;
	ieee->rate = 3;
//#ifdef ENABLE_LPS
	ieee->ps = IEEE80211_PS_MBCAST|IEEE80211_PS_UNICAST;
//#else
//	ieee->ps = IEEE80211_PS_DISABLED;
//#endif
	ieee->sta_sleep = 0;
//by amy
	ieee->bInactivePs = false;
	ieee->actscanning = false;
	ieee->ListenInterval = 2;
	ieee->NumRxDataInPeriod = 0; //YJ,add,080828
	ieee->NumRxBcnInPeriod = 0; //YJ,add,080828
	ieee->NumRxOkTotal = 0;//+by amy 080312
	ieee->NumRxUnicast = 0;//YJ,add,080828,for keep alive
	ieee->beinretry = false;
	ieee->bHwRadioOff = false;
//by amy

	init_mgmt_queue(ieee);

	ieee->tx_pending.txb = NULL;

	init_timer(&ieee->associate_timer);
	ieee->associate_timer.data = (unsigned long)ieee;
	ieee->associate_timer.function = ieee80211_associate_abort_cb;

	init_timer(&ieee->beacon_timer);
	ieee->beacon_timer.data = (unsigned long) ieee;
	ieee->beacon_timer.function = ieee80211_send_beacon_cb;

#ifdef PF_SYNCTHREAD
	ieee->wq = create_workqueue(DRV_NAME,0);
#else
	ieee->wq = create_workqueue(DRV_NAME);
#endif
	INIT_DELAYED_WORK(&ieee->start_ibss_wq,(void*) ieee80211_start_ibss_wq);
	INIT_WORK(&ieee->associate_complete_wq,(void*) ieee80211_associate_complete_wq);
	INIT_WORK(&ieee->associate_procedure_wq,(void*) ieee80211_associate_procedure_wq);
	INIT_DELAYED_WORK(&ieee->softmac_scan_wq,(void*) ieee80211_softmac_scan_wq);
	INIT_DELAYED_WORK(&ieee->associate_retry_wq,(void*) ieee80211_associate_retry_wq);
	INIT_WORK(&ieee->wx_sync_scan_wq,(void*) ieee80211_wx_sync_scan_wq);
//	INIT_WORK(&ieee->watch_dog_wq,(void*) ieee80211_watch_dog_wq);

	sema_init(&ieee->wx_sem, 1);
	sema_init(&ieee->scan_sem, 1);

	spin_lock_init(&ieee->mgmt_tx_lock);
	spin_lock_init(&ieee->beacon_lock);

	tasklet_init(&ieee->ps_task,
	     (void(*)(unsigned long)) ieee80211_sta_ps,
	     (unsigned long)ieee);
	ieee->pDot11dInfo = kmalloc(sizeof(RT_DOT11D_INFO), GFP_ATOMIC);
}