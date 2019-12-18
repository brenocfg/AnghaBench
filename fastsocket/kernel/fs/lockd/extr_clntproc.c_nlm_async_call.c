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
typedef  int /*<<< orphan*/  u32 ;
struct rpc_message {int /*<<< orphan*/ * rpc_resp; int /*<<< orphan*/ * rpc_argp; } ;
struct rpc_call_ops {int dummy; } ;
struct nlm_rqst {int /*<<< orphan*/  a_res; int /*<<< orphan*/  a_args; } ;

/* Variables and functions */
 int nlm_do_async_call (struct nlm_rqst*,int /*<<< orphan*/ ,struct rpc_message*,struct rpc_call_ops const*) ; 

int nlm_async_call(struct nlm_rqst *req, u32 proc, const struct rpc_call_ops *tk_ops)
{
	struct rpc_message msg = {
		.rpc_argp	= &req->a_args,
		.rpc_resp	= &req->a_res,
	};
	return nlm_do_async_call(req, proc, &msg, tk_ops);
}