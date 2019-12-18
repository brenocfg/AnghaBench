#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct vmbuspipe_hdr {int dummy; } ;
struct vmbus_channel {int dummy; } ;
struct icmsg_negotiate {int dummy; } ;
struct icmsg_hdr {scalar_t__ icmsgtype; int icflags; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {int operation; } ;
struct hv_vss_msg {TYPE_3__ dm_info; TYPE_2__ vss_cf; TYPE_1__ vss_hdr; } ;
struct TYPE_8__ {int active; struct hv_vss_msg* msg; int /*<<< orphan*/  recv_req_id; struct vmbus_channel* recv_channel; scalar_t__ recv_len; } ;

/* Variables and functions */
 int ICMSGHDRFLAG_RESPONSE ; 
 int ICMSGHDRFLAG_TRANSACTION ; 
 scalar_t__ ICMSGTYPE_NEGOTIATE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  UTIL_FW_VERSION ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  VSS_HBU_NO_AUTO_RECOVERY ; 
#define  VSS_OP_FREEZE 131 
#define  VSS_OP_GET_DM_INFO 130 
#define  VSS_OP_HOT_BACKUP 129 
#define  VSS_OP_THAW 128 
 int /*<<< orphan*/  VSS_VERSION ; 
 int /*<<< orphan*/ * recv_buffer ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_prep_negotiate_resp (struct icmsg_hdr*,struct icmsg_negotiate*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_recvpacket (struct vmbus_channel*,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_sendpacket (struct vmbus_channel*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vss_respond_to_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vss_send_op_work ; 
 TYPE_4__ vss_transaction ; 

void hv_vss_onchannelcallback(void *context)
{
	struct vmbus_channel *channel = context;
	u32 recvlen;
	u64 requestid;
	struct hv_vss_msg *vss_msg;


	struct icmsg_hdr *icmsghdrp;
	struct icmsg_negotiate *negop = NULL;

	if (vss_transaction.active) {
		/*
		 * We will defer processing this callback once
		 * the current transaction is complete.
		 */
		vss_transaction.recv_channel = channel;
		return;
	}

	vmbus_recvpacket(channel, recv_buffer, PAGE_SIZE * 2, &recvlen,
			 &requestid);

	if (recvlen > 0) {
		icmsghdrp = (struct icmsg_hdr *)&recv_buffer[
			sizeof(struct vmbuspipe_hdr)];

		if (icmsghdrp->icmsgtype == ICMSGTYPE_NEGOTIATE) {
			vmbus_prep_negotiate_resp(icmsghdrp, negop,
				 recv_buffer, UTIL_FW_VERSION,
				 VSS_VERSION);
		} else {
			vss_msg = (struct hv_vss_msg *)&recv_buffer[
				sizeof(struct vmbuspipe_hdr) +
				sizeof(struct icmsg_hdr)];

			/*
			 * Stash away this global state for completing the
			 * transaction; note transactions are serialized.
			 */

			vss_transaction.recv_len = recvlen;
			vss_transaction.recv_channel = channel;
			vss_transaction.recv_req_id = requestid;
			vss_transaction.active = true;
			vss_transaction.msg = (struct hv_vss_msg *)vss_msg;

			switch (vss_msg->vss_hdr.operation) {
				/*
				 * Initiate a "freeze/thaw"
				 * operation in the guest.
				 * We respond to the host once
				 * the operation is complete.
				 *
				 * We send the message to the
				 * user space daemon and the
				 * operation is performed in
				 * the daemon.
				 */
			case VSS_OP_FREEZE:
			case VSS_OP_THAW:
				schedule_work(&vss_send_op_work);
				return;

			case VSS_OP_HOT_BACKUP:
				vss_msg->vss_cf.flags =
					 VSS_HBU_NO_AUTO_RECOVERY;
				vss_respond_to_host(0);
				return;

			case VSS_OP_GET_DM_INFO:
				vss_msg->dm_info.flags = 0;
				vss_respond_to_host(0);
				return;

			default:
				vss_respond_to_host(0);
				return;

			}

		}

		icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION
			| ICMSGHDRFLAG_RESPONSE;

		vmbus_sendpacket(channel, recv_buffer,
				       recvlen, requestid,
				       VM_PKT_DATA_INBAND, 0);
	}

}