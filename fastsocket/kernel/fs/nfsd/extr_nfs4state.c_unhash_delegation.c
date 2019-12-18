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
struct nfs4_delegation {int /*<<< orphan*/  dl_recall_lru; int /*<<< orphan*/  dl_perclnt; int /*<<< orphan*/  dl_perfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_close_delegation (struct nfs4_delegation*) ; 
 int /*<<< orphan*/  nfs4_put_delegation (struct nfs4_delegation*) ; 
 int /*<<< orphan*/  recall_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
unhash_delegation(struct nfs4_delegation *dp)
{
	list_del_init(&dp->dl_perfile);
	list_del_init(&dp->dl_perclnt);
	spin_lock(&recall_lock);
	list_del_init(&dp->dl_recall_lru);
	spin_unlock(&recall_lock);
	nfs4_close_delegation(dp);
	nfs4_put_delegation(dp);
}