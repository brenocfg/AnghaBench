#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  channel; } ;
struct TYPE_4__ {int /*<<< orphan*/  auth_mode; } ;
struct lbs_private {int mac_control; int radio_on; int enablehwauto; int /*<<< orphan*/  event_fifo; scalar_t__* resp_len; scalar_t__ resp_idx; int /*<<< orphan*/  cmd_pending; int /*<<< orphan*/  driver_lock; int /*<<< orphan*/  cmdpendingq; int /*<<< orphan*/  cmdfreeq; int /*<<< orphan*/  command_timer; int /*<<< orphan*/  lock; int /*<<< orphan*/  psstate; int /*<<< orphan*/  psmode; int /*<<< orphan*/  capability; TYPE_2__ curbssparams; int /*<<< orphan*/  mode; TYPE_1__ secinfo; void* mesh_connect_status; void* connect_status; int /*<<< orphan*/  current_addr; int /*<<< orphan*/  network_free_list; TYPE_3__* networks; int /*<<< orphan*/  network_list; } ;
struct bss_descriptor {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int CMD_ACT_MAC_RX_ON ; 
 int CMD_ACT_MAC_TX_ON ; 
 int /*<<< orphan*/  DEFAULT_AD_HOC_CHANNEL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IW_AUTH_ALG_OPEN_SYSTEM ; 
 int /*<<< orphan*/  IW_MODE_INFRA ; 
 int /*<<< orphan*/  LBS802_11POWERMODECAM ; 
 int /*<<< orphan*/  LBS_DEB_MAIN ; 
 void* LBS_DISCONNECTED ; 
 int MAX_NETWORK_COUNT ; 
 int /*<<< orphan*/  PS_STATE_FULL_POWER ; 
 int /*<<< orphan*/  WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 int /*<<< orphan*/  command_timer_fn ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_alloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ lbs_allocate_cmd_buffer (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_pr_err (char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lbs_init_adapter(struct lbs_private *priv)
{
	size_t bufsize;
	int i, ret = 0;

	lbs_deb_enter(LBS_DEB_MAIN);

	/* Allocate buffer to store the BSSID list */
	bufsize = MAX_NETWORK_COUNT * sizeof(struct bss_descriptor);
	priv->networks = kzalloc(bufsize, GFP_KERNEL);
	if (!priv->networks) {
		lbs_pr_err("Out of memory allocating beacons\n");
		ret = -1;
		goto out;
	}

	/* Initialize scan result lists */
	INIT_LIST_HEAD(&priv->network_free_list);
	INIT_LIST_HEAD(&priv->network_list);
	for (i = 0; i < MAX_NETWORK_COUNT; i++) {
		list_add_tail(&priv->networks[i].list,
			      &priv->network_free_list);
	}

	memset(priv->current_addr, 0xff, ETH_ALEN);

	priv->connect_status = LBS_DISCONNECTED;
	priv->mesh_connect_status = LBS_DISCONNECTED;
	priv->secinfo.auth_mode = IW_AUTH_ALG_OPEN_SYSTEM;
	priv->mode = IW_MODE_INFRA;
	priv->curbssparams.channel = DEFAULT_AD_HOC_CHANNEL;
	priv->mac_control = CMD_ACT_MAC_RX_ON | CMD_ACT_MAC_TX_ON;
	priv->radio_on = 1;
	priv->enablehwauto = 1;
	priv->capability = WLAN_CAPABILITY_SHORT_PREAMBLE;
	priv->psmode = LBS802_11POWERMODECAM;
	priv->psstate = PS_STATE_FULL_POWER;

	mutex_init(&priv->lock);

	setup_timer(&priv->command_timer, command_timer_fn,
		(unsigned long)priv);

	INIT_LIST_HEAD(&priv->cmdfreeq);
	INIT_LIST_HEAD(&priv->cmdpendingq);

	spin_lock_init(&priv->driver_lock);
	init_waitqueue_head(&priv->cmd_pending);

	/* Allocate the command buffers */
	if (lbs_allocate_cmd_buffer(priv)) {
		lbs_pr_err("Out of memory allocating command buffers\n");
		ret = -ENOMEM;
		goto out;
	}
	priv->resp_idx = 0;
	priv->resp_len[0] = priv->resp_len[1] = 0;

	/* Create the event FIFO */
	priv->event_fifo = kfifo_alloc(sizeof(u32) * 16, GFP_KERNEL, NULL);
	if (IS_ERR(priv->event_fifo)) {
		lbs_pr_err("Out of memory allocating event FIFO buffer\n");
		ret = -ENOMEM;
		goto out;
	}

out:
	lbs_deb_leave_args(LBS_DEB_MAIN, "ret %d", ret);

	return ret;
}