#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vmbuspipe_hdr {int dummy; } ;
struct vmbus_channel {int /*<<< orphan*/ * onchannel_callback; } ;
struct icmsg_hdr {int status; int icflags; } ;
struct hv_kvp_exchg_msg_value {char* key; int key_size; char* value; int value_size; int /*<<< orphan*/  value_type; } ;
struct TYPE_10__ {struct hv_kvp_exchg_msg_value data; } ;
struct TYPE_9__ {struct hv_kvp_exchg_msg_value data; } ;
struct TYPE_11__ {TYPE_4__ kvp_enum_data; TYPE_3__ kvp_get; } ;
struct hv_kvp_msg {TYPE_5__ body; } ;
struct hv_kvp_ip_msg {int dummy; } ;
struct TYPE_12__ {int active; TYPE_2__* kvp_msg; int /*<<< orphan*/  recv_req_id; struct vmbus_channel* recv_channel; int /*<<< orphan*/  recv_len; } ;
struct TYPE_7__ {int operation; } ;
struct TYPE_8__ {TYPE_1__ kvp_hdr; } ;

/* Variables and functions */
 void* HV_E_FAIL ; 
 int HV_KVP_EXCHANGE_MAX_KEY_SIZE ; 
 int HV_KVP_EXCHANGE_MAX_VALUE_SIZE ; 
 int ICMSGHDRFLAG_RESPONSE ; 
 int ICMSGHDRFLAG_TRANSACTION ; 
#define  KVP_OP_DELETE 132 
#define  KVP_OP_GET 131 
#define  KVP_OP_GET_IP_INFO 130 
#define  KVP_OP_SET 129 
#define  KVP_OP_SET_IP_INFO 128 
 int /*<<< orphan*/  REG_SZ ; 
 int /*<<< orphan*/  UTF16_HOST_ENDIAN ; 
 int /*<<< orphan*/  VM_PKT_DATA_INBAND ; 
 TYPE_6__ kvp_transaction ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int process_ob_ipinfo (struct hv_kvp_msg*,struct hv_kvp_ip_msg*,int const) ; 
 int /*<<< orphan*/ * recv_buffer ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int utf8s_to_utf16s (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmbus_sendpacket (struct vmbus_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kvp_respond_to_host(struct hv_kvp_msg *msg_to_host, int error)
{
	struct hv_kvp_msg  *kvp_msg;
	struct hv_kvp_exchg_msg_value  *kvp_data;
	char	*key_name;
	char	*value;
	struct icmsg_hdr *icmsghdrp;
	int	keylen = 0;
	int	valuelen = 0;
	u32	buf_len;
	struct vmbus_channel *channel;
	u64	req_id;
	int ret;

	/*
	 * If a transaction is not active; log and return.
	 */

	if (!kvp_transaction.active) {
		/*
		 * This is a spurious call!
		 */
		pr_warn("KVP: Transaction not active\n");
		return;
	}
	/*
	 * Copy the global state for completing the transaction. Note that
	 * only one transaction can be active at a time.
	 */

	buf_len = kvp_transaction.recv_len;
	channel = kvp_transaction.recv_channel;
	req_id = kvp_transaction.recv_req_id;

	kvp_transaction.active = false;

	icmsghdrp = (struct icmsg_hdr *)
			&recv_buffer[sizeof(struct vmbuspipe_hdr)];

	if (channel->onchannel_callback == NULL)
		/*
		 * We have raced with util driver being unloaded;
		 * silently return.
		 */
		return;

	icmsghdrp->status = error;

	/*
	 * If the error parameter is set, terminate the host's enumeration
	 * on this pool.
	 */
	if (error) {
		/*
		 * Something failed or we have timedout;
		 * terminate the current host-side iteration.
		 */
		goto response_done;
	}

	kvp_msg = (struct hv_kvp_msg *)
			&recv_buffer[sizeof(struct vmbuspipe_hdr) +
			sizeof(struct icmsg_hdr)];

	switch (kvp_transaction.kvp_msg->kvp_hdr.operation) {
	case KVP_OP_GET_IP_INFO:
		ret = process_ob_ipinfo(msg_to_host,
				 (struct hv_kvp_ip_msg *)kvp_msg,
				 KVP_OP_GET_IP_INFO);
		if (ret < 0)
			icmsghdrp->status = HV_E_FAIL;

		goto response_done;
	case KVP_OP_SET_IP_INFO:
		goto response_done;
	case KVP_OP_GET:
		kvp_data = &kvp_msg->body.kvp_get.data;
		goto copy_value;

	case KVP_OP_SET:
	case KVP_OP_DELETE:
		goto response_done;

	default:
		break;
	}

	kvp_data = &kvp_msg->body.kvp_enum_data.data;
	key_name = msg_to_host->body.kvp_enum_data.data.key;

	/*
	 * The windows host expects the key/value pair to be encoded
	 * in utf16. Ensure that the key/value size reported to the host
	 * will be less than or equal to the MAX size (including the
	 * terminating character).
	 */
	keylen = utf8s_to_utf16s(key_name, strlen(key_name), UTF16_HOST_ENDIAN,
				(wchar_t *) kvp_data->key,
				(HV_KVP_EXCHANGE_MAX_KEY_SIZE / 2) - 2);
	kvp_data->key_size = 2*(keylen + 1); /* utf16 encoding */

copy_value:
	value = msg_to_host->body.kvp_enum_data.data.value;
	valuelen = utf8s_to_utf16s(value, strlen(value), UTF16_HOST_ENDIAN,
				(wchar_t *) kvp_data->value,
				(HV_KVP_EXCHANGE_MAX_VALUE_SIZE / 2) - 2);
	kvp_data->value_size = 2*(valuelen + 1); /* utf16 encoding */

	/*
	 * If the utf8s to utf16s conversion failed; notify host
	 * of the error.
	 */
	if ((keylen < 0) || (valuelen < 0))
		icmsghdrp->status = HV_E_FAIL;

	kvp_data->value_type = REG_SZ; /* all our values are strings */

response_done:
	icmsghdrp->icflags = ICMSGHDRFLAG_TRANSACTION | ICMSGHDRFLAG_RESPONSE;

	vmbus_sendpacket(channel, recv_buffer, buf_len, req_id,
				VM_PKT_DATA_INBAND, 0);

}