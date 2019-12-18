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
struct nes_cm_node {int state; struct iw_cm_id* cm_id; int /*<<< orphan*/  cm_core; } ;
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;} ;
typedef  enum nes_cm_node_state { ____Placeholder_nes_cm_node_state } nes_cm_node_state ;

/* Variables and functions */
 int /*<<< orphan*/  NES_CM_EVENT_ABORTED ; 
 int NES_CM_STATE_CLOSED ; 
#define  NES_CM_STATE_CLOSING 131 
#define  NES_CM_STATE_FIN_WAIT1 130 
#define  NES_CM_STATE_LAST_ACK 129 
#define  NES_CM_STATE_SYN_RCVD 128 
 int /*<<< orphan*/  add_ref_cm_node (struct nes_cm_node*) ; 
 int /*<<< orphan*/  create_event (struct nes_cm_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rem_ref_cm_node (int /*<<< orphan*/ ,struct nes_cm_node*) ; 
 int /*<<< orphan*/  send_reset (struct nes_cm_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 

__attribute__((used)) static void nes_retrans_expired(struct nes_cm_node *cm_node)
{
	struct iw_cm_id *cm_id = cm_node->cm_id;
	enum nes_cm_node_state state = cm_node->state;
	cm_node->state = NES_CM_STATE_CLOSED;

	switch (state) {
	case NES_CM_STATE_SYN_RCVD:
	case NES_CM_STATE_CLOSING:
		rem_ref_cm_node(cm_node->cm_core, cm_node);
		break;
	case NES_CM_STATE_LAST_ACK:
	case NES_CM_STATE_FIN_WAIT1:
		if (cm_node->cm_id)
			cm_id->rem_ref(cm_id);
		send_reset(cm_node, NULL);
		break;
	default:
		add_ref_cm_node(cm_node);
		send_reset(cm_node, NULL);
		create_event(cm_node, NES_CM_EVENT_ABORTED);
	}
}