#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct CodaFid {int dummy; } ;
struct TYPE_10__ {struct CodaFid NewFid; struct CodaFid OldFid; } ;
struct TYPE_9__ {struct CodaFid CodaFid; } ;
struct TYPE_8__ {struct CodaFid CodaFid; } ;
struct TYPE_7__ {struct CodaFid CodaFid; } ;
union outputArgs {TYPE_5__ coda_replace; TYPE_4__ coda_purgefid; TYPE_3__ coda_zapfile; TYPE_2__ coda_zapdir; } ;
struct super_block {TYPE_1__* s_root; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {struct inode* d_inode; } ;

/* Variables and functions */
#define  CODA_FLUSH 133 
#define  CODA_PURGEFID 132 
#define  CODA_PURGEUSER 131 
#define  CODA_REPLACE 130 
#define  CODA_ZAPDIR 129 
#define  CODA_ZAPFILE 128 
 int /*<<< orphan*/  C_FLUSH ; 
 int /*<<< orphan*/  C_PURGE ; 
 int /*<<< orphan*/  C_VATTR ; 
 int /*<<< orphan*/  coda_cache_clear_all (struct super_block*) ; 
 struct inode* coda_fid_to_inode (struct CodaFid*,struct super_block*) ; 
 int /*<<< orphan*/  coda_flag_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_flag_inode_children (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_replace_fid (struct inode*,struct CodaFid*,struct CodaFid*) ; 
 int /*<<< orphan*/  d_prune_aliases (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  shrink_dcache_sb (struct super_block*) ; 

int coda_downcall(int opcode, union outputArgs * out, struct super_block *sb)
{
	struct inode *inode = NULL;
	struct CodaFid *fid, *newfid;

	/* Handle invalidation requests. */
	if ( !sb || !sb->s_root)
		return 0;

	switch (opcode) {
	case CODA_FLUSH:
		coda_cache_clear_all(sb);
		shrink_dcache_sb(sb);
		if (sb->s_root->d_inode)
		    coda_flag_inode(sb->s_root->d_inode, C_FLUSH);
		break;

	case CODA_PURGEUSER:
		coda_cache_clear_all(sb);
		break;

	case CODA_ZAPDIR:
		fid = &out->coda_zapdir.CodaFid;
		inode = coda_fid_to_inode(fid, sb);
		if (inode) {
			coda_flag_inode_children(inode, C_PURGE);
			coda_flag_inode(inode, C_VATTR);
		}
		break;

	case CODA_ZAPFILE:
		fid = &out->coda_zapfile.CodaFid;
		inode = coda_fid_to_inode(fid, sb);
		if (inode)
			coda_flag_inode(inode, C_VATTR);
		break;

	case CODA_PURGEFID:
		fid = &out->coda_purgefid.CodaFid;
		inode = coda_fid_to_inode(fid, sb);
		if (inode) {
			coda_flag_inode_children(inode, C_PURGE);

			/* catch the dentries later if some are still busy */
			coda_flag_inode(inode, C_PURGE);
			d_prune_aliases(inode);

		}
		break;

	case CODA_REPLACE:
		fid = &out->coda_replace.OldFid;
		newfid = &out->coda_replace.NewFid;
		inode = coda_fid_to_inode(fid, sb);
		if (inode)
			coda_replace_fid(inode, fid, newfid);
		break;
	}

	if (inode)
		iput(inode);

	return 0;
}