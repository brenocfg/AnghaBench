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
struct nfs_access_entry {int /*<<< orphan*/  cred; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nfs_access_entry*) ; 
 int /*<<< orphan*/  nfs_access_nr_entries ; 
 int /*<<< orphan*/  put_rpccred (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb__after_atomic_dec () ; 
 int /*<<< orphan*/  smp_mb__before_atomic_dec () ; 

__attribute__((used)) static void nfs_access_free_entry(struct nfs_access_entry *entry)
{
	put_rpccred(entry->cred);
	kfree(entry);
	smp_mb__before_atomic_dec();
	atomic_long_dec(&nfs_access_nr_entries);
	smp_mb__after_atomic_dec();
}