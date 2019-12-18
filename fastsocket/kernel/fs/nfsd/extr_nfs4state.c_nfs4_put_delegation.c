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
struct nfs4_delegation {int /*<<< orphan*/  dl_file; int /*<<< orphan*/  dl_count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  deleg_slab ; 
 int /*<<< orphan*/  dprintk (char*,struct nfs4_delegation*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct nfs4_delegation*) ; 
 int /*<<< orphan*/  num_delegations ; 
 int /*<<< orphan*/  put_nfs4_file (int /*<<< orphan*/ ) ; 

void
nfs4_put_delegation(struct nfs4_delegation *dp)
{
	if (atomic_dec_and_test(&dp->dl_count)) {
		dprintk("NFSD: freeing dp %p\n",dp);
		put_nfs4_file(dp->dl_file);
		kmem_cache_free(deleg_slab, dp);
		num_delegations--;
	}
}