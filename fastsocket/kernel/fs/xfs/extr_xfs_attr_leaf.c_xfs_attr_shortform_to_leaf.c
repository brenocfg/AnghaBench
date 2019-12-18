#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_4__* i_afp; } ;
typedef  TYPE_3__ xfs_inode_t ;
struct TYPE_18__ {char* if_data; } ;
struct TYPE_21__ {TYPE_1__ if_u1; } ;
typedef  TYPE_4__ xfs_ifork_t ;
typedef  int /*<<< orphan*/  xfs_dabuf_t ;
typedef  scalar_t__ xfs_dablk_t ;
struct TYPE_22__ {size_t namelen; int /*<<< orphan*/  flags; int /*<<< orphan*/  hashval; int /*<<< orphan*/  valuelen; int /*<<< orphan*/ * value; int /*<<< orphan*/ * name; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  trans; int /*<<< orphan*/  whichfork; int /*<<< orphan*/  total; int /*<<< orphan*/  flist; int /*<<< orphan*/  firstblock; TYPE_3__* dp; } ;
typedef  TYPE_5__ xfs_da_args_t ;
struct TYPE_19__ {int count; int /*<<< orphan*/  totsize; } ;
struct TYPE_23__ {TYPE_2__ hdr; TYPE_7__* list; } ;
typedef  TYPE_6__ xfs_attr_shortform_t ;
struct TYPE_24__ {size_t namelen; int /*<<< orphan*/  flags; int /*<<< orphan*/ * nameval; int /*<<< orphan*/  valuelen; } ;
typedef  TYPE_7__ xfs_attr_sf_entry_t ;
typedef  int /*<<< orphan*/  nargs ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EIO ; 
 int ENOATTR ; 
 int ENOSPC ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_ATTR_NSP_ONDISK_TO_ARGS (int /*<<< orphan*/ ) ; 
 TYPE_7__* XFS_ATTR_SF_NEXTENTRY (TYPE_7__*) ; 
 int /*<<< orphan*/  XFS_DA_OP_OKNOENT ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 char* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_xfs_attr_sf_to_leaf (TYPE_5__*) ; 
 int xfs_attr_leaf_add (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int xfs_attr_leaf_create (TYPE_5__*,scalar_t__,int /*<<< orphan*/ **) ; 
 int xfs_attr_leaf_lookup_int (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  xfs_da_buf_done (int /*<<< orphan*/ *) ; 
 int xfs_da_grow_inode (TYPE_5__*,scalar_t__*) ; 
 int /*<<< orphan*/  xfs_da_hashname (int /*<<< orphan*/ *,size_t) ; 
 int xfs_da_shrink_inode (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_idata_realloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

int
xfs_attr_shortform_to_leaf(xfs_da_args_t *args)
{
	xfs_inode_t *dp;
	xfs_attr_shortform_t *sf;
	xfs_attr_sf_entry_t *sfe;
	xfs_da_args_t nargs;
	char *tmpbuffer;
	int error, i, size;
	xfs_dablk_t blkno;
	xfs_dabuf_t *bp;
	xfs_ifork_t *ifp;

	trace_xfs_attr_sf_to_leaf(args);

	dp = args->dp;
	ifp = dp->i_afp;
	sf = (xfs_attr_shortform_t *)ifp->if_u1.if_data;
	size = be16_to_cpu(sf->hdr.totsize);
	tmpbuffer = kmem_alloc(size, KM_SLEEP);
	ASSERT(tmpbuffer != NULL);
	memcpy(tmpbuffer, ifp->if_u1.if_data, size);
	sf = (xfs_attr_shortform_t *)tmpbuffer;

	xfs_idata_realloc(dp, -size, XFS_ATTR_FORK);
	bp = NULL;
	error = xfs_da_grow_inode(args, &blkno);
	if (error) {
		/*
		 * If we hit an IO error middle of the transaction inside
		 * grow_inode(), we may have inconsistent data. Bail out.
		 */
		if (error == EIO)
			goto out;
		xfs_idata_realloc(dp, size, XFS_ATTR_FORK);	/* try to put */
		memcpy(ifp->if_u1.if_data, tmpbuffer, size);	/* it back */
		goto out;
	}

	ASSERT(blkno == 0);
	error = xfs_attr_leaf_create(args, blkno, &bp);
	if (error) {
		error = xfs_da_shrink_inode(args, 0, bp);
		bp = NULL;
		if (error)
			goto out;
		xfs_idata_realloc(dp, size, XFS_ATTR_FORK);	/* try to put */
		memcpy(ifp->if_u1.if_data, tmpbuffer, size);	/* it back */
		goto out;
	}

	memset((char *)&nargs, 0, sizeof(nargs));
	nargs.dp = dp;
	nargs.firstblock = args->firstblock;
	nargs.flist = args->flist;
	nargs.total = args->total;
	nargs.whichfork = XFS_ATTR_FORK;
	nargs.trans = args->trans;
	nargs.op_flags = XFS_DA_OP_OKNOENT;

	sfe = &sf->list[0];
	for (i = 0; i < sf->hdr.count; i++) {
		nargs.name = sfe->nameval;
		nargs.namelen = sfe->namelen;
		nargs.value = &sfe->nameval[nargs.namelen];
		nargs.valuelen = sfe->valuelen;
		nargs.hashval = xfs_da_hashname(sfe->nameval,
						sfe->namelen);
		nargs.flags = XFS_ATTR_NSP_ONDISK_TO_ARGS(sfe->flags);
		error = xfs_attr_leaf_lookup_int(bp, &nargs); /* set a->index */
		ASSERT(error == ENOATTR);
		error = xfs_attr_leaf_add(bp, &nargs);
		ASSERT(error != ENOSPC);
		if (error)
			goto out;
		sfe = XFS_ATTR_SF_NEXTENTRY(sfe);
	}
	error = 0;

out:
	if(bp)
		xfs_da_buf_done(bp);
	kmem_free(tmpbuffer);
	return(error);
}