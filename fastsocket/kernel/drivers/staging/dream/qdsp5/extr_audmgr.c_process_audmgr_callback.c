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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  volume; int /*<<< orphan*/  handle; } ;
struct rpc_audmgr_cb_func_ptr {TYPE_1__ u; int /*<<< orphan*/  status; int /*<<< orphan*/  set_to_one; } ;
struct audmgr {int handle; int /*<<< orphan*/  wait; int /*<<< orphan*/  state; } ;

/* Variables and functions */
#define  RPC_AUDMGR_STATUS_CODEC_CONFIG 135 
#define  RPC_AUDMGR_STATUS_DISABLED 134 
#define  RPC_AUDMGR_STATUS_ERROR 133 
#define  RPC_AUDMGR_STATUS_FAILURE 132 
#define  RPC_AUDMGR_STATUS_PENDING 131 
#define  RPC_AUDMGR_STATUS_READY 130 
#define  RPC_AUDMGR_STATUS_SUSPEND 129 
#define  RPC_AUDMGR_STATUS_VOLUME_CHANGE 128 
 int /*<<< orphan*/  STATE_DISABLED ; 
 int /*<<< orphan*/  STATE_ENABLED ; 
 int /*<<< orphan*/  STATE_ERROR ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_audmgr_callback(struct audmgr *am,
				   struct rpc_audmgr_cb_func_ptr *args,
				   int len)
{
	if (len < (sizeof(uint32_t) * 3))
		return;
	if (be32_to_cpu(args->set_to_one) != 1)
		return;

	switch (be32_to_cpu(args->status)) {
	case RPC_AUDMGR_STATUS_READY:
		if (len < sizeof(uint32_t) * 4)
			break;
		am->handle = be32_to_cpu(args->u.handle);
		pr_info("audmgr: rpc READY handle=0x%08x\n", am->handle);
		break;
	case RPC_AUDMGR_STATUS_CODEC_CONFIG: {
		uint32_t volume;
		if (len < sizeof(uint32_t) * 4)
			break;
		volume = be32_to_cpu(args->u.volume);
		pr_info("audmgr: rpc CODEC_CONFIG volume=0x%08x\n", volume);
		am->state = STATE_ENABLED;
		wake_up(&am->wait);
		break;
	}
	case RPC_AUDMGR_STATUS_PENDING:
		pr_err("audmgr: PENDING?\n");
		break;
	case RPC_AUDMGR_STATUS_SUSPEND:
		pr_err("audmgr: SUSPEND?\n");
		break;
	case RPC_AUDMGR_STATUS_FAILURE:
		pr_err("audmgr: FAILURE\n");
		break;
	case RPC_AUDMGR_STATUS_VOLUME_CHANGE:
		pr_err("audmgr: VOLUME_CHANGE?\n");
		break;
	case RPC_AUDMGR_STATUS_DISABLED:
		pr_err("audmgr: DISABLED\n");
		am->state = STATE_DISABLED;
		wake_up(&am->wait);
		break;
	case RPC_AUDMGR_STATUS_ERROR:
		pr_err("audmgr: ERROR?\n");
		am->state = STATE_ERROR;
		wake_up(&am->wait);
		break;
	default:
		break;
	}
}