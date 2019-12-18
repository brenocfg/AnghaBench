#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* mach_node_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
struct TYPE_4__ {int /*<<< orphan*/  bootstrap_port; } ;

/* Variables and functions */
 scalar_t__ IP_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_NODE_DOWN ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  MACH_NODE_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  flipc_port_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 

kern_return_t
flipc_node_retire(mach_node_t node)
{
    if (!MACH_NODE_VALID(node))
        return KERN_NODE_DOWN;

    ipc_port_t bs_port = node->bootstrap_port;
    if (IP_VALID(bs_port)) {
        ip_lock(bs_port);
        flipc_port_destroy(bs_port);
        ip_unlock(bs_port);
    }

    return KERN_SUCCESS;
}