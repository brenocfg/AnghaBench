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
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct nes_cm_core {void* disconn_wq; int /*<<< orphan*/  post_event; void* event_wq; TYPE_1__ listen_list; int /*<<< orphan*/  listen_list_lock; int /*<<< orphan*/  ht_lock; int /*<<< orphan*/ * api; int /*<<< orphan*/  events_posted; int /*<<< orphan*/  free_tx_pkt_max; int /*<<< orphan*/  state; int /*<<< orphan*/  mtu; TYPE_2__ tcp_timer; int /*<<< orphan*/  connected_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NES_CM_DEFAULT_FREE_PKTS ; 
 int /*<<< orphan*/  NES_CM_DEFAULT_MTU ; 
 int /*<<< orphan*/  NES_CM_STATE_INITED ; 
 int /*<<< orphan*/  NES_DBG_CM ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* create_singlethread_workqueue (char*) ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 struct nes_cm_core* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nes_cm_api ; 
 int /*<<< orphan*/  nes_cm_post_event ; 
 int /*<<< orphan*/  nes_cm_timer_tick ; 
 int /*<<< orphan*/  nes_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  print_core (struct nes_cm_core*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nes_cm_core *nes_cm_alloc_core(void)
{
	struct nes_cm_core *cm_core;

	/* setup the CM core */
	/* alloc top level core control structure */
	cm_core = kzalloc(sizeof(*cm_core), GFP_KERNEL);
	if (!cm_core)
		return NULL;

	INIT_LIST_HEAD(&cm_core->connected_nodes);
	init_timer(&cm_core->tcp_timer);
	cm_core->tcp_timer.function = nes_cm_timer_tick;

	cm_core->mtu = NES_CM_DEFAULT_MTU;
	cm_core->state = NES_CM_STATE_INITED;
	cm_core->free_tx_pkt_max = NES_CM_DEFAULT_FREE_PKTS;

	atomic_set(&cm_core->events_posted, 0);

	cm_core->api = &nes_cm_api;

	spin_lock_init(&cm_core->ht_lock);
	spin_lock_init(&cm_core->listen_list_lock);

	INIT_LIST_HEAD(&cm_core->listen_list.list);

	nes_debug(NES_DBG_CM, "Init CM Core completed -- cm_core=%p\n", cm_core);

	nes_debug(NES_DBG_CM, "Enable QUEUE EVENTS\n");
	cm_core->event_wq = create_singlethread_workqueue("nesewq");
	cm_core->post_event = nes_cm_post_event;
	nes_debug(NES_DBG_CM, "Enable QUEUE DISCONNECTS\n");
	cm_core->disconn_wq = create_singlethread_workqueue("nesdwq");

	print_core(cm_core);
	return cm_core;
}