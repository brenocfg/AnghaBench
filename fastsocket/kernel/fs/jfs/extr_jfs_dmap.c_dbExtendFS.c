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
typedef  int u32 ;
struct metapage {scalar_t__ data; } ;
struct jfs_sb_info {int nbperpage; int /*<<< orphan*/  l2nbperpage; struct bmap* bmap; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dmapctl {void** stree; } ;
struct dmap {int /*<<< orphan*/  start; } ;
struct bmap {int db_mapsize; int db_agl2size; int db_agsize; int db_numag; int* db_agfree; int db_maxag; int db_nfree; void* db_maxfreebud; int /*<<< orphan*/  db_maxlevel; } ;
typedef  void* s8 ;
typedef  int s64 ;

/* Variables and functions */
 int BLKTODMAP (int,int /*<<< orphan*/ ) ; 
 int BLKTOL0 (int,int /*<<< orphan*/ ) ; 
 int BLKTOL1 (int,int /*<<< orphan*/ ) ; 
 int BMAPBLKNO ; 
 int /*<<< orphan*/  BMAPSZTOLEV (int) ; 
 int BPERDMAP ; 
 int CTLLEAFIND ; 
 int EIO ; 
 struct jfs_sb_info* JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2BPERDMAP ; 
 int L2MAXL0SIZE ; 
 int L2MAXL1SIZE ; 
 int LPERCTL ; 
 int MAXAG ; 
 int MAXL0SIZE ; 
 int MAXL1SIZE ; 
 int /*<<< orphan*/  PSIZE ; 
 int dbGetL2AGSize (int) ; 
 void* dbInitDmap (struct dmap*,int,int) ; 
 void* dbInitDmapCtl (struct dmapctl*,int,int) ; 
 struct metapage* get_metapage (struct inode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jfs_info (char*,long long,long long,long long) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 struct metapage* read_metapage (struct inode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_metapage (struct metapage*) ; 
 int /*<<< orphan*/  write_metapage (struct metapage*) ; 

int dbExtendFS(struct inode *ipbmap, s64 blkno,	s64 nblocks)
{
	struct jfs_sb_info *sbi = JFS_SBI(ipbmap->i_sb);
	int nbperpage = sbi->nbperpage;
	int i, i0 = true, j, j0 = true, k, n;
	s64 newsize;
	s64 p;
	struct metapage *mp, *l2mp, *l1mp = NULL, *l0mp = NULL;
	struct dmapctl *l2dcp, *l1dcp, *l0dcp;
	struct dmap *dp;
	s8 *l0leaf, *l1leaf, *l2leaf;
	struct bmap *bmp = sbi->bmap;
	int agno, l2agsize, oldl2agsize;
	s64 ag_rem;

	newsize = blkno + nblocks;

	jfs_info("dbExtendFS: blkno:%Ld nblocks:%Ld newsize:%Ld",
		 (long long) blkno, (long long) nblocks, (long long) newsize);

	/*
	 *	initialize bmap control page.
	 *
	 * all the data in bmap control page should exclude
	 * the mkfs hidden dmap page.
	 */

	/* update mapsize */
	bmp->db_mapsize = newsize;
	bmp->db_maxlevel = BMAPSZTOLEV(bmp->db_mapsize);

	/* compute new AG size */
	l2agsize = dbGetL2AGSize(newsize);
	oldl2agsize = bmp->db_agl2size;

	bmp->db_agl2size = l2agsize;
	bmp->db_agsize = 1 << l2agsize;

	/* compute new number of AG */
	agno = bmp->db_numag;
	bmp->db_numag = newsize >> l2agsize;
	bmp->db_numag += ((u32) newsize % (u32) bmp->db_agsize) ? 1 : 0;

	/*
	 *	reconfigure db_agfree[]
	 * from old AG configuration to new AG configuration;
	 *
	 * coalesce contiguous k (newAGSize/oldAGSize) AGs;
	 * i.e., (AGi, ..., AGj) where i = k*n and j = k*(n+1) - 1 to AGn;
	 * note: new AG size = old AG size * (2**x).
	 */
	if (l2agsize == oldl2agsize)
		goto extend;
	k = 1 << (l2agsize - oldl2agsize);
	ag_rem = bmp->db_agfree[0];	/* save agfree[0] */
	for (i = 0, n = 0; i < agno; n++) {
		bmp->db_agfree[n] = 0;	/* init collection point */

		/* coalesce cotiguous k AGs; */
		for (j = 0; j < k && i < agno; j++, i++) {
			/* merge AGi to AGn */
			bmp->db_agfree[n] += bmp->db_agfree[i];
		}
	}
	bmp->db_agfree[0] += ag_rem;	/* restore agfree[0] */

	for (; n < MAXAG; n++)
		bmp->db_agfree[n] = 0;

	/*
	 * update highest active ag number
	 */

	bmp->db_maxag = bmp->db_maxag / k;

	/*
	 *	extend bmap
	 *
	 * update bit maps and corresponding level control pages;
	 * global control page db_nfree, db_agfree[agno], db_maxfreebud;
	 */
      extend:
	/* get L2 page */
	p = BMAPBLKNO + nbperpage;	/* L2 page */
	l2mp = read_metapage(ipbmap, p, PSIZE, 0);
	if (!l2mp) {
		jfs_error(ipbmap->i_sb, "dbExtendFS: L2 page could not be read");
		return -EIO;
	}
	l2dcp = (struct dmapctl *) l2mp->data;

	/* compute start L1 */
	k = blkno >> L2MAXL1SIZE;
	l2leaf = l2dcp->stree + CTLLEAFIND + k;
	p = BLKTOL1(blkno, sbi->l2nbperpage);	/* L1 page */

	/*
	 * extend each L1 in L2
	 */
	for (; k < LPERCTL; k++, p += nbperpage) {
		/* get L1 page */
		if (j0) {
			/* read in L1 page: (blkno & (MAXL1SIZE - 1)) */
			l1mp = read_metapage(ipbmap, p, PSIZE, 0);
			if (l1mp == NULL)
				goto errout;
			l1dcp = (struct dmapctl *) l1mp->data;

			/* compute start L0 */
			j = (blkno & (MAXL1SIZE - 1)) >> L2MAXL0SIZE;
			l1leaf = l1dcp->stree + CTLLEAFIND + j;
			p = BLKTOL0(blkno, sbi->l2nbperpage);
			j0 = false;
		} else {
			/* assign/init L1 page */
			l1mp = get_metapage(ipbmap, p, PSIZE, 0);
			if (l1mp == NULL)
				goto errout;

			l1dcp = (struct dmapctl *) l1mp->data;

			/* compute start L0 */
			j = 0;
			l1leaf = l1dcp->stree + CTLLEAFIND;
			p += nbperpage;	/* 1st L0 of L1.k */
		}

		/*
		 * extend each L0 in L1
		 */
		for (; j < LPERCTL; j++) {
			/* get L0 page */
			if (i0) {
				/* read in L0 page: (blkno & (MAXL0SIZE - 1)) */

				l0mp = read_metapage(ipbmap, p, PSIZE, 0);
				if (l0mp == NULL)
					goto errout;
				l0dcp = (struct dmapctl *) l0mp->data;

				/* compute start dmap */
				i = (blkno & (MAXL0SIZE - 1)) >>
				    L2BPERDMAP;
				l0leaf = l0dcp->stree + CTLLEAFIND + i;
				p = BLKTODMAP(blkno,
					      sbi->l2nbperpage);
				i0 = false;
			} else {
				/* assign/init L0 page */
				l0mp = get_metapage(ipbmap, p, PSIZE, 0);
				if (l0mp == NULL)
					goto errout;

				l0dcp = (struct dmapctl *) l0mp->data;

				/* compute start dmap */
				i = 0;
				l0leaf = l0dcp->stree + CTLLEAFIND;
				p += nbperpage;	/* 1st dmap of L0.j */
			}

			/*
			 * extend each dmap in L0
			 */
			for (; i < LPERCTL; i++) {
				/*
				 * reconstruct the dmap page, and
				 * initialize corresponding parent L0 leaf
				 */
				if ((n = blkno & (BPERDMAP - 1))) {
					/* read in dmap page: */
					mp = read_metapage(ipbmap, p,
							   PSIZE, 0);
					if (mp == NULL)
						goto errout;
					n = min(nblocks, (s64)BPERDMAP - n);
				} else {
					/* assign/init dmap page */
					mp = read_metapage(ipbmap, p,
							   PSIZE, 0);
					if (mp == NULL)
						goto errout;

					n = min(nblocks, (s64)BPERDMAP);
				}

				dp = (struct dmap *) mp->data;
				*l0leaf = dbInitDmap(dp, blkno, n);

				bmp->db_nfree += n;
				agno = le64_to_cpu(dp->start) >> l2agsize;
				bmp->db_agfree[agno] += n;

				write_metapage(mp);

				l0leaf++;
				p += nbperpage;

				blkno += n;
				nblocks -= n;
				if (nblocks == 0)
					break;
			}	/* for each dmap in a L0 */

			/*
			 * build current L0 page from its leaves, and
			 * initialize corresponding parent L1 leaf
			 */
			*l1leaf = dbInitDmapCtl(l0dcp, 0, ++i);
			write_metapage(l0mp);
			l0mp = NULL;

			if (nblocks)
				l1leaf++;	/* continue for next L0 */
			else {
				/* more than 1 L0 ? */
				if (j > 0)
					break;	/* build L1 page */
				else {
					/* summarize in global bmap page */
					bmp->db_maxfreebud = *l1leaf;
					release_metapage(l1mp);
					release_metapage(l2mp);
					goto finalize;
				}
			}
		}		/* for each L0 in a L1 */

		/*
		 * build current L1 page from its leaves, and
		 * initialize corresponding parent L2 leaf
		 */
		*l2leaf = dbInitDmapCtl(l1dcp, 1, ++j);
		write_metapage(l1mp);
		l1mp = NULL;

		if (nblocks)
			l2leaf++;	/* continue for next L1 */
		else {
			/* more than 1 L1 ? */
			if (k > 0)
				break;	/* build L2 page */
			else {
				/* summarize in global bmap page */
				bmp->db_maxfreebud = *l2leaf;
				release_metapage(l2mp);
				goto finalize;
			}
		}
	}			/* for each L1 in a L2 */

	jfs_error(ipbmap->i_sb,
		  "dbExtendFS: function has not returned as expected");
errout:
	if (l0mp)
		release_metapage(l0mp);
	if (l1mp)
		release_metapage(l1mp);
	release_metapage(l2mp);
	return -EIO;

	/*
	 *	finalize bmap control page
	 */
finalize:

	return 0;
}