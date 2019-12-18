#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct metapage {scalar_t__ data; } ;
struct TYPE_3__ {int* stree; } ;
struct dmap {TYPE_1__ tree; } ;
struct bmap {TYPE_2__* db_ipbmap; int /*<<< orphan*/  db_l2nbperpage; } ;
typedef  int s64 ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int BLKTODMAP (int,int /*<<< orphan*/ ) ; 
 int BPERDMAP ; 
 int EIO ; 
 int L2BPERDMAP ; 
 int /*<<< orphan*/  PSIZE ; 
 size_t ROOT ; 
 int /*<<< orphan*/  assert (int) ; 
 int dbAllocDmap (struct bmap*,struct dmap*,int,int) ; 
 int dbAllocDmapLev (struct bmap*,struct dmap*,int,int,int*) ; 
 scalar_t__ dbFreeDmap (struct bmap*,struct dmap*,int,int) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mark_metapage_dirty (struct metapage*) ; 
 int min (int,int) ; 
 struct metapage* read_metapage (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  write_metapage (struct metapage*) ; 

__attribute__((used)) static int
dbAllocCtl(struct bmap * bmp, s64 nblocks, int l2nb, s64 blkno, s64 * results)
{
	int rc, nb;
	s64 b, lblkno, n;
	struct metapage *mp;
	struct dmap *dp;

	/* check if the allocation request is confined to a single dmap.
	 */
	if (l2nb <= L2BPERDMAP) {
		/* get the buffer for the dmap.
		 */
		lblkno = BLKTODMAP(blkno, bmp->db_l2nbperpage);
		mp = read_metapage(bmp->db_ipbmap, lblkno, PSIZE, 0);
		if (mp == NULL)
			return -EIO;
		dp = (struct dmap *) mp->data;

		/* try to allocate the blocks.
		 */
		rc = dbAllocDmapLev(bmp, dp, (int) nblocks, l2nb, results);
		if (rc == 0)
			mark_metapage_dirty(mp);

		release_metapage(mp);

		return (rc);
	}

	/* allocation request involving multiple dmaps. it must start on
	 * a dmap boundary.
	 */
	assert((blkno & (BPERDMAP - 1)) == 0);

	/* allocate the blocks dmap by dmap.
	 */
	for (n = nblocks, b = blkno; n > 0; n -= nb, b += nb) {
		/* get the buffer for the dmap.
		 */
		lblkno = BLKTODMAP(b, bmp->db_l2nbperpage);
		mp = read_metapage(bmp->db_ipbmap, lblkno, PSIZE, 0);
		if (mp == NULL) {
			rc = -EIO;
			goto backout;
		}
		dp = (struct dmap *) mp->data;

		/* the dmap better be all free.
		 */
		if (dp->tree.stree[ROOT] != L2BPERDMAP) {
			release_metapage(mp);
			jfs_error(bmp->db_ipbmap->i_sb,
				  "dbAllocCtl: the dmap is not all free");
			rc = -EIO;
			goto backout;
		}

		/* determine how many blocks to allocate from this dmap.
		 */
		nb = min(n, (s64)BPERDMAP);

		/* allocate the blocks from the dmap.
		 */
		if ((rc = dbAllocDmap(bmp, dp, b, nb))) {
			release_metapage(mp);
			goto backout;
		}

		/* write the buffer.
		 */
		write_metapage(mp);
	}

	/* set the results (starting block number) and return.
	 */
	*results = blkno;
	return (0);

	/* something failed in handling an allocation request involving
	 * multiple dmaps.  we'll try to clean up by backing out any
	 * allocation that has already happened for this request.  if
	 * we fail in backing out the allocation, we'll mark the file
	 * system to indicate that blocks have been leaked.
	 */
      backout:

	/* try to backout the allocations dmap by dmap.
	 */
	for (n = nblocks - n, b = blkno; n > 0;
	     n -= BPERDMAP, b += BPERDMAP) {
		/* get the buffer for this dmap.
		 */
		lblkno = BLKTODMAP(b, bmp->db_l2nbperpage);
		mp = read_metapage(bmp->db_ipbmap, lblkno, PSIZE, 0);
		if (mp == NULL) {
			/* could not back out.  mark the file system
			 * to indicate that we have leaked blocks.
			 */
			jfs_error(bmp->db_ipbmap->i_sb,
				  "dbAllocCtl: I/O Error: Block Leakage.");
			continue;
		}
		dp = (struct dmap *) mp->data;

		/* free the blocks is this dmap.
		 */
		if (dbFreeDmap(bmp, dp, b, BPERDMAP)) {
			/* could not back out.  mark the file system
			 * to indicate that we have leaked blocks.
			 */
			release_metapage(mp);
			jfs_error(bmp->db_ipbmap->i_sb,
				  "dbAllocCtl: Block Leakage.");
			continue;
		}

		/* write the buffer.
		 */
		write_metapage(mp);
	}

	return (rc);
}