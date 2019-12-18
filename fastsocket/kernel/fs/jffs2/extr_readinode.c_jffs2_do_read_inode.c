#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct jffs2_sb_info {int /*<<< orphan*/  inocache_lock; int /*<<< orphan*/  inocache_wq; } ;
struct jffs2_raw_node_ref {int dummy; } ;
struct jffs2_raw_inode {int dummy; } ;
struct jffs2_inode_info {TYPE_1__* inocache; } ;
struct jffs2_inode_cache {int dummy; } ;
struct TYPE_5__ {int state; int ino; int pino_nlink; struct jffs2_raw_node_ref* nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int ENOENT ; 
 int ENOMEM ; 
#define  INO_STATE_CHECKEDABSENT 133 
#define  INO_STATE_CHECKING 132 
#define  INO_STATE_GC 131 
#define  INO_STATE_PRESENT 130 
#define  INO_STATE_READING 129 
#define  INO_STATE_UNCHECKED 128 
 int /*<<< orphan*/  JFFS2_ERROR (char*,...) ; 
 int /*<<< orphan*/  dbg_readinode (char*,...) ; 
 int /*<<< orphan*/  jffs2_add_ino_cache (struct jffs2_sb_info*,TYPE_1__*) ; 
 TYPE_1__* jffs2_alloc_inode_cache () ; 
 int jffs2_do_read_inode_internal (struct jffs2_sb_info*,struct jffs2_inode_info*,struct jffs2_raw_inode*) ; 
 TYPE_1__* jffs2_get_ino_cache (struct jffs2_sb_info*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sleep_on_spinunlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int jffs2_do_read_inode(struct jffs2_sb_info *c, struct jffs2_inode_info *f,
			uint32_t ino, struct jffs2_raw_inode *latest_node)
{
	dbg_readinode("read inode #%u\n", ino);

 retry_inocache:
	spin_lock(&c->inocache_lock);
	f->inocache = jffs2_get_ino_cache(c, ino);

	if (f->inocache) {
		/* Check its state. We may need to wait before we can use it */
		switch(f->inocache->state) {
		case INO_STATE_UNCHECKED:
		case INO_STATE_CHECKEDABSENT:
			f->inocache->state = INO_STATE_READING;
			break;

		case INO_STATE_CHECKING:
		case INO_STATE_GC:
			/* If it's in either of these states, we need
			   to wait for whoever's got it to finish and
			   put it back. */
			dbg_readinode("waiting for ino #%u in state %d\n", ino, f->inocache->state);
			sleep_on_spinunlock(&c->inocache_wq, &c->inocache_lock);
			goto retry_inocache;

		case INO_STATE_READING:
		case INO_STATE_PRESENT:
			/* Eep. This should never happen. It can
			happen if Linux calls read_inode() again
			before clear_inode() has finished though. */
			JFFS2_ERROR("Eep. Trying to read_inode #%u when it's already in state %d!\n", ino, f->inocache->state);
			/* Fail. That's probably better than allowing it to succeed */
			f->inocache = NULL;
			break;

		default:
			BUG();
		}
	}
	spin_unlock(&c->inocache_lock);

	if (!f->inocache && ino == 1) {
		/* Special case - no root inode on medium */
		f->inocache = jffs2_alloc_inode_cache();
		if (!f->inocache) {
			JFFS2_ERROR("cannot allocate inocache for root inode\n");
			return -ENOMEM;
		}
		dbg_readinode("creating inocache for root inode\n");
		memset(f->inocache, 0, sizeof(struct jffs2_inode_cache));
		f->inocache->ino = f->inocache->pino_nlink = 1;
		f->inocache->nodes = (struct jffs2_raw_node_ref *)f->inocache;
		f->inocache->state = INO_STATE_READING;
		jffs2_add_ino_cache(c, f->inocache);
	}
	if (!f->inocache) {
		JFFS2_ERROR("requestied to read an nonexistent ino %u\n", ino);
		return -ENOENT;
	}

	return jffs2_do_read_inode_internal(c, f, latest_node);
}