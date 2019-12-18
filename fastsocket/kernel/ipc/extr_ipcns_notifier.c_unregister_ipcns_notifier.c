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
struct ipc_namespace {scalar_t__ auto_msgmni; int /*<<< orphan*/  ipcns_nb; } ;

/* Variables and functions */
 int /*<<< orphan*/  blocking_notifier_chain_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipcns_chain ; 

void unregister_ipcns_notifier(struct ipc_namespace *ns)
{
	blocking_notifier_chain_unregister(&ipcns_chain, &ns->ipcns_nb);
	ns->auto_msgmni = 0;
}