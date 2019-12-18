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
struct TYPE_2__ {int /*<<< orphan*/  proc_net; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*) ; 
 TYPE_1__ init_net ; 
 int /*<<< orphan*/ * proc_net_rpc ; 
 int /*<<< orphan*/  remove_proc_entry (char*,int /*<<< orphan*/ ) ; 

void
rpc_proc_exit(void)
{
	dprintk("RPC:       unregistering /proc/net/rpc\n");
	if (proc_net_rpc) {
		proc_net_rpc = NULL;
		remove_proc_entry("rpc", init_net.proc_net);
	}
}