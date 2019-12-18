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
struct o2hb_node_event {int hn_event_type; int hn_node_num; int /*<<< orphan*/  hn_item; struct o2nm_node* hn_node; } ;
typedef  enum o2hb_callback_type { ____Placeholder_o2hb_callback_type } o2hb_callback_type ;

/* Variables and functions */
 int /*<<< orphan*/  ML_HEARTBEAT ; 
 int O2HB_NODE_UP_CB ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  o2hb_live_lock ; 
 int /*<<< orphan*/  o2hb_node_events ; 

__attribute__((used)) static void o2hb_queue_node_event(struct o2hb_node_event *event,
				  enum o2hb_callback_type type,
				  struct o2nm_node *node,
				  int node_num)
{
	assert_spin_locked(&o2hb_live_lock);

	event->hn_event_type = type;
	event->hn_node = node;
	event->hn_node_num = node_num;

	mlog(ML_HEARTBEAT, "Queue node %s event for node %d\n",
	     type == O2HB_NODE_UP_CB ? "UP" : "DOWN", node_num);

	list_add_tail(&event->hn_item, &o2hb_node_events);
}