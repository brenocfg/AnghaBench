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
struct nfs4_stateowner {int dummy; } ;
struct nfs4_stateid {int dummy; } ;
struct nfs4_file {int dummy; } ;
struct nfs4_delegation {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * deleg_slab ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/ * file_slab ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd4_free_slabs () ; 
 int /*<<< orphan*/ * stateid_slab ; 
 int /*<<< orphan*/ * stateowner_slab ; 

__attribute__((used)) static int
nfsd4_init_slabs(void)
{
	stateowner_slab = kmem_cache_create("nfsd4_stateowners",
			sizeof(struct nfs4_stateowner), 0, 0, NULL);
	if (stateowner_slab == NULL)
		goto out_nomem;
	file_slab = kmem_cache_create("nfsd4_files",
			sizeof(struct nfs4_file), 0, 0, NULL);
	if (file_slab == NULL)
		goto out_nomem;
	stateid_slab = kmem_cache_create("nfsd4_stateids",
			sizeof(struct nfs4_stateid), 0, 0, NULL);
	if (stateid_slab == NULL)
		goto out_nomem;
	deleg_slab = kmem_cache_create("nfsd4_delegations",
			sizeof(struct nfs4_delegation), 0, 0, NULL);
	if (deleg_slab == NULL)
		goto out_nomem;
	return 0;
out_nomem:
	nfsd4_free_slabs();
	dprintk("nfsd4: out of memory while initializing nfsv4\n");
	return -ENOMEM;
}