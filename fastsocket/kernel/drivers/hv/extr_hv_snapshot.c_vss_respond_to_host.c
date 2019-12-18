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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vmbuspipe_hdr {int dummy; } ;
struct vmbus_channel {int /*<<< orphan*/ * onchannel_callback; } ;
struct icmsg_hdr {int status; int icflags; } ;
struct TYPE_2__ {int active; int /*<<< orphan*/  recv_req_id; struct vmbus_channel* recv_channel; int /*<<< orphan*/  recv_len; } ;

/* Variables and functions */
 int ICMSGHDRFLAG_RESPONSE ; 
 int ICMSGHDRFLAG_TRANSACTION ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/ * recv_buffer ; 
 int /*<<< orphan*/  vmbus_sendpacket (struct vmbus_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ vss_transaction ; 

__attribute__((used)) static void
vss_respond_to_host(int error)
{
	struct icmsg_hdr *icmsghdrp;
	u32	buf_len;
	struct vmbus_channel *channel;
	u64	req_id;

	/*
	 * If a transaction is not active; log and return.
	 */

	if (!vss_transaction.active) {
		/*
		 * This is a spurious call!
		 */
		pr_warn("VSS: Transaction not active\n");
		return;
	}
	/*
	 * Copy the global state for completing the transaction. Note that
	 * only one transaction can be active at a time.
	 */

	buf_len = vss_transaction.recv_len;
	channel = vss_transaction.recv_channel;
	req_id = vss_transaction.recv_req_id;
	vss_transaction.active = false;

	icmsghdrp = (struct icmsg_hdr *)
			&recv_buffer[sizeof(struct vmbuspipe_hdr)];

	if (channel->onchannel_callback == NULL)
		/*
		 * We have raced with util driver being unloaded;
		 * silently return.
		 */
		return;

	icmsghdrp->status = error;

	icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION | ICMSGHDRFLAG_RESPONSE;

	vmbus_sendpacket(channel, recv_buffer, buf_len, req_id,
				VM_PKT_DATA_INBAND, 0);

}