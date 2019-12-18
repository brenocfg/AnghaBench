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
struct super_block {int dummy; } ;
struct nfs_server {TYPE_1__* fscache_key; int /*<<< orphan*/ * fscache; } ;
struct TYPE_2__ {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE ; 
 struct nfs_server* NFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct nfs_server*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fscache_relinquish_cookie (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_fscache_keys ; 
 int /*<<< orphan*/  nfs_fscache_keys_lock ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs_fscache_release_super_cookie(struct super_block *sb)
{
	struct nfs_server *nfss = NFS_SB(sb);

	dfprintk(FSCACHE, "NFS: releasing superblock cookie (0x%p/0x%p)\n",
		 nfss, nfss->fscache);

	fscache_relinquish_cookie(nfss->fscache, 0);
	nfss->fscache = NULL;

	if (nfss->fscache_key) {
		spin_lock(&nfs_fscache_keys_lock);
		rb_erase(&nfss->fscache_key->node, &nfs_fscache_keys);
		spin_unlock(&nfs_fscache_keys_lock);
		kfree(nfss->fscache_key);
		nfss->fscache_key = NULL;
	}
}