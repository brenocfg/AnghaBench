#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qstr {int len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct TYPE_5__ {int /*<<< orphan*/  d_child; } ;
struct TYPE_4__ {char* name; int len; int /*<<< orphan*/  hash; } ;
struct dentry {char* d_iname; int /*<<< orphan*/  d_subdirs; TYPE_2__ d_u; int /*<<< orphan*/ * d_sb; int /*<<< orphan*/ * d_parent; int /*<<< orphan*/  d_alias; int /*<<< orphan*/  d_lru; int /*<<< orphan*/  d_hash; scalar_t__ d_mounted; int /*<<< orphan*/ * d_fsdata; int /*<<< orphan*/ * d_op; int /*<<< orphan*/ * d_inode; int /*<<< orphan*/  d_lock; int /*<<< orphan*/  d_flags; int /*<<< orphan*/  d_count; TYPE_1__ d_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  nr_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCACHE_UNHASHED ; 
 int DNAME_INLINE_LEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dcache_lock ; 
 int /*<<< orphan*/  dentry_cache ; 
 TYPE_3__ dentry_stat ; 
 int /*<<< orphan*/ * dget (struct dentry*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct dentry* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dentry*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dentry *d_alloc(struct dentry * parent, const struct qstr *name)
{
	struct dentry *dentry;
	char *dname;

	dentry = kmem_cache_alloc(dentry_cache, GFP_KERNEL);
	if (!dentry)
		return NULL;

	if (name->len > DNAME_INLINE_LEN-1) {
		dname = kmalloc(name->len + 1, GFP_KERNEL);
		if (!dname) {
			kmem_cache_free(dentry_cache, dentry); 
			return NULL;
		}
	} else  {
		dname = dentry->d_iname;
	}	
	dentry->d_name.name = dname;

	dentry->d_name.len = name->len;
	dentry->d_name.hash = name->hash;
	memcpy(dname, name->name, name->len);
	dname[name->len] = 0;

	atomic_set(&dentry->d_count, 1);
	dentry->d_flags = DCACHE_UNHASHED;
	spin_lock_init(&dentry->d_lock);
	dentry->d_inode = NULL;
	dentry->d_parent = NULL;
	dentry->d_sb = NULL;
	dentry->d_op = NULL;
	dentry->d_fsdata = NULL;
	dentry->d_mounted = 0;
	INIT_HLIST_NODE(&dentry->d_hash);
	INIT_LIST_HEAD(&dentry->d_lru);
	INIT_LIST_HEAD(&dentry->d_subdirs);
	INIT_LIST_HEAD(&dentry->d_alias);

	if (parent) {
		dentry->d_parent = dget(parent);
		dentry->d_sb = parent->d_sb;
	} else {
		INIT_LIST_HEAD(&dentry->d_u.d_child);
	}

	spin_lock(&dcache_lock);
	if (parent)
		list_add(&dentry->d_u.d_child, &parent->d_subdirs);
	dentry_stat.nr_dentry++;
	spin_unlock(&dcache_lock);

	return dentry;
}