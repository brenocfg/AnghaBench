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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  pv_minor; int /*<<< orphan*/  pv_major; } ;
struct TYPE_3__ {int /*<<< orphan*/  pv_minor; int /*<<< orphan*/  pv_major; } ;
struct dlm_query_join_request {int /*<<< orphan*/  node_map; TYPE_2__ fs_proto; TYPE_1__ dlm_proto; int /*<<< orphan*/  name_len; int /*<<< orphan*/  domain; int /*<<< orphan*/  node_idx; } ;
struct dlm_query_join_packet {int code; int /*<<< orphan*/  fs_minor; int /*<<< orphan*/  dlm_minor; } ;
struct dlm_ctxt {TYPE_2__ fs_locking_proto; TYPE_1__ dlm_locking_proto; int /*<<< orphan*/  live_nodes_map; int /*<<< orphan*/  name; int /*<<< orphan*/  node_num; } ;
typedef  int /*<<< orphan*/  join_msg ;
typedef  enum dlm_query_join_response_code { ____Placeholder_dlm_query_join_response_code } dlm_query_join_response_code ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_MOD_KEY ; 
 int /*<<< orphan*/  DLM_QUERY_JOIN_MSG ; 
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int EPROTO ; 
 int JOIN_DISALLOW ; 
 int JOIN_OK ; 
 int JOIN_OK_NO_MAP ; 
 int JOIN_PROTOCOL_MISMATCH ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int /*<<< orphan*/  O2NM_MAX_NODES ; 
 int /*<<< orphan*/  byte_copymap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_query_join_wire_to_packet (int /*<<< orphan*/ ,struct dlm_query_join_packet*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dlm_query_join_request*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_query_join_request*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_request_join(struct dlm_ctxt *dlm,
			    int node,
			    enum dlm_query_join_response_code *response)
{
	int status;
	struct dlm_query_join_request join_msg;
	struct dlm_query_join_packet packet;
	u32 join_resp;

	mlog(0, "querying node %d\n", node);

	memset(&join_msg, 0, sizeof(join_msg));
	join_msg.node_idx = dlm->node_num;
	join_msg.name_len = strlen(dlm->name);
	memcpy(join_msg.domain, dlm->name, join_msg.name_len);
	join_msg.dlm_proto = dlm->dlm_locking_proto;
	join_msg.fs_proto = dlm->fs_locking_proto;

	/* copy live node map to join message */
	byte_copymap(join_msg.node_map, dlm->live_nodes_map, O2NM_MAX_NODES);

	status = o2net_send_message(DLM_QUERY_JOIN_MSG, DLM_MOD_KEY, &join_msg,
				    sizeof(join_msg), node,
				    &join_resp);
	if (status < 0 && status != -ENOPROTOOPT) {
		mlog_errno(status);
		goto bail;
	}
	dlm_query_join_wire_to_packet(join_resp, &packet);

	/* -ENOPROTOOPT from the net code means the other side isn't
	    listening for our message type -- that's fine, it means
	    his dlm isn't up, so we can consider him a 'yes' but not
	    joined into the domain.  */
	if (status == -ENOPROTOOPT) {
		status = 0;
		*response = JOIN_OK_NO_MAP;
	} else if (packet.code == JOIN_DISALLOW ||
		   packet.code == JOIN_OK_NO_MAP) {
		*response = packet.code;
	} else if (packet.code == JOIN_PROTOCOL_MISMATCH) {
		mlog(ML_NOTICE,
		     "This node requested DLM locking protocol %u.%u and "
		     "filesystem locking protocol %u.%u.  At least one of "
		     "the protocol versions on node %d is not compatible, "
		     "disconnecting\n",
		     dlm->dlm_locking_proto.pv_major,
		     dlm->dlm_locking_proto.pv_minor,
		     dlm->fs_locking_proto.pv_major,
		     dlm->fs_locking_proto.pv_minor,
		     node);
		status = -EPROTO;
		*response = packet.code;
	} else if (packet.code == JOIN_OK) {
		*response = packet.code;
		/* Use the same locking protocol as the remote node */
		dlm->dlm_locking_proto.pv_minor = packet.dlm_minor;
		dlm->fs_locking_proto.pv_minor = packet.fs_minor;
		mlog(0,
		     "Node %d responds JOIN_OK with DLM locking protocol "
		     "%u.%u and fs locking protocol %u.%u\n",
		     node,
		     dlm->dlm_locking_proto.pv_major,
		     dlm->dlm_locking_proto.pv_minor,
		     dlm->fs_locking_proto.pv_major,
		     dlm->fs_locking_proto.pv_minor);
	} else {
		status = -EINVAL;
		mlog(ML_ERROR, "invalid response %d from node %u\n",
		     packet.code, node);
	}

	mlog(0, "status %d, node %d response is %d\n", status, node,
	     *response);

bail:
	return status;
}