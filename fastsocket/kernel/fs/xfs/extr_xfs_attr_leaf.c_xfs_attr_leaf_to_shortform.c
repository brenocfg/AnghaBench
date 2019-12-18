#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_20__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ di_format; } ;
struct TYPE_25__ {TYPE_2__ i_d; TYPE_20__* i_mount; } ;
typedef  TYPE_4__ xfs_inode_t ;
struct TYPE_26__ {char* data; } ;
typedef  TYPE_5__ xfs_dabuf_t ;
struct TYPE_27__ {size_t namelen; int valuelen; int /*<<< orphan*/  flags; int /*<<< orphan*/  hashval; int /*<<< orphan*/ * value; int /*<<< orphan*/ * name; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  trans; int /*<<< orphan*/  whichfork; int /*<<< orphan*/  total; int /*<<< orphan*/  flist; int /*<<< orphan*/  firstblock; TYPE_4__* dp; } ;
typedef  TYPE_6__ xfs_da_args_t ;
struct TYPE_21__ {int /*<<< orphan*/  magic; } ;
struct TYPE_24__ {int /*<<< orphan*/  count; TYPE_1__ info; } ;
struct TYPE_28__ {TYPE_3__ hdr; TYPE_9__* entries; } ;
typedef  TYPE_7__ xfs_attr_leafblock_t ;
struct TYPE_29__ {size_t namelen; int /*<<< orphan*/  valuelen; int /*<<< orphan*/ * nameval; } ;
typedef  TYPE_8__ xfs_attr_leaf_name_local_t ;
struct TYPE_30__ {int flags; int /*<<< orphan*/  hashval; int /*<<< orphan*/  nameidx; } ;
typedef  TYPE_9__ xfs_attr_leaf_entry_t ;
typedef  int /*<<< orphan*/  nargs ;
struct TYPE_22__ {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int XFS_ATTR_INCOMPLETE ; 
 int XFS_ATTR_LEAF_MAGIC ; 
 int XFS_ATTR_LOCAL ; 
 int /*<<< orphan*/  XFS_ATTR_NSP_ONDISK_TO_ARGS (int) ; 
 int /*<<< orphan*/  XFS_DA_OP_OKNOENT ; 
 scalar_t__ XFS_DINODE_FMT_BTREE ; 
 int XFS_LBSIZE (TYPE_20__*) ; 
 int XFS_MOUNT_ATTR2 ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 char* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_xfs_attr_leaf_to_sf (TYPE_6__*) ; 
 int /*<<< orphan*/  xfs_attr_fork_reset (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* xfs_attr_leaf_name_local (TYPE_7__*,int) ; 
 int /*<<< orphan*/  xfs_attr_shortform_add (TYPE_6__*,int) ; 
 int /*<<< orphan*/  xfs_attr_shortform_create (TYPE_6__*) ; 
 int xfs_da_shrink_inode (TYPE_6__*,int /*<<< orphan*/ ,TYPE_5__*) ; 

int
xfs_attr_leaf_to_shortform(xfs_dabuf_t *bp, xfs_da_args_t *args, int forkoff)
{
	xfs_attr_leafblock_t *leaf;
	xfs_attr_leaf_entry_t *entry;
	xfs_attr_leaf_name_local_t *name_loc;
	xfs_da_args_t nargs;
	xfs_inode_t *dp;
	char *tmpbuffer;
	int error, i;

	trace_xfs_attr_leaf_to_sf(args);

	dp = args->dp;
	tmpbuffer = kmem_alloc(XFS_LBSIZE(dp->i_mount), KM_SLEEP);
	ASSERT(tmpbuffer != NULL);

	ASSERT(bp != NULL);
	memcpy(tmpbuffer, bp->data, XFS_LBSIZE(dp->i_mount));
	leaf = (xfs_attr_leafblock_t *)tmpbuffer;
	ASSERT(be16_to_cpu(leaf->hdr.info.magic) == XFS_ATTR_LEAF_MAGIC);
	memset(bp->data, 0, XFS_LBSIZE(dp->i_mount));

	/*
	 * Clean out the prior contents of the attribute list.
	 */
	error = xfs_da_shrink_inode(args, 0, bp);
	if (error)
		goto out;

	if (forkoff == -1) {
		ASSERT(dp->i_mount->m_flags & XFS_MOUNT_ATTR2);
		ASSERT(dp->i_d.di_format != XFS_DINODE_FMT_BTREE);
		xfs_attr_fork_reset(dp, args->trans);
		goto out;
	}

	xfs_attr_shortform_create(args);

	/*
	 * Copy the attributes
	 */
	memset((char *)&nargs, 0, sizeof(nargs));
	nargs.dp = dp;
	nargs.firstblock = args->firstblock;
	nargs.flist = args->flist;
	nargs.total = args->total;
	nargs.whichfork = XFS_ATTR_FORK;
	nargs.trans = args->trans;
	nargs.op_flags = XFS_DA_OP_OKNOENT;
	entry = &leaf->entries[0];
	for (i = 0; i < be16_to_cpu(leaf->hdr.count); entry++, i++) {
		if (entry->flags & XFS_ATTR_INCOMPLETE)
			continue;	/* don't copy partial entries */
		if (!entry->nameidx)
			continue;
		ASSERT(entry->flags & XFS_ATTR_LOCAL);
		name_loc = xfs_attr_leaf_name_local(leaf, i);
		nargs.name = name_loc->nameval;
		nargs.namelen = name_loc->namelen;
		nargs.value = &name_loc->nameval[nargs.namelen];
		nargs.valuelen = be16_to_cpu(name_loc->valuelen);
		nargs.hashval = be32_to_cpu(entry->hashval);
		nargs.flags = XFS_ATTR_NSP_ONDISK_TO_ARGS(entry->flags);
		xfs_attr_shortform_add(&nargs, forkoff);
	}
	error = 0;

out:
	kmem_free(tmpbuffer);
	return(error);
}