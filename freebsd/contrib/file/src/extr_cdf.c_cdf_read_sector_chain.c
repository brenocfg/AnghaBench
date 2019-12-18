#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * sst_tab; } ;
typedef  TYPE_1__ cdf_stream_t ;
typedef  int /*<<< orphan*/  cdf_secid_t ;
typedef  int /*<<< orphan*/  cdf_sat_t ;
typedef  int /*<<< orphan*/  cdf_info_t ;
struct TYPE_12__ {size_t h_min_size_standard_stream; } ;
typedef  TYPE_2__ cdf_header_t ;

/* Variables and functions */
 int cdf_read_long_sector_chain (int /*<<< orphan*/  const*,TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t,TYPE_1__*) ; 
 int cdf_read_short_sector_chain (TYPE_2__ const*,int /*<<< orphan*/  const*,TYPE_1__ const*,int /*<<< orphan*/ ,size_t,TYPE_1__*) ; 

int
cdf_read_sector_chain(const cdf_info_t *info, const cdf_header_t *h,
    const cdf_sat_t *sat, const cdf_sat_t *ssat, const cdf_stream_t *sst,
    cdf_secid_t sid, size_t len, cdf_stream_t *scn)
{

	if (len < h->h_min_size_standard_stream && sst->sst_tab != NULL)
		return cdf_read_short_sector_chain(h, ssat, sst, sid, len,
		    scn);
	else
		return cdf_read_long_sector_chain(info, h, sat, sid, len, scn);
}