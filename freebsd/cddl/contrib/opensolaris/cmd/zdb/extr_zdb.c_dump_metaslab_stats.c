#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rt_histogram; } ;
typedef  TYPE_1__ range_tree_t ;
struct TYPE_7__ {int ms_size; int /*<<< orphan*/  ms_allocatable_by_size; TYPE_1__* ms_allocatable; } ;
typedef  TYPE_2__ metaslab_t ;
typedef  int /*<<< orphan*/  maxbuf ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int NN_NUMBUF_SZ ; 
 int /*<<< orphan*/  RANGE_TREE_HISTOGRAM_SIZE ; 
 int /*<<< orphan*/  avl_numnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dump_histogram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metaslab_block_maxsize (TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int range_tree_space (TYPE_1__*) ; 
 int /*<<< orphan*/  zdb_nicenum (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
dump_metaslab_stats(metaslab_t *msp)
{
	char maxbuf[32];
	range_tree_t *rt = msp->ms_allocatable;
	avl_tree_t *t = &msp->ms_allocatable_by_size;
	int free_pct = range_tree_space(rt) * 100 / msp->ms_size;

	/* max sure nicenum has enough space */
	CTASSERT(sizeof (maxbuf) >= NN_NUMBUF_SZ);

	zdb_nicenum(metaslab_block_maxsize(msp), maxbuf, sizeof (maxbuf));

	(void) printf("\t %25s %10lu   %7s  %6s   %4s %4d%%\n",
	    "segments", avl_numnodes(t), "maxsize", maxbuf,
	    "freepct", free_pct);
	(void) printf("\tIn-memory histogram:\n");
	dump_histogram(rt->rt_histogram, RANGE_TREE_HISTOGRAM_SIZE, 0);
}