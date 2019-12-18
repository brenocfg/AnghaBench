#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int low; } ;
struct TYPE_9__ {scalar_t__* filter_en; TYPE_1__ ver; } ;
struct TYPE_8__ {int filter; unsigned short* coeff; scalar_t__ enable; } ;
typedef  TYPE_2__ IXJ_FILTER_RAW ;
typedef  TYPE_3__ IXJ ;

/* Variables and functions */
 scalar_t__ ixj_WriteDSPCommand (unsigned short,TYPE_3__*) ; 

__attribute__((used)) static int ixj_init_filter_raw(IXJ *j, IXJ_FILTER_RAW * jfr)
{
	unsigned short cmd;
	int cnt, max;
	if (jfr->filter > 3) {
		return -1;
	}
	if (ixj_WriteDSPCommand(0x5154 + jfr->filter, j))	/* Select Filter */
		return -1;

	if (!jfr->enable) {
		if (ixj_WriteDSPCommand(0x5152, j))		/* Disable Filter */
			return -1;
		else
			return 0;
	} else {
		if (ixj_WriteDSPCommand(0x5153, j))		/* Enable Filter */
			return -1;
		/* Select the filter (f0 - f3) to use. */
		if (ixj_WriteDSPCommand(0x5154 + jfr->filter, j))
			return -1;
	}
	/* We need to load a programmable filter set for undefined */
	/* frequencies.  So we will point the filter to a programmable set. */
	/* Since there are only 4 filters and 4 programmable sets, we will */
	/* just point the filter to the same number set and program it for the */
	/* frequency we want. */
	if (ixj_WriteDSPCommand(0x5170 + jfr->filter, j))
		return -1;
	if (j->ver.low != 0x12) {
		cmd = 0x515B;
		max = 19;
	} else {
		cmd = 0x515E;
		max = 15;
	}
	if (ixj_WriteDSPCommand(cmd, j))
		return -1;
	for (cnt = 0; cnt < max; cnt++) {
		if (ixj_WriteDSPCommand(jfr->coeff[cnt], j))
			return -1;
	}
	j->filter_en[jfr->filter] = jfr->enable;
	return 0;
}