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
struct dmaptree {scalar_t__* stree; } ;
struct dmap {int /*<<< orphan*/  nfree; int /*<<< orphan*/ * wmap; int /*<<< orphan*/  tree; } ;
struct bmap {int db_agl2size; int db_maxag; int* db_agfree; int db_nfree; } ;
typedef  scalar_t__ s8 ;
typedef  int s64 ;

/* Variables and functions */
 int /*<<< orphan*/  BMAP_LOCK (struct bmap*) ; 
 int /*<<< orphan*/  BMAP_UNLOCK (struct bmap*) ; 
 int BPERDMAP ; 
 int DBWORD ; 
 int L2DBWORD ; 
 int LEAFIND ; 
 int ONES ; 
 size_t ROOT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int dbAdjCtl (struct bmap*,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbFreeBits (struct bmap*,struct dmap*,int,int) ; 
 int /*<<< orphan*/  dbInitDmapTree (struct dmap*) ; 
 int /*<<< orphan*/  le32_add_cpu (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int min (int,int) ; 

__attribute__((used)) static int dbAllocDmapBU(struct bmap * bmp, struct dmap * dp, s64 blkno,
			 int nblocks)
{
	int rc;
	int dbitno, word, rembits, nb, nwords, wbitno, agno;
	s8 oldroot, *leaf;
	struct dmaptree *tp = (struct dmaptree *) & dp->tree;

	/* save the current value of the root (i.e. maximum free string)
	 * of the dmap tree.
	 */
	oldroot = tp->stree[ROOT];

	/* pick up a pointer to the leaves of the dmap tree */
	leaf = tp->stree + LEAFIND;

	/* determine the bit number and word within the dmap of the
	 * starting block.
	 */
	dbitno = blkno & (BPERDMAP - 1);
	word = dbitno >> L2DBWORD;

	/* block range better be within the dmap */
	assert(dbitno + nblocks <= BPERDMAP);

	/* allocate the bits of the dmap's words corresponding to the block
	 * range. not all bits of the first and last words may be contained
	 * within the block range.  if this is the case, we'll work against
	 * those words (i.e. partial first and/or last) on an individual basis
	 * (a single pass), allocating the bits of interest by hand and
	 * updating the leaf corresponding to the dmap word. a single pass
	 * will be used for all dmap words fully contained within the
	 * specified range.  within this pass, the bits of all fully contained
	 * dmap words will be marked as free in a single shot and the leaves
	 * will be updated. a single leaf may describe the free space of
	 * multiple dmap words, so we may update only a subset of the actual
	 * leaves corresponding to the dmap words of the block range.
	 */
	for (rembits = nblocks; rembits > 0; rembits -= nb, dbitno += nb) {
		/* determine the bit number within the word and
		 * the number of bits within the word.
		 */
		wbitno = dbitno & (DBWORD - 1);
		nb = min(rembits, DBWORD - wbitno);

		/* check if only part of a word is to be allocated.
		 */
		if (nb < DBWORD) {
			/* allocate (set to 1) the appropriate bits within
			 * this dmap word.
			 */
			dp->wmap[word] |= cpu_to_le32(ONES << (DBWORD - nb)
						      >> wbitno);

			word++;
		} else {
			/* one or more dmap words are fully contained
			 * within the block range.  determine how many
			 * words and allocate (set to 1) the bits of these
			 * words.
			 */
			nwords = rembits >> L2DBWORD;
			memset(&dp->wmap[word], (int) ONES, nwords * 4);

			/* determine how many bits */
			nb = nwords << L2DBWORD;
			word += nwords;
		}
	}

	/* update the free count for this dmap */
	le32_add_cpu(&dp->nfree, -nblocks);

	/* reconstruct summary tree */
	dbInitDmapTree(dp);

	BMAP_LOCK(bmp);

	/* if this allocation group is completely free,
	 * update the highest active allocation group number
	 * if this allocation group is the new max.
	 */
	agno = blkno >> bmp->db_agl2size;
	if (agno > bmp->db_maxag)
		bmp->db_maxag = agno;

	/* update the free count for the allocation group and map */
	bmp->db_agfree[agno] -= nblocks;
	bmp->db_nfree -= nblocks;

	BMAP_UNLOCK(bmp);

	/* if the root has not changed, done. */
	if (tp->stree[ROOT] == oldroot)
		return (0);

	/* root changed. bubble the change up to the dmap control pages.
	 * if the adjustment of the upper level control pages fails,
	 * backout the bit allocation (thus making everything consistent).
	 */
	if ((rc = dbAdjCtl(bmp, blkno, tp->stree[ROOT], 1, 0)))
		dbFreeBits(bmp, dp, blkno, nblocks);

	return (rc);
}