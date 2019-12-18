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
struct TYPE_3__ {int operation; } ;
struct hv_kvp_msg {TYPE_1__ kvp_hdr; } ;
struct TYPE_4__ {int active; scalar_t__ kvp_context; } ;

/* Variables and functions */
#define  KVP_OP_REGISTER 129 
#define  KVP_OP_REGISTER1 128 
 int dm_reg_value ; 
 int /*<<< orphan*/  hv_kvp_onchannelcallback (scalar_t__) ; 
 int /*<<< orphan*/  kvp_register (int) ; 
 TYPE_2__ kvp_transaction ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int kvp_handle_handshake(struct hv_kvp_msg *msg)
{
	int ret = 1;

	switch (msg->kvp_hdr.operation) {
	case KVP_OP_REGISTER:
		dm_reg_value = KVP_OP_REGISTER;
		pr_info("KVP: IP injection functionality not available\n");
		pr_info("KVP: Upgrade the KVP daemon\n");
		break;
	case KVP_OP_REGISTER1:
		dm_reg_value = KVP_OP_REGISTER1;
		break;
	default:
		pr_info("KVP: incompatible daemon\n");
		pr_info("KVP: KVP version: %d, Daemon version: %d\n",
			KVP_OP_REGISTER1, msg->kvp_hdr.operation);
		ret = 0;
	}

	if (ret) {
		/*
		 * We have a compatible daemon; complete the handshake.
		 */
		pr_info("KVP: user-mode registering done.\n");
		kvp_register(dm_reg_value);
		kvp_transaction.active = false;
		if (kvp_transaction.kvp_context)
			hv_kvp_onchannelcallback(kvp_transaction.kvp_context);
	}
	return ret;
}