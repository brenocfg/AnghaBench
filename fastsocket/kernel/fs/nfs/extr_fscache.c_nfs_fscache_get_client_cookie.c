#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nfs_client {int /*<<< orphan*/  fscache; } ;
struct TYPE_2__ {int /*<<< orphan*/  primary_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct nfs_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfs_client*) ; 
 TYPE_1__ nfs_fscache_netfs ; 
 int /*<<< orphan*/  nfs_fscache_server_index_def ; 

void nfs_fscache_get_client_cookie(struct nfs_client *clp)
{
	/* create a cache index for looking up filehandles */
	clp->fscache = fscache_acquire_cookie(nfs_fscache_netfs.primary_index,
					      &nfs_fscache_server_index_def,
					      clp);
	dfprintk(FSCACHE, "NFS: get client cookie (0x%p/0x%p)\n",
		 clp, clp->fscache);
}