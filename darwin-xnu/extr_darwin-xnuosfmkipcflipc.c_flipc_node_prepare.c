#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* mach_node_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
struct TYPE_6__ {int /*<<< orphan*/  node_id; } ;
struct TYPE_7__ {TYPE_1__ info; int /*<<< orphan*/  bootstrap_port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IP_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_NODE_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  MNL_NAME_BOOTSTRAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flipc_port_create (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_unlock (int /*<<< orphan*/ ) ; 

kern_return_t
flipc_node_prepare(mach_node_t node)
{
    kern_return_t kr;

    assert(MACH_NODE_VALID(node));
    ipc_port_t bs_port = node->bootstrap_port;
    assert(IP_VALID(bs_port));

    ip_lock(bs_port);

    kr = flipc_port_create(bs_port,
                           node,
                           MNL_NAME_BOOTSTRAP(node->info.node_id));
    ip_unlock(bs_port);

    return kr;
}