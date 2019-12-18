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
struct o2nm_node {int dummy; } ;
struct o2hb_node_event {int /*<<< orphan*/  hn_item; } ;
struct o2hb_disk_slot {size_t ds_node_num; int /*<<< orphan*/  ds_live_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ML_HEARTBEAT ; 
 int /*<<< orphan*/  O2HB_NODE_DOWN_CB ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  o2hb_live_node_bitmap ; 
 int /*<<< orphan*/ * o2hb_live_slots ; 
 int /*<<< orphan*/  o2hb_queue_node_event (struct o2hb_node_event*,int /*<<< orphan*/ ,struct o2nm_node*,size_t) ; 
 int /*<<< orphan*/  o2hb_run_event_list (struct o2hb_node_event*) ; 
 struct o2nm_node* o2nm_get_node_by_num (size_t) ; 
 int /*<<< orphan*/  o2nm_node_put (struct o2nm_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void o2hb_shutdown_slot(struct o2hb_disk_slot *slot)
{
	struct o2hb_node_event event =
		{ .hn_item = LIST_HEAD_INIT(event.hn_item), };
	struct o2nm_node *node;

	node = o2nm_get_node_by_num(slot->ds_node_num);
	if (!node)
		return;

	spin_lock(&o2hb_live_lock);
	if (!list_empty(&slot->ds_live_item)) {
		mlog(ML_HEARTBEAT, "Shutdown, node %d leaves region\n",
		     slot->ds_node_num);

		list_del_init(&slot->ds_live_item);

		if (list_empty(&o2hb_live_slots[slot->ds_node_num])) {
			clear_bit(slot->ds_node_num, o2hb_live_node_bitmap);

			o2hb_queue_node_event(&event, O2HB_NODE_DOWN_CB, node,
					      slot->ds_node_num);
		}
	}
	spin_unlock(&o2hb_live_lock);

	o2hb_run_event_list(&event);

	o2nm_node_put(node);
}