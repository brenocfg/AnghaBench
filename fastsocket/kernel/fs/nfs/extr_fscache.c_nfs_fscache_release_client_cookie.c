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
struct nfs_client {int /*<<< orphan*/ * fscache; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct nfs_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void nfs_fscache_release_client_cookie(struct nfs_client *clp)
{
	dfprintk(FSCACHE, "NFS: releasing client cookie (0x%p/0x%p)\n",
		 clp, clp->fscache);

	fscache_relinquish_cookie(clp->fscache, 0);
	clp->fscache = NULL;
}