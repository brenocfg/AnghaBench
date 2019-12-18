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
struct rpc_request_hdr {scalar_t__ type; scalar_t__ xid; scalar_t__ rpc_vers; scalar_t__ prog; scalar_t__ vers; scalar_t__ procedure; } ;

/* Variables and functions */
 scalar_t__ RPC_ADSP_RTOS_MTOA_PROG ; 
 scalar_t__ RPC_ADSP_RTOS_MTOA_VERS ; 
 void* be32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_adsp_rtos_mtoa (struct rpc_request_hdr*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int msm_rpc_read (int /*<<< orphan*/ ,void**,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  rpc_cb_server_client ; 

__attribute__((used)) static int adsp_rpc_thread(void *data)
{
	void *buffer;
	struct rpc_request_hdr *req;
	int rc;

	do {
		rc = msm_rpc_read(rpc_cb_server_client, &buffer, -1, -1);
		if (rc < 0) {
			pr_err("adsp: could not read rpc: %d\n", rc);
			break;
		}
		req = (struct rpc_request_hdr *)buffer;

		req->type = be32_to_cpu(req->type);
		req->xid = be32_to_cpu(req->xid);
		req->rpc_vers = be32_to_cpu(req->rpc_vers);
		req->prog = be32_to_cpu(req->prog);
		req->vers = be32_to_cpu(req->vers);
		req->procedure = be32_to_cpu(req->procedure);

		if (req->type != 0)
			goto bad_rpc;
		if (req->rpc_vers != 2)
			goto bad_rpc;
		if (req->prog != RPC_ADSP_RTOS_MTOA_PROG)
			goto bad_rpc;
		if (req->vers != RPC_ADSP_RTOS_MTOA_VERS)
			goto bad_rpc;

		handle_adsp_rtos_mtoa(req);
		kfree(buffer);
		continue;

bad_rpc:
		pr_err("adsp: bogus rpc from modem\n");
		kfree(buffer);
	} while (1);

	do_exit(0);
}