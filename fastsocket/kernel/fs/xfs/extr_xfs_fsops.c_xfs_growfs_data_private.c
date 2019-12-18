#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_54__   TYPE_6__ ;
typedef  struct TYPE_53__   TYPE_5__ ;
typedef  struct TYPE_52__   TYPE_4__ ;
typedef  struct TYPE_51__   TYPE_3__ ;
typedef  struct TYPE_50__   TYPE_2__ ;
typedef  struct TYPE_49__   TYPE_1__ ;
typedef  struct TYPE_48__   TYPE_16__ ;

/* Type definitions */
struct TYPE_51__ {int /*<<< orphan*/  t_flags; } ;
typedef  TYPE_3__ xfs_trans_t ;
typedef  scalar_t__ xfs_rfsblock_t ;
struct TYPE_48__ {scalar_t__ sb_dblocks; int sb_imax_pct; int sb_agblocks; int sb_agcount; scalar_t__ sb_inopblog; int /*<<< orphan*/  sb_blocksize; int /*<<< orphan*/  sb_sectsize; } ;
struct TYPE_52__ {int m_maxagi; TYPE_16__ m_sb; int /*<<< orphan*/  m_ddev_targp; scalar_t__ m_maxicount; } ;
typedef  TYPE_4__ xfs_mount_t ;
struct TYPE_53__ {scalar_t__ newblocks; int imaxpct; } ;
typedef  TYPE_5__ xfs_growfs_data_t ;
typedef  scalar_t__ xfs_extlen_t ;
typedef  int /*<<< orphan*/  xfs_buf_t ;
struct TYPE_54__ {void* ar_blockcount; void* ar_startblock; } ;
typedef  TYPE_6__ xfs_alloc_rec_t ;
typedef  int xfs_agnumber_t ;
struct TYPE_49__ {void* bb_rightsib; void* bb_leftsib; } ;
struct TYPE_50__ {TYPE_1__ s; } ;
struct xfs_btree_block {void* agf_length; void* agi_length; TYPE_2__ bb_u; void* bb_numrecs; scalar_t__ bb_level; void* bb_magic; void** agi_unlinked; void* agi_dirino; void* agi_newino; scalar_t__ agi_freecount; void* agi_level; void* agi_root; scalar_t__ agi_count; void* agi_seqno; void* agi_versionnum; void* agi_magicnum; void* agf_longest; void* agf_freeblks; scalar_t__ agf_flcount; void* agf_fllast; scalar_t__ agf_flfirst; void** agf_levels; void** agf_roots; void* agf_seqno; void* agf_versionnum; void* agf_magicnum; } ;
typedef  struct xfs_btree_block xfs_agi_t ;
typedef  struct xfs_btree_block xfs_agf_t ;
typedef  scalar_t__ __uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BBTOB (scalar_t__) ; 
 scalar_t__ BTOBB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ NULLAGBLOCK ; 
 scalar_t__ NULLAGINO ; 
 int XBF_LOCK ; 
 int XBF_MAPPED ; 
 scalar_t__ XFS_ABTB_MAGIC ; 
 scalar_t__ XFS_ABTC_MAGIC ; 
 int /*<<< orphan*/  XFS_AGB_TO_DADDR (TYPE_4__*,int,scalar_t__) ; 
 int /*<<< orphan*/  XFS_AGB_TO_FSB (TYPE_4__*,int,scalar_t__) ; 
 int XFS_AGFL_SIZE (TYPE_4__*) ; 
 int /*<<< orphan*/  XFS_AGF_DADDR (TYPE_4__*) ; 
 int /*<<< orphan*/  XFS_AGF_LENGTH ; 
 scalar_t__ XFS_AGF_MAGIC ; 
 scalar_t__ XFS_AGF_VERSION ; 
 int /*<<< orphan*/  XFS_AGI_DADDR (TYPE_4__*) ; 
 int /*<<< orphan*/  XFS_AGI_LENGTH ; 
 scalar_t__ XFS_AGI_MAGIC ; 
 int XFS_AGI_UNLINKED_BUCKETS ; 
 scalar_t__ XFS_AGI_VERSION ; 
 int /*<<< orphan*/  XFS_AG_DADDR (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* XFS_ALLOC_REC_ADDR (TYPE_4__*,struct xfs_btree_block*,int) ; 
 scalar_t__ XFS_BNO_BLOCK (TYPE_4__*) ; 
 size_t XFS_BTNUM_BNOi ; 
 size_t XFS_BTNUM_CNTi ; 
 struct xfs_btree_block* XFS_BUF_TO_AGF (int /*<<< orphan*/ *) ; 
 struct xfs_btree_block* XFS_BUF_TO_AGI (int /*<<< orphan*/ *) ; 
 struct xfs_btree_block* XFS_BUF_TO_BLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFS_BUF_TO_SBP (int /*<<< orphan*/ *) ; 
 scalar_t__ XFS_CNT_BLOCK (TYPE_4__*) ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ XFS_FSB_TO_BB (TYPE_4__*,scalar_t__) ; 
 scalar_t__ XFS_FSS_TO_BB (TYPE_4__*,int) ; 
 int /*<<< orphan*/  XFS_GROWDATA_LOG_RES (TYPE_4__*) ; 
 int /*<<< orphan*/  XFS_GROWFS_SPACE_RES (TYPE_4__*) ; 
 scalar_t__ XFS_IBT_BLOCK (TYPE_4__*) ; 
 scalar_t__ XFS_IBT_MAGIC ; 
 scalar_t__ XFS_MIN_AG_BLOCKS ; 
 scalar_t__ XFS_PREALLOC_BLOCKS (TYPE_4__*) ; 
 int /*<<< orphan*/  XFS_SB_ALL_BITS ; 
 scalar_t__ XFS_SB_BLOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  XFS_TRANS_ABORT ; 
 int /*<<< orphan*/  XFS_TRANS_GROWFS ; 
 int /*<<< orphan*/  XFS_TRANS_RESERVE ; 
 int /*<<< orphan*/  XFS_TRANS_SB_AGCOUNT ; 
 int /*<<< orphan*/  XFS_TRANS_SB_DBLOCKS ; 
 int /*<<< orphan*/  XFS_TRANS_SB_FDBLOCKS ; 
 int /*<<< orphan*/  XFS_TRANS_SB_IMAXPCT ; 
 int /*<<< orphan*/  be32_add_cpu (void**,scalar_t__) ; 
 scalar_t__ be32_to_cpu (void*) ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (scalar_t__) ; 
 scalar_t__ do_div (scalar_t__,int) ; 
 int /*<<< orphan*/  memset (struct xfs_btree_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_alloc_log_agf (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_alloc_read_agf (TYPE_4__*,TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * xfs_buf_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/ * xfs_buf_read_uncached (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_relse (int /*<<< orphan*/ *) ; 
 int xfs_bwrite (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int xfs_free_extent (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xfs_ialloc_log_agi (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int xfs_ialloc_read_agi (TYPE_4__*,TYPE_3__*,int,int /*<<< orphan*/ **) ; 
 int xfs_initialize_perag (TYPE_4__*,int,int*) ; 
 int xfs_read_buf (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  xfs_sb_to_disk (int /*<<< orphan*/ ,TYPE_16__*,int /*<<< orphan*/ ) ; 
 int xfs_sb_validate_fsb_count (TYPE_16__*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_set_low_space_thresholds (TYPE_4__*) ; 
 int /*<<< orphan*/  xfs_trans_agblocks_delta (TYPE_3__*,scalar_t__) ; 
 TYPE_3__* xfs_trans_alloc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_cancel (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int xfs_trans_commit (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_mod_sb (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int xfs_trans_reserve (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_warn (TYPE_4__*,char*,int,int) ; 

__attribute__((used)) static int
xfs_growfs_data_private(
	xfs_mount_t		*mp,		/* mount point for filesystem */
	xfs_growfs_data_t	*in)		/* growfs data input struct */
{
	xfs_agf_t		*agf;
	xfs_agi_t		*agi;
	xfs_agnumber_t		agno;
	xfs_extlen_t		agsize;
	xfs_extlen_t		tmpsize;
	xfs_alloc_rec_t		*arec;
	struct xfs_btree_block	*block;
	xfs_buf_t		*bp;
	int			bucket;
	int			dpct;
	int			error;
	xfs_agnumber_t		nagcount;
	xfs_agnumber_t		nagimax = 0;
	xfs_rfsblock_t		nb, nb_mod;
	xfs_rfsblock_t		new;
	xfs_rfsblock_t		nfree;
	xfs_agnumber_t		oagcount;
	int			pct;
	xfs_trans_t		*tp;

	nb = in->newblocks;
	pct = in->imaxpct;
	if (nb < mp->m_sb.sb_dblocks || pct < 0 || pct > 100)
		return XFS_ERROR(EINVAL);
	if ((error = xfs_sb_validate_fsb_count(&mp->m_sb, nb)))
		return error;
	dpct = pct - mp->m_sb.sb_imax_pct;
	bp = xfs_buf_read_uncached(mp, mp->m_ddev_targp,
				XFS_FSB_TO_BB(mp, nb) - XFS_FSS_TO_BB(mp, 1),
				BBTOB(XFS_FSS_TO_BB(mp, 1)), 0);
	if (!bp)
		return EIO;
	xfs_buf_relse(bp);

	new = nb;	/* use new as a temporary here */
	nb_mod = do_div(new, mp->m_sb.sb_agblocks);
	nagcount = new + (nb_mod != 0);
	if (nb_mod && nb_mod < XFS_MIN_AG_BLOCKS) {
		nagcount--;
		nb = (xfs_rfsblock_t)nagcount * mp->m_sb.sb_agblocks;
		if (nb < mp->m_sb.sb_dblocks)
			return XFS_ERROR(EINVAL);
	}
	new = nb - mp->m_sb.sb_dblocks;
	oagcount = mp->m_sb.sb_agcount;

	/* allocate the new per-ag structures */
	if (nagcount > oagcount) {
		error = xfs_initialize_perag(mp, nagcount, &nagimax);
		if (error)
			return error;
	}

	tp = xfs_trans_alloc(mp, XFS_TRANS_GROWFS);
	tp->t_flags |= XFS_TRANS_RESERVE;
	if ((error = xfs_trans_reserve(tp, XFS_GROWFS_SPACE_RES(mp),
			XFS_GROWDATA_LOG_RES(mp), 0, 0, 0))) {
		xfs_trans_cancel(tp, 0);
		return error;
	}

	/*
	 * Write new AG headers to disk. Non-transactional, but written
	 * synchronously so they are completed prior to the growfs transaction
	 * being logged.
	 */
	nfree = 0;
	for (agno = nagcount - 1; agno >= oagcount; agno--, new -= agsize) {
		/*
		 * AG freelist header block
		 */
		bp = xfs_buf_get(mp->m_ddev_targp,
				 XFS_AG_DADDR(mp, agno, XFS_AGF_DADDR(mp)),
				 XFS_FSS_TO_BB(mp, 1), XBF_LOCK | XBF_MAPPED);
		if (!bp) {
			error = ENOMEM;
			goto error0;
		}
		agf = XFS_BUF_TO_AGF(bp);
		memset(agf, 0, mp->m_sb.sb_sectsize);
		agf->agf_magicnum = cpu_to_be32(XFS_AGF_MAGIC);
		agf->agf_versionnum = cpu_to_be32(XFS_AGF_VERSION);
		agf->agf_seqno = cpu_to_be32(agno);
		if (agno == nagcount - 1)
			agsize =
				nb -
				(agno * (xfs_rfsblock_t)mp->m_sb.sb_agblocks);
		else
			agsize = mp->m_sb.sb_agblocks;
		agf->agf_length = cpu_to_be32(agsize);
		agf->agf_roots[XFS_BTNUM_BNOi] = cpu_to_be32(XFS_BNO_BLOCK(mp));
		agf->agf_roots[XFS_BTNUM_CNTi] = cpu_to_be32(XFS_CNT_BLOCK(mp));
		agf->agf_levels[XFS_BTNUM_BNOi] = cpu_to_be32(1);
		agf->agf_levels[XFS_BTNUM_CNTi] = cpu_to_be32(1);
		agf->agf_flfirst = 0;
		agf->agf_fllast = cpu_to_be32(XFS_AGFL_SIZE(mp) - 1);
		agf->agf_flcount = 0;
		tmpsize = agsize - XFS_PREALLOC_BLOCKS(mp);
		agf->agf_freeblks = cpu_to_be32(tmpsize);
		agf->agf_longest = cpu_to_be32(tmpsize);
		error = xfs_bwrite(mp, bp);
		if (error) {
			goto error0;
		}
		/*
		 * AG inode header block
		 */
		bp = xfs_buf_get(mp->m_ddev_targp,
				 XFS_AG_DADDR(mp, agno, XFS_AGI_DADDR(mp)),
				 XFS_FSS_TO_BB(mp, 1), XBF_LOCK | XBF_MAPPED);
		if (!bp) {
			error = ENOMEM;
			goto error0;
		}
		agi = XFS_BUF_TO_AGI(bp);
		memset(agi, 0, mp->m_sb.sb_sectsize);
		agi->agi_magicnum = cpu_to_be32(XFS_AGI_MAGIC);
		agi->agi_versionnum = cpu_to_be32(XFS_AGI_VERSION);
		agi->agi_seqno = cpu_to_be32(agno);
		agi->agi_length = cpu_to_be32(agsize);
		agi->agi_count = 0;
		agi->agi_root = cpu_to_be32(XFS_IBT_BLOCK(mp));
		agi->agi_level = cpu_to_be32(1);
		agi->agi_freecount = 0;
		agi->agi_newino = cpu_to_be32(NULLAGINO);
		agi->agi_dirino = cpu_to_be32(NULLAGINO);
		for (bucket = 0; bucket < XFS_AGI_UNLINKED_BUCKETS; bucket++)
			agi->agi_unlinked[bucket] = cpu_to_be32(NULLAGINO);
		error = xfs_bwrite(mp, bp);
		if (error) {
			goto error0;
		}
		/*
		 * BNO btree root block
		 */
		bp = xfs_buf_get(mp->m_ddev_targp,
				 XFS_AGB_TO_DADDR(mp, agno, XFS_BNO_BLOCK(mp)),
				 BTOBB(mp->m_sb.sb_blocksize),
				 XBF_LOCK | XBF_MAPPED);
		if (!bp) {
			error = ENOMEM;
			goto error0;
		}
		block = XFS_BUF_TO_BLOCK(bp);
		memset(block, 0, mp->m_sb.sb_blocksize);
		block->bb_magic = cpu_to_be32(XFS_ABTB_MAGIC);
		block->bb_level = 0;
		block->bb_numrecs = cpu_to_be16(1);
		block->bb_u.s.bb_leftsib = cpu_to_be32(NULLAGBLOCK);
		block->bb_u.s.bb_rightsib = cpu_to_be32(NULLAGBLOCK);
		arec = XFS_ALLOC_REC_ADDR(mp, block, 1);
		arec->ar_startblock = cpu_to_be32(XFS_PREALLOC_BLOCKS(mp));
		arec->ar_blockcount = cpu_to_be32(
			agsize - be32_to_cpu(arec->ar_startblock));
		error = xfs_bwrite(mp, bp);
		if (error) {
			goto error0;
		}
		/*
		 * CNT btree root block
		 */
		bp = xfs_buf_get(mp->m_ddev_targp,
				 XFS_AGB_TO_DADDR(mp, agno, XFS_CNT_BLOCK(mp)),
				 BTOBB(mp->m_sb.sb_blocksize),
				 XBF_LOCK | XBF_MAPPED);
		if (!bp) {
			error = ENOMEM;
			goto error0;
		}
		block = XFS_BUF_TO_BLOCK(bp);
		memset(block, 0, mp->m_sb.sb_blocksize);
		block->bb_magic = cpu_to_be32(XFS_ABTC_MAGIC);
		block->bb_level = 0;
		block->bb_numrecs = cpu_to_be16(1);
		block->bb_u.s.bb_leftsib = cpu_to_be32(NULLAGBLOCK);
		block->bb_u.s.bb_rightsib = cpu_to_be32(NULLAGBLOCK);
		arec = XFS_ALLOC_REC_ADDR(mp, block, 1);
		arec->ar_startblock = cpu_to_be32(XFS_PREALLOC_BLOCKS(mp));
		arec->ar_blockcount = cpu_to_be32(
			agsize - be32_to_cpu(arec->ar_startblock));
		nfree += be32_to_cpu(arec->ar_blockcount);
		error = xfs_bwrite(mp, bp);
		if (error) {
			goto error0;
		}
		/*
		 * INO btree root block
		 */
		bp = xfs_buf_get(mp->m_ddev_targp,
				 XFS_AGB_TO_DADDR(mp, agno, XFS_IBT_BLOCK(mp)),
				 BTOBB(mp->m_sb.sb_blocksize),
				 XBF_LOCK | XBF_MAPPED);
		if (!bp) {
			error = ENOMEM;
			goto error0;
		}
		block = XFS_BUF_TO_BLOCK(bp);
		memset(block, 0, mp->m_sb.sb_blocksize);
		block->bb_magic = cpu_to_be32(XFS_IBT_MAGIC);
		block->bb_level = 0;
		block->bb_numrecs = 0;
		block->bb_u.s.bb_leftsib = cpu_to_be32(NULLAGBLOCK);
		block->bb_u.s.bb_rightsib = cpu_to_be32(NULLAGBLOCK);
		error = xfs_bwrite(mp, bp);
		if (error) {
			goto error0;
		}
	}
	xfs_trans_agblocks_delta(tp, nfree);
	/*
	 * There are new blocks in the old last a.g.
	 */
	if (new) {
		/*
		 * Change the agi length.
		 */
		error = xfs_ialloc_read_agi(mp, tp, agno, &bp);
		if (error) {
			goto error0;
		}
		ASSERT(bp);
		agi = XFS_BUF_TO_AGI(bp);
		be32_add_cpu(&agi->agi_length, new);
		ASSERT(nagcount == oagcount ||
		       be32_to_cpu(agi->agi_length) == mp->m_sb.sb_agblocks);
		xfs_ialloc_log_agi(tp, bp, XFS_AGI_LENGTH);
		/*
		 * Change agf length.
		 */
		error = xfs_alloc_read_agf(mp, tp, agno, 0, &bp);
		if (error) {
			goto error0;
		}
		ASSERT(bp);
		agf = XFS_BUF_TO_AGF(bp);
		be32_add_cpu(&agf->agf_length, new);
		ASSERT(be32_to_cpu(agf->agf_length) ==
		       be32_to_cpu(agi->agi_length));

		xfs_alloc_log_agf(tp, bp, XFS_AGF_LENGTH);
		/*
		 * Free the new space.
		 */
		error = xfs_free_extent(tp, XFS_AGB_TO_FSB(mp, agno,
			be32_to_cpu(agf->agf_length) - new), new);
		if (error) {
			goto error0;
		}
	}

	/*
	 * Update changed superblock fields transactionally. These are not
	 * seen by the rest of the world until the transaction commit applies
	 * them atomically to the superblock.
	 */
	if (nagcount > oagcount)
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_AGCOUNT, nagcount - oagcount);
	if (nb > mp->m_sb.sb_dblocks)
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_DBLOCKS,
				 nb - mp->m_sb.sb_dblocks);
	if (nfree)
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_FDBLOCKS, nfree);
	if (dpct)
		xfs_trans_mod_sb(tp, XFS_TRANS_SB_IMAXPCT, dpct);
	error = xfs_trans_commit(tp, 0);
	if (error)
		return error;

	/* New allocation groups fully initialized, so update mount struct */
	if (nagimax)
		mp->m_maxagi = nagimax;
	if (mp->m_sb.sb_imax_pct) {
		__uint64_t icount = mp->m_sb.sb_dblocks * mp->m_sb.sb_imax_pct;
		do_div(icount, 100);
		mp->m_maxicount = icount << mp->m_sb.sb_inopblog;
	} else
		mp->m_maxicount = 0;
	xfs_set_low_space_thresholds(mp);

	/* update secondary superblocks. */
	for (agno = 1; agno < nagcount; agno++) {
		error = xfs_read_buf(mp, mp->m_ddev_targp,
				  XFS_AGB_TO_DADDR(mp, agno, XFS_SB_BLOCK(mp)),
				  XFS_FSS_TO_BB(mp, 1), 0, &bp);
		if (error) {
			xfs_warn(mp,
		"error %d reading secondary superblock for ag %d",
				error, agno);
			break;
		}
		xfs_sb_to_disk(XFS_BUF_TO_SBP(bp), &mp->m_sb, XFS_SB_ALL_BITS);
		/*
		 * If we get an error writing out the alternate superblocks,
		 * just issue a warning and continue.  The real work is
		 * already done and committed.
		 */
		if (!(error = xfs_bwrite(mp, bp))) {
			continue;
		} else {
			xfs_warn(mp,
		"write error %d updating secondary superblock for ag %d",
				error, agno);
			break; /* no point in continuing */
		}
	}
	return 0;

 error0:
	xfs_trans_cancel(tp, XFS_TRANS_ABORT);
	return error;
}