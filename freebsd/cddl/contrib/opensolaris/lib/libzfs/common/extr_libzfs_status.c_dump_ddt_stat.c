#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  refcnt ;
typedef  int /*<<< orphan*/  ref_psize ;
typedef  int /*<<< orphan*/  ref_lsize ;
typedef  int /*<<< orphan*/  ref_dsize ;
typedef  int /*<<< orphan*/  ref_blocks ;
typedef  int /*<<< orphan*/  psize ;
typedef  int /*<<< orphan*/  lsize ;
typedef  int /*<<< orphan*/  dsize ;
struct TYPE_3__ {unsigned long long dds_blocks; unsigned long long dds_lsize; unsigned long long dds_psize; unsigned long long dds_dsize; unsigned long long dds_ref_blocks; unsigned long long dds_ref_lsize; unsigned long long dds_ref_psize; unsigned long long dds_ref_dsize; } ;
typedef  TYPE_1__ ddt_stat_t ;
typedef  int /*<<< orphan*/  blocks ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int /*<<< orphan*/  zfs_nicenum (unsigned long long,char*,int) ; 

__attribute__((used)) static void
dump_ddt_stat(const ddt_stat_t *dds, int h)
{
	char refcnt[6];
	char blocks[6], lsize[6], psize[6], dsize[6];
	char ref_blocks[6], ref_lsize[6], ref_psize[6], ref_dsize[6];

	if (dds == NULL || dds->dds_blocks == 0)
		return;

	if (h == -1)
		(void) strcpy(refcnt, "Total");
	else
		zfs_nicenum(1ULL << h, refcnt, sizeof (refcnt));

	zfs_nicenum(dds->dds_blocks, blocks, sizeof (blocks));
	zfs_nicenum(dds->dds_lsize, lsize, sizeof (lsize));
	zfs_nicenum(dds->dds_psize, psize, sizeof (psize));
	zfs_nicenum(dds->dds_dsize, dsize, sizeof (dsize));
	zfs_nicenum(dds->dds_ref_blocks, ref_blocks, sizeof (ref_blocks));
	zfs_nicenum(dds->dds_ref_lsize, ref_lsize, sizeof (ref_lsize));
	zfs_nicenum(dds->dds_ref_psize, ref_psize, sizeof (ref_psize));
	zfs_nicenum(dds->dds_ref_dsize, ref_dsize, sizeof (ref_dsize));

	(void) printf("%6s   %6s   %5s   %5s   %5s   %6s   %5s   %5s   %5s\n",
	    refcnt,
	    blocks, lsize, psize, dsize,
	    ref_blocks, ref_lsize, ref_psize, ref_dsize);
}