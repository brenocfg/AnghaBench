#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_72__   TYPE_9__ ;
typedef  struct TYPE_71__   TYPE_8__ ;
typedef  struct TYPE_70__   TYPE_7__ ;
typedef  struct TYPE_69__   TYPE_6__ ;
typedef  struct TYPE_68__   TYPE_5__ ;
typedef  struct TYPE_67__   TYPE_4__ ;
typedef  struct TYPE_66__   TYPE_3__ ;
typedef  struct TYPE_65__   TYPE_2__ ;
typedef  struct TYPE_64__   TYPE_1__ ;
typedef  struct TYPE_63__   TYPE_17__ ;
typedef  struct TYPE_62__   TYPE_16__ ;
typedef  struct TYPE_61__   TYPE_15__ ;
typedef  struct TYPE_60__   TYPE_14__ ;
typedef  struct TYPE_59__   TYPE_13__ ;
typedef  struct TYPE_58__   TYPE_12__ ;
typedef  struct TYPE_57__   TYPE_11__ ;
typedef  struct TYPE_56__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_70__ {TYPE_1__* m_dirnameops; scalar_t__ m_dirblksize; } ;
typedef  TYPE_7__ xfs_mount_t ;
struct TYPE_67__ {scalar_t__ di_size; } ;
struct TYPE_65__ {int /*<<< orphan*/ * if_data; } ;
struct TYPE_66__ {int if_flags; int if_bytes; TYPE_2__ if_u1; } ;
struct TYPE_71__ {int /*<<< orphan*/  i_ino; TYPE_4__ i_d; TYPE_3__ i_df; TYPE_7__* i_mount; } ;
typedef  TYPE_8__ xfs_inode_t ;
struct TYPE_69__ {int count; int /*<<< orphan*/  parent; int /*<<< orphan*/  i8count; } ;
struct TYPE_72__ {TYPE_6__ hdr; } ;
typedef  TYPE_9__ xfs_dir2_sf_t ;
struct TYPE_56__ {int namelen; TYPE_9__* name; } ;
typedef  TYPE_10__ xfs_dir2_sf_entry_t ;
struct TYPE_57__ {void* address; void* hashval; } ;
typedef  TYPE_11__ xfs_dir2_leaf_entry_t ;
typedef  int /*<<< orphan*/  xfs_dir2_db_t ;
struct TYPE_58__ {void* length; void* freetag; } ;
typedef  TYPE_12__ xfs_dir2_data_unused_t ;
typedef  int /*<<< orphan*/  xfs_dir2_data_t ;
struct TYPE_59__ {int namelen; char* name; void* inumber; } ;
typedef  TYPE_13__ xfs_dir2_data_entry_t ;
typedef  scalar_t__ xfs_dir2_data_aoff_t ;
struct TYPE_60__ {void* count; scalar_t__ stale; } ;
typedef  TYPE_14__ xfs_dir2_block_tail_t ;
struct TYPE_68__ {void* magic; } ;
struct TYPE_61__ {scalar_t__ u; TYPE_5__ hdr; } ;
typedef  TYPE_15__ xfs_dir2_block_t ;
struct TYPE_62__ {TYPE_15__* data; } ;
typedef  TYPE_16__ xfs_dabuf_t ;
struct TYPE_63__ {int /*<<< orphan*/ * trans; TYPE_8__* dp; } ;
typedef  TYPE_17__ xfs_da_args_t ;
typedef  int uint ;
struct xfs_name {int len; TYPE_9__* name; } ;
typedef  void* __be16 ;
struct TYPE_64__ {int (* hashname ) (struct xfs_name*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  XFS_DATA_FORK ; 
 int XFS_DIR2_BLOCK_MAGIC ; 
 int XFS_DIR2_DATA_DOTDOT_OFFSET ; 
 int XFS_DIR2_DATA_DOT_OFFSET ; 
 int XFS_DIR2_DATA_FIRST_OFFSET ; 
 int XFS_DIR2_DATA_FREE_TAG ; 
 int /*<<< orphan*/  XFS_DIR2_DATA_SPACE ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int XFS_FORCED_SHUTDOWN (TYPE_7__*) ; 
 int XFS_IFINLINE ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int be16_to_cpu (void*) ; 
 scalar_t__ be32_to_cpu (void*) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 char* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,TYPE_9__*,int) ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parent ; 
 int stub1 (struct xfs_name*) ; 
 int /*<<< orphan*/  trace_xfs_dir2_sf_to_block (TYPE_17__*) ; 
 int /*<<< orphan*/  xfs_da_buf_done (TYPE_16__*) ; 
 TYPE_11__* xfs_dir2_block_leaf_p (TYPE_14__*) ; 
 int /*<<< orphan*/  xfs_dir2_block_log_leaf (int /*<<< orphan*/ *,TYPE_16__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_dir2_block_log_tail (int /*<<< orphan*/ *,TYPE_16__*) ; 
 int /*<<< orphan*/  xfs_dir2_block_sort ; 
 TYPE_14__* xfs_dir2_block_tail_p (TYPE_7__*,TYPE_15__*) ; 
 int xfs_dir2_byte_to_dataptr (TYPE_7__*,int) ; 
 int /*<<< orphan*/  xfs_dir2_data_check (TYPE_8__*,TYPE_16__*) ; 
 void** xfs_dir2_data_entry_tag_p (TYPE_13__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_freeinsert (int /*<<< orphan*/ *,TYPE_12__*,int*) ; 
 int xfs_dir2_data_init (TYPE_17__*,int /*<<< orphan*/ ,TYPE_16__**) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_entry (int /*<<< orphan*/ *,TYPE_16__*,TYPE_13__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_log_unused (int /*<<< orphan*/ *,TYPE_16__*,TYPE_12__*) ; 
 void** xfs_dir2_data_unused_tag_p (TYPE_12__*) ; 
 int /*<<< orphan*/  xfs_dir2_data_use_free (int /*<<< orphan*/ *,TYPE_16__*,TYPE_12__*,scalar_t__,int,int*,int*) ; 
 int xfs_dir2_grow_inode (TYPE_17__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_10__* xfs_dir2_sf_firstentry (TYPE_9__*) ; 
 int /*<<< orphan*/  xfs_dir2_sf_get_inumber (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int xfs_dir2_sf_get_offset (TYPE_10__*) ; 
 scalar_t__ xfs_dir2_sf_hdr_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_dir2_sf_hdr_t ; 
 int /*<<< orphan*/ * xfs_dir2_sf_inumberp (TYPE_10__*) ; 
 TYPE_10__* xfs_dir2_sf_nextentry (TYPE_9__*,TYPE_10__*) ; 
 int xfs_dir_hash_dot ; 
 int xfs_dir_hash_dotdot ; 
 int /*<<< orphan*/  xfs_idata_realloc (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sort (TYPE_11__*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ *,TYPE_8__*,int /*<<< orphan*/ ) ; 

int						/* error */
xfs_dir2_sf_to_block(
	xfs_da_args_t		*args)		/* operation arguments */
{
	xfs_dir2_db_t		blkno;		/* dir-relative block # (0) */
	xfs_dir2_block_t	*block;		/* block structure */
	xfs_dir2_leaf_entry_t	*blp;		/* block leaf entries */
	xfs_dabuf_t		*bp;		/* block buffer */
	xfs_dir2_block_tail_t	*btp;		/* block tail pointer */
	char			*buf;		/* sf buffer */
	int			buf_len;
	xfs_dir2_data_entry_t	*dep;		/* data entry pointer */
	xfs_inode_t		*dp;		/* incore directory inode */
	int			dummy;		/* trash */
	xfs_dir2_data_unused_t	*dup;		/* unused entry pointer */
	int			endoffset;	/* end of data objects */
	int			error;		/* error return value */
	int			i;		/* index */
	xfs_mount_t		*mp;		/* filesystem mount point */
	int			needlog;	/* need to log block header */
	int			needscan;	/* need to scan block freespc */
	int			newoffset;	/* offset from current entry */
	int			offset;		/* target block offset */
	xfs_dir2_sf_entry_t	*sfep;		/* sf entry pointer */
	xfs_dir2_sf_t		*sfp;		/* shortform structure */
	__be16			*tagp;		/* end of data entry */
	xfs_trans_t		*tp;		/* transaction pointer */
	struct xfs_name		name;

	trace_xfs_dir2_sf_to_block(args);

	dp = args->dp;
	tp = args->trans;
	mp = dp->i_mount;
	ASSERT(dp->i_df.if_flags & XFS_IFINLINE);
	/*
	 * Bomb out if the shortform directory is way too short.
	 */
	if (dp->i_d.di_size < offsetof(xfs_dir2_sf_hdr_t, parent)) {
		ASSERT(XFS_FORCED_SHUTDOWN(mp));
		return XFS_ERROR(EIO);
	}
	ASSERT(dp->i_df.if_bytes == dp->i_d.di_size);
	ASSERT(dp->i_df.if_u1.if_data != NULL);
	sfp = (xfs_dir2_sf_t *)dp->i_df.if_u1.if_data;
	ASSERT(dp->i_d.di_size >= xfs_dir2_sf_hdr_size(sfp->hdr.i8count));
	/*
	 * Copy the directory into the stack buffer.
	 * Then pitch the incore inode data so we can make extents.
	 */

	buf_len = dp->i_df.if_bytes;
	buf = kmem_alloc(buf_len, KM_SLEEP);

	memcpy(buf, sfp, buf_len);
	xfs_idata_realloc(dp, -buf_len, XFS_DATA_FORK);
	dp->i_d.di_size = 0;
	xfs_trans_log_inode(tp, dp, XFS_ILOG_CORE);
	/*
	 * Reset pointer - old sfp is gone.
	 */
	sfp = (xfs_dir2_sf_t *)buf;
	/*
	 * Add block 0 to the inode.
	 */
	error = xfs_dir2_grow_inode(args, XFS_DIR2_DATA_SPACE, &blkno);
	if (error) {
		kmem_free(buf);
		return error;
	}
	/*
	 * Initialize the data block.
	 */
	error = xfs_dir2_data_init(args, blkno, &bp);
	if (error) {
		kmem_free(buf);
		return error;
	}
	block = bp->data;
	block->hdr.magic = cpu_to_be32(XFS_DIR2_BLOCK_MAGIC);
	/*
	 * Compute size of block "tail" area.
	 */
	i = (uint)sizeof(*btp) +
	    (sfp->hdr.count + 2) * (uint)sizeof(xfs_dir2_leaf_entry_t);
	/*
	 * The whole thing is initialized to free by the init routine.
	 * Say we're using the leaf and tail area.
	 */
	dup = (xfs_dir2_data_unused_t *)block->u;
	needlog = needscan = 0;
	xfs_dir2_data_use_free(tp, bp, dup, mp->m_dirblksize - i, i, &needlog,
		&needscan);
	ASSERT(needscan == 0);
	/*
	 * Fill in the tail.
	 */
	btp = xfs_dir2_block_tail_p(mp, block);
	btp->count = cpu_to_be32(sfp->hdr.count + 2);	/* ., .. */
	btp->stale = 0;
	blp = xfs_dir2_block_leaf_p(btp);
	endoffset = (uint)((char *)blp - (char *)block);
	/*
	 * Remove the freespace, we'll manage it.
	 */
	xfs_dir2_data_use_free(tp, bp, dup,
		(xfs_dir2_data_aoff_t)((char *)dup - (char *)block),
		be16_to_cpu(dup->length), &needlog, &needscan);
	/*
	 * Create entry for .
	 */
	dep = (xfs_dir2_data_entry_t *)
	      ((char *)block + XFS_DIR2_DATA_DOT_OFFSET);
	dep->inumber = cpu_to_be64(dp->i_ino);
	dep->namelen = 1;
	dep->name[0] = '.';
	tagp = xfs_dir2_data_entry_tag_p(dep);
	*tagp = cpu_to_be16((char *)dep - (char *)block);
	xfs_dir2_data_log_entry(tp, bp, dep);
	blp[0].hashval = cpu_to_be32(xfs_dir_hash_dot);
	blp[0].address = cpu_to_be32(xfs_dir2_byte_to_dataptr(mp,
				(char *)dep - (char *)block));
	/*
	 * Create entry for ..
	 */
	dep = (xfs_dir2_data_entry_t *)
		((char *)block + XFS_DIR2_DATA_DOTDOT_OFFSET);
	dep->inumber = cpu_to_be64(xfs_dir2_sf_get_inumber(sfp, &sfp->hdr.parent));
	dep->namelen = 2;
	dep->name[0] = dep->name[1] = '.';
	tagp = xfs_dir2_data_entry_tag_p(dep);
	*tagp = cpu_to_be16((char *)dep - (char *)block);
	xfs_dir2_data_log_entry(tp, bp, dep);
	blp[1].hashval = cpu_to_be32(xfs_dir_hash_dotdot);
	blp[1].address = cpu_to_be32(xfs_dir2_byte_to_dataptr(mp,
				(char *)dep - (char *)block));
	offset = XFS_DIR2_DATA_FIRST_OFFSET;
	/*
	 * Loop over existing entries, stuff them in.
	 */
	if ((i = 0) == sfp->hdr.count)
		sfep = NULL;
	else
		sfep = xfs_dir2_sf_firstentry(sfp);
	/*
	 * Need to preserve the existing offset values in the sf directory.
	 * Insert holes (unused entries) where necessary.
	 */
	while (offset < endoffset) {
		/*
		 * sfep is null when we reach the end of the list.
		 */
		if (sfep == NULL)
			newoffset = endoffset;
		else
			newoffset = xfs_dir2_sf_get_offset(sfep);
		/*
		 * There should be a hole here, make one.
		 */
		if (offset < newoffset) {
			dup = (xfs_dir2_data_unused_t *)
			      ((char *)block + offset);
			dup->freetag = cpu_to_be16(XFS_DIR2_DATA_FREE_TAG);
			dup->length = cpu_to_be16(newoffset - offset);
			*xfs_dir2_data_unused_tag_p(dup) = cpu_to_be16(
				((char *)dup - (char *)block));
			xfs_dir2_data_log_unused(tp, bp, dup);
			(void)xfs_dir2_data_freeinsert((xfs_dir2_data_t *)block,
				dup, &dummy);
			offset += be16_to_cpu(dup->length);
			continue;
		}
		/*
		 * Copy a real entry.
		 */
		dep = (xfs_dir2_data_entry_t *)((char *)block + newoffset);
		dep->inumber = cpu_to_be64(xfs_dir2_sf_get_inumber(sfp,
				xfs_dir2_sf_inumberp(sfep)));
		dep->namelen = sfep->namelen;
		memcpy(dep->name, sfep->name, dep->namelen);
		tagp = xfs_dir2_data_entry_tag_p(dep);
		*tagp = cpu_to_be16((char *)dep - (char *)block);
		xfs_dir2_data_log_entry(tp, bp, dep);
		name.name = sfep->name;
		name.len = sfep->namelen;
		blp[2 + i].hashval = cpu_to_be32(mp->m_dirnameops->
							hashname(&name));
		blp[2 + i].address = cpu_to_be32(xfs_dir2_byte_to_dataptr(mp,
						 (char *)dep - (char *)block));
		offset = (int)((char *)(tagp + 1) - (char *)block);
		if (++i == sfp->hdr.count)
			sfep = NULL;
		else
			sfep = xfs_dir2_sf_nextentry(sfp, sfep);
	}
	/* Done with the temporary buffer */
	kmem_free(buf);
	/*
	 * Sort the leaf entries by hash value.
	 */
	xfs_sort(blp, be32_to_cpu(btp->count), sizeof(*blp), xfs_dir2_block_sort);
	/*
	 * Log the leaf entry area and tail.
	 * Already logged the header in data_init, ignore needlog.
	 */
	ASSERT(needscan == 0);
	xfs_dir2_block_log_leaf(tp, bp, 0, be32_to_cpu(btp->count) - 1);
	xfs_dir2_block_log_tail(tp, bp);
	xfs_dir2_data_check(dp, bp);
	xfs_da_buf_done(bp);
	return 0;
}