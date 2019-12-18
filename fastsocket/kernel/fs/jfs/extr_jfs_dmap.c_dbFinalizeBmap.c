#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct bmap {int db_maxag; int db_numag; int db_mapsize; int db_agsize; int db_agl2size; int db_nfree; int* db_agfree; size_t db_agpref; int db_aglevel; int db_agheigth; int db_agwidth; scalar_t__ db_agstart; } ;
typedef  int s64 ;
struct TYPE_2__ {struct bmap* bmap; } ;

/* Variables and functions */
 int BMAPSZTOLEV (int) ; 
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int L2BPERDMAP ; 
 int L2LPERCTL ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 

void dbFinalizeBmap(struct inode *ipbmap)
{
	struct bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;
	int actags, inactags, l2nl;
	s64 ag_rem, actfree, inactfree, avgfree;
	int i, n;

	/*
	 *	finalize bmap control page
	 */
//finalize:
	/*
	 * compute db_agpref: preferred ag to allocate from
	 * (the leftmost ag with average free space in it);
	 */
//agpref:
	/* get the number of active ags and inacitve ags */
	actags = bmp->db_maxag + 1;
	inactags = bmp->db_numag - actags;
	ag_rem = bmp->db_mapsize & (bmp->db_agsize - 1);	/* ??? */

	/* determine how many blocks are in the inactive allocation
	 * groups. in doing this, we must account for the fact that
	 * the rightmost group might be a partial group (i.e. file
	 * system size is not a multiple of the group size).
	 */
	inactfree = (inactags && ag_rem) ?
	    ((inactags - 1) << bmp->db_agl2size) + ag_rem
	    : inactags << bmp->db_agl2size;

	/* determine how many free blocks are in the active
	 * allocation groups plus the average number of free blocks
	 * within the active ags.
	 */
	actfree = bmp->db_nfree - inactfree;
	avgfree = (u32) actfree / (u32) actags;

	/* if the preferred allocation group has not average free space.
	 * re-establish the preferred group as the leftmost
	 * group with average free space.
	 */
	if (bmp->db_agfree[bmp->db_agpref] < avgfree) {
		for (bmp->db_agpref = 0; bmp->db_agpref < actags;
		     bmp->db_agpref++) {
			if (bmp->db_agfree[bmp->db_agpref] >= avgfree)
				break;
		}
		if (bmp->db_agpref >= bmp->db_numag) {
			jfs_error(ipbmap->i_sb,
				  "cannot find ag with average freespace");
		}
	}

	/*
	 * compute db_aglevel, db_agheigth, db_width, db_agstart:
	 * an ag is covered in aglevel dmapctl summary tree,
	 * at agheight level height (from leaf) with agwidth number of nodes
	 * each, which starts at agstart index node of the smmary tree node
	 * array;
	 */
	bmp->db_aglevel = BMAPSZTOLEV(bmp->db_agsize);
	l2nl =
	    bmp->db_agl2size - (L2BPERDMAP + bmp->db_aglevel * L2LPERCTL);
	bmp->db_agheigth = l2nl >> 1;
	bmp->db_agwidth = 1 << (l2nl - (bmp->db_agheigth << 1));
	for (i = 5 - bmp->db_agheigth, bmp->db_agstart = 0, n = 1; i > 0;
	     i--) {
		bmp->db_agstart += n;
		n <<= 2;
	}

}