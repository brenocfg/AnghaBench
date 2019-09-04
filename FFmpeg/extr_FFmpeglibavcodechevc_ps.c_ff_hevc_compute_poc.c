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
struct TYPE_3__ {int log2_max_poc_lsb; } ;
typedef  TYPE_1__ HEVCSPS ;

/* Variables and functions */
 int HEVC_NAL_BLA_N_LP ; 
 int HEVC_NAL_BLA_W_LP ; 
 int HEVC_NAL_BLA_W_RADL ; 

int ff_hevc_compute_poc(const HEVCSPS *sps, int pocTid0, int poc_lsb, int nal_unit_type)
{
    int max_poc_lsb  = 1 << sps->log2_max_poc_lsb;
    int prev_poc_lsb = pocTid0 % max_poc_lsb;
    int prev_poc_msb = pocTid0 - prev_poc_lsb;
    int poc_msb;

    if (poc_lsb < prev_poc_lsb && prev_poc_lsb - poc_lsb >= max_poc_lsb / 2)
        poc_msb = prev_poc_msb + max_poc_lsb;
    else if (poc_lsb > prev_poc_lsb && poc_lsb - prev_poc_lsb > max_poc_lsb / 2)
        poc_msb = prev_poc_msb - max_poc_lsb;
    else
        poc_msb = prev_poc_msb;

    // For BLA picture types, POCmsb is set to 0.
    if (nal_unit_type == HEVC_NAL_BLA_W_LP   ||
        nal_unit_type == HEVC_NAL_BLA_W_RADL ||
        nal_unit_type == HEVC_NAL_BLA_N_LP)
        poc_msb = 0;

    return poc_msb + poc_lsb;
}