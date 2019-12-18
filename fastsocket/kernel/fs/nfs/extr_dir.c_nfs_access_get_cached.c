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
struct rpc_cred {int dummy; } ;
struct nfs_inode {int cache_validity; int /*<<< orphan*/  access_cache; int /*<<< orphan*/  access_cache_entry_lru; scalar_t__ attrtimeo; } ;
struct nfs_access_entry {int /*<<< orphan*/  lru; int /*<<< orphan*/  rb_node; int /*<<< orphan*/  mask; int /*<<< orphan*/  cred; scalar_t__ jiffies; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int ENOENT ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_INO_INVALID_ACCESS ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs_access_free_entry (struct nfs_access_entry*) ; 
 struct nfs_access_entry* nfs_access_search_rbtree (struct inode*,struct rpc_cred*) ; 
 int /*<<< orphan*/  nfs_access_zap_cache (struct inode*) ; 
 int /*<<< orphan*/  nfs_have_delegated_attributes (struct inode*) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time_in_range_open (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int nfs_access_get_cached(struct inode *inode, struct rpc_cred *cred, struct nfs_access_entry *res)
{
	struct nfs_inode *nfsi = NFS_I(inode);
	struct nfs_access_entry *cache;
	int err = -ENOENT;

	spin_lock(&inode->i_lock);
	if (nfsi->cache_validity & NFS_INO_INVALID_ACCESS)
		goto out_zap;
	cache = nfs_access_search_rbtree(inode, cred);
	if (cache == NULL)
		goto out;
	if (!nfs_have_delegated_attributes(inode) &&
	    !time_in_range_open(jiffies, cache->jiffies, cache->jiffies + nfsi->attrtimeo))
		goto out_stale;
	res->jiffies = cache->jiffies;
	res->cred = cache->cred;
	res->mask = cache->mask;
	list_move_tail(&cache->lru, &nfsi->access_cache_entry_lru);
	err = 0;
out:
	spin_unlock(&inode->i_lock);
	return err;
out_stale:
	rb_erase(&cache->rb_node, &nfsi->access_cache);
	list_del(&cache->lru);
	spin_unlock(&inode->i_lock);
	nfs_access_free_entry(cache);
	return -ENOENT;
out_zap:
	spin_unlock(&inode->i_lock);
	nfs_access_zap_cache(inode);
	return -ENOENT;
}