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
struct wmi {int stopped; int /*<<< orphan*/  wmi_event_tasklet; int /*<<< orphan*/  pending_tx_events; int /*<<< orphan*/  cmd_wait; int /*<<< orphan*/  multi_write_mutex; int /*<<< orphan*/  op_mutex; int /*<<< orphan*/  event_lock; int /*<<< orphan*/  wmi_lock; int /*<<< orphan*/  wmi_event_queue; struct ath9k_htc_priv* drv_priv; } ;
struct ath9k_htc_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ath9k_wmi_event_tasklet ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct wmi* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

struct wmi *ath9k_init_wmi(struct ath9k_htc_priv *priv)
{
	struct wmi *wmi;

	wmi = kzalloc(sizeof(struct wmi), GFP_KERNEL);
	if (!wmi)
		return NULL;

	wmi->drv_priv = priv;
	wmi->stopped = false;
	skb_queue_head_init(&wmi->wmi_event_queue);
	spin_lock_init(&wmi->wmi_lock);
	spin_lock_init(&wmi->event_lock);
	mutex_init(&wmi->op_mutex);
	mutex_init(&wmi->multi_write_mutex);
	init_completion(&wmi->cmd_wait);
	INIT_LIST_HEAD(&wmi->pending_tx_events);
	tasklet_init(&wmi->wmi_event_tasklet, ath9k_wmi_event_tasklet,
		     (unsigned long)wmi);

	return wmi;
}