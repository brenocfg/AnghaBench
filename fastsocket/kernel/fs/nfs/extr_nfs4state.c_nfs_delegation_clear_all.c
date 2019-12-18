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
struct nfs_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfs_delegation_mark_reclaim (struct nfs_client*) ; 
 int /*<<< orphan*/  nfs_delegation_reap_unclaimed (struct nfs_client*) ; 

__attribute__((used)) static void nfs_delegation_clear_all(struct nfs_client *clp)
{
	nfs_delegation_mark_reclaim(clp);
	nfs_delegation_reap_unclaimed(clp);
}