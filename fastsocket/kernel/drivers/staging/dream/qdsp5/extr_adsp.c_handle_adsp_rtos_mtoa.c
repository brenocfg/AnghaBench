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
struct rpc_request_hdr {int procedure; int /*<<< orphan*/  xid; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_ACCEPTSTAT_PROC_UNAVAIL ; 
 int /*<<< orphan*/  RPC_ACCEPTSTAT_SUCCESS ; 
#define  RPC_ADSP_RTOS_MODEM_TO_APP_PROC 129 
#define  RPC_ADSP_RTOS_MTOA_NULL_PROC 128 
 int /*<<< orphan*/  handle_adsp_rtos_mtoa_app (struct rpc_request_hdr*) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  rpc_cb_server_client ; 
 int /*<<< orphan*/  rpc_send_accepted_void_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_adsp_rtos_mtoa(struct rpc_request_hdr *req)
{
	switch (req->procedure) {
	case RPC_ADSP_RTOS_MTOA_NULL_PROC:
		rpc_send_accepted_void_reply(rpc_cb_server_client,
					     req->xid,
					     RPC_ACCEPTSTAT_SUCCESS);
		break;
	case RPC_ADSP_RTOS_MODEM_TO_APP_PROC:
		handle_adsp_rtos_mtoa_app(req);
		break;
	default:
		pr_err("adsp: unknowned proc %d\n", req->procedure);
		rpc_send_accepted_void_reply(
			rpc_cb_server_client, req->xid,
			RPC_ACCEPTSTAT_PROC_UNAVAIL);
		break;
	}
	return 0;
}