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
struct shrinker {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  OLD_ZNODE_AGE ; 
 int /*<<< orphan*/  YOUNG_ZNODE_AGE ; 
 long atomic_long_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbg_tnc (char*,...) ; 
 int kick_a_thread () ; 
 int shrink_tnc_trees (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ubifs_clean_zn_cnt ; 

int ubifs_shrinker(struct shrinker *shrink, int nr, gfp_t gfp_mask)
{
	int freed, contention = 0;
	long clean_zn_cnt = atomic_long_read(&ubifs_clean_zn_cnt);

	if (nr == 0)
		return clean_zn_cnt;

	if (!clean_zn_cnt) {
		/*
		 * No clean znodes, nothing to reap. All we can do in this case
		 * is to kick background threads to start commit, which will
		 * probably make clean znodes which, in turn, will be freeable.
		 * And we return -1 which means will make VM call us again
		 * later.
		 */
		dbg_tnc("no clean znodes, kick a thread");
		return kick_a_thread();
	}

	freed = shrink_tnc_trees(nr, OLD_ZNODE_AGE, &contention);
	if (freed >= nr)
		goto out;

	dbg_tnc("not enough old znodes, try to free young ones");
	freed += shrink_tnc_trees(nr - freed, YOUNG_ZNODE_AGE, &contention);
	if (freed >= nr)
		goto out;

	dbg_tnc("not enough young znodes, free all");
	freed += shrink_tnc_trees(nr - freed, 0, &contention);

	if (!freed && contention) {
		dbg_tnc("freed nothing, but contention");
		return -1;
	}

out:
	dbg_tnc("%d znodes were freed, requested %d", freed, nr);
	return freed;
}