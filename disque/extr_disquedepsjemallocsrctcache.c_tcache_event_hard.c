#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsd_t ;
struct TYPE_10__ {size_t next_gc_bin; scalar_t__ ev_cnt; TYPE_2__* tbins; } ;
typedef  TYPE_1__ tcache_t ;
struct TYPE_11__ {int low_water; int ncached; int lg_fill_div; } ;
typedef  TYPE_2__ tcache_bin_t ;
struct TYPE_12__ {int ncached_max; } ;
typedef  TYPE_3__ tcache_bin_info_t ;
typedef  size_t szind_t ;

/* Variables and functions */
 size_t NBINS ; 
 scalar_t__ nhbins ; 
 int /*<<< orphan*/  tcache_bin_flush_large (int /*<<< orphan*/ *,TYPE_2__*,size_t,int,TYPE_1__*) ; 
 int /*<<< orphan*/  tcache_bin_flush_small (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,size_t,int) ; 
 TYPE_3__* tcache_bin_info ; 

void
tcache_event_hard(tsd_t *tsd, tcache_t *tcache)
{
	szind_t binind = tcache->next_gc_bin;
	tcache_bin_t *tbin = &tcache->tbins[binind];
	tcache_bin_info_t *tbin_info = &tcache_bin_info[binind];

	if (tbin->low_water > 0) {
		/*
		 * Flush (ceiling) 3/4 of the objects below the low water mark.
		 */
		if (binind < NBINS) {
			tcache_bin_flush_small(tsd, tcache, tbin, binind,
			    tbin->ncached - tbin->low_water + (tbin->low_water
			    >> 2));
		} else {
			tcache_bin_flush_large(tsd, tbin, binind, tbin->ncached
			    - tbin->low_water + (tbin->low_water >> 2), tcache);
		}
		/*
		 * Reduce fill count by 2X.  Limit lg_fill_div such that the
		 * fill count is always at least 1.
		 */
		if ((tbin_info->ncached_max >> (tbin->lg_fill_div+1)) >= 1)
			tbin->lg_fill_div++;
	} else if (tbin->low_water < 0) {
		/*
		 * Increase fill count by 2X.  Make sure lg_fill_div stays
		 * greater than 0.
		 */
		if (tbin->lg_fill_div > 1)
			tbin->lg_fill_div--;
	}
	tbin->low_water = tbin->ncached;

	tcache->next_gc_bin++;
	if (tcache->next_gc_bin == nhbins)
		tcache->next_gc_bin = 0;
	tcache->ev_cnt = 0;
}