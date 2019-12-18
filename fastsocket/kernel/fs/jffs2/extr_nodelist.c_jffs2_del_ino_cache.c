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
struct jffs2_sb_info {int /*<<< orphan*/  inocache_lock; struct jffs2_inode_cache** inocache_list; } ;
struct jffs2_inode_cache {size_t ino; scalar_t__ state; struct jffs2_inode_cache* next; int /*<<< orphan*/  xref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 size_t INOCACHE_HASHSIZE ; 
 scalar_t__ INO_STATE_CLEARING ; 
 scalar_t__ INO_STATE_READING ; 
 int /*<<< orphan*/  dbg_inocache (char*,struct jffs2_inode_cache*,size_t) ; 
 int /*<<< orphan*/  jffs2_free_inode_cache (struct jffs2_inode_cache*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void jffs2_del_ino_cache(struct jffs2_sb_info *c, struct jffs2_inode_cache *old)
{
	struct jffs2_inode_cache **prev;

#ifdef CONFIG_JFFS2_FS_XATTR
	BUG_ON(old->xref);
#endif
	dbg_inocache("del %p (ino #%u)\n", old, old->ino);
	spin_lock(&c->inocache_lock);

	prev = &c->inocache_list[old->ino % INOCACHE_HASHSIZE];

	while ((*prev) && (*prev)->ino < old->ino) {
		prev = &(*prev)->next;
	}
	if ((*prev) == old) {
		*prev = old->next;
	}

	/* Free it now unless it's in READING or CLEARING state, which
	   are the transitions upon read_inode() and clear_inode(). The
	   rest of the time we know nobody else is looking at it, and
	   if it's held by read_inode() or clear_inode() they'll free it
	   for themselves. */
	if (old->state != INO_STATE_READING && old->state != INO_STATE_CLEARING)
		jffs2_free_inode_cache(old);

	spin_unlock(&c->inocache_lock);
}