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
struct nsproxy {int /*<<< orphan*/  ipc_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  exit_sem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ipc_ns (void*) ; 
 int /*<<< orphan*/  put_ipc_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipcns_install(struct nsproxy *nsproxy, void *ns)
{
	/* Ditch state from the old ipc namespace */
	exit_sem(current);
	put_ipc_ns(nsproxy->ipc_ns);
	nsproxy->ipc_ns = get_ipc_ns(ns);
	return 0;
}