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
struct nfs4_file {int fi_had_conflict; int /*<<< orphan*/  fi_hash; int /*<<< orphan*/  fi_access; int /*<<< orphan*/  fi_fds; scalar_t__ fi_id; int /*<<< orphan*/  fi_inode; int /*<<< orphan*/  fi_delegations; int /*<<< orphan*/  fi_stateids; int /*<<< orphan*/  fi_ref; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current_fileid ; 
 int /*<<< orphan*/ * file_hashtbl ; 
 unsigned int file_hashval (struct inode*) ; 
 int /*<<< orphan*/  file_slab ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 struct nfs4_file* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recall_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct nfs4_file *
alloc_init_file(struct inode *ino)
{
	struct nfs4_file *fp;
	unsigned int hashval = file_hashval(ino);

	fp = kmem_cache_alloc(file_slab, GFP_KERNEL);
	if (fp) {
		atomic_set(&fp->fi_ref, 1);
		INIT_LIST_HEAD(&fp->fi_hash);
		INIT_LIST_HEAD(&fp->fi_stateids);
		INIT_LIST_HEAD(&fp->fi_delegations);
		fp->fi_inode = igrab(ino);
		fp->fi_id = current_fileid++;
		fp->fi_had_conflict = false;
		memset(fp->fi_fds, 0, sizeof(fp->fi_fds));
		memset(fp->fi_access, 0, sizeof(fp->fi_access));
		spin_lock(&recall_lock);
		list_add(&fp->fi_hash, &file_hashtbl[hashval]);
		spin_unlock(&recall_lock);
		return fp;
	}
	return NULL;
}