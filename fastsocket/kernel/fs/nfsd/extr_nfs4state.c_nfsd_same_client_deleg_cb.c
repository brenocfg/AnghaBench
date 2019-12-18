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
struct nfs4_delegation {scalar_t__ dl_client; } ;
struct file_lock {scalar_t__ fl_lmops; scalar_t__ fl_owner; } ;

/* Variables and functions */

__attribute__((used)) static
int nfsd_same_client_deleg_cb(struct file_lock *onlist, struct file_lock *try)
{
	struct nfs4_delegation *onlistd =
		(struct nfs4_delegation *)onlist->fl_owner;
	struct nfs4_delegation *tryd =
		(struct nfs4_delegation *)try->fl_owner;

	if (onlist->fl_lmops != try->fl_lmops)
		return 0;

	return onlistd->dl_client == tryd->dl_client;
}