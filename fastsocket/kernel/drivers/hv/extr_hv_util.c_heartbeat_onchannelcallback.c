#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct vmbuspipe_hdr {int dummy; } ;
struct vmbus_channel {int dummy; } ;
struct icmsg_negotiate {int dummy; } ;
struct icmsg_hdr {scalar_t__ icmsgtype; int icflags; } ;
struct heartbeat_msg_data {int seq_num; } ;
struct TYPE_2__ {int /*<<< orphan*/ * recv_buffer; } ;

/* Variables and functions */
 int ICMSGHDRFLAG_RESPONSE ; 
 int ICMSGHDRFLAG_TRANSACTION ; 
 scalar_t__ ICMSGTYPE_NEGOTIATE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  hb_srv_version ; 
 int /*<<< orphan*/  util_fw_version ; 
 TYPE_1__ util_heartbeat ; 
 int /*<<< orphan*/  vmbus_prep_negotiate_resp (struct icmsg_hdr*,struct icmsg_negotiate*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_recvpacket (struct vmbus_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_sendpacket (struct vmbus_channel*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void heartbeat_onchannelcallback(void *context)
{
	struct vmbus_channel *channel = context;
	u32 recvlen;
	u64 requestid;
	struct icmsg_hdr *icmsghdrp;
	struct heartbeat_msg_data *heartbeat_msg;
	u8 *hbeat_txf_buf = util_heartbeat.recv_buffer;
	struct icmsg_negotiate *negop = NULL;

	vmbus_recvpacket(channel, hbeat_txf_buf,
			 PAGE_SIZE, &recvlen, &requestid);

	if (recvlen > 0) {
		icmsghdrp = (struct icmsg_hdr *)&hbeat_txf_buf[
				sizeof(struct vmbuspipe_hdr)];

		if (icmsghdrp->icmsgtype == ICMSGTYPE_NEGOTIATE) {
			vmbus_prep_negotiate_resp(icmsghdrp, negop,
				hbeat_txf_buf, util_fw_version,
				hb_srv_version);
		} else {
			heartbeat_msg =
				(struct heartbeat_msg_data *)&hbeat_txf_buf[
					sizeof(struct vmbuspipe_hdr) +
					sizeof(struct icmsg_hdr)];

			heartbeat_msg->seq_num += 1;
		}

		icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION
			| ICMSGHDRFLAG_RESPONSE;

		vmbus_sendpacket(channel, hbeat_txf_buf,
				       recvlen, requestid,
				       VM_PKT_DATA_INBAND, 0);
	}
}