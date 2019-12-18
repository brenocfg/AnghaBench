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
typedef  scalar_t__ uint32_t ;
struct audmgr {int /*<<< orphan*/  ept; } ;

/* Variables and functions */
 scalar_t__ AUDMGR_CB_FUNC_PTR ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  process_audmgr_callback (struct audmgr*,void*,int) ; 
 int /*<<< orphan*/  rpc_ack (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void process_rpc_request(uint32_t proc, uint32_t xid,
				void *data, int len, void *private)
{
	struct audmgr *am = private;
	uint32_t *x = data;

	if (0) {
		int n = len / 4;
		pr_info("rpc_call proc %d:", proc);
		while (n--)
			printk(" %08x", be32_to_cpu(*x++));
		printk("\n");
	}

	if (proc == AUDMGR_CB_FUNC_PTR)
		process_audmgr_callback(am, data, len);
	else
		pr_err("audmgr: unknown rpc proc %d\n", proc);
	rpc_ack(am->ept, xid);
}