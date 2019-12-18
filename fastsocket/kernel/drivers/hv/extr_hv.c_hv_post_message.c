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
typedef  union hv_connection_id {int dummy; } hv_connection_id ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct hv_input_post_message {int message_type; size_t payload_size; scalar_t__ payload; union hv_connection_id connectionid; } ;
typedef  enum hv_message_type { ____Placeholder_hv_message_type } hv_message_type ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HVCALL_POST_MESSAGE ; 
 int /*<<< orphan*/  HV_HYPERCALL_PARAM_ALIGN ; 
 size_t HV_MESSAGE_PAYLOAD_BYTE_COUNT ; 
 int do_hypercall (int /*<<< orphan*/ ,struct hv_input_post_message*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 scalar_t__ kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

int hv_post_message(union hv_connection_id connection_id,
		  enum hv_message_type message_type,
		  void *payload, size_t payload_size)
{
	struct aligned_input {
		u64 alignment8;
		struct hv_input_post_message msg;
	};

	struct hv_input_post_message *aligned_msg;
	u16 status;
	unsigned long addr;

	if (payload_size > HV_MESSAGE_PAYLOAD_BYTE_COUNT)
		return -EMSGSIZE;

	addr = (unsigned long)kmalloc(sizeof(struct aligned_input), GFP_ATOMIC);
	if (!addr)
		return -ENOMEM;

	aligned_msg = (struct hv_input_post_message *)
			(ALIGN(addr, HV_HYPERCALL_PARAM_ALIGN));

	aligned_msg->connectionid = connection_id;
	aligned_msg->message_type = message_type;
	aligned_msg->payload_size = payload_size;
	memcpy((void *)aligned_msg->payload, payload, payload_size);

	status = do_hypercall(HVCALL_POST_MESSAGE, aligned_msg, NULL)
		& 0xFFFF;

	kfree((void *)addr);

	return status;
}