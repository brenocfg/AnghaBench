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
typedef  int NalUnitType ;

/* Variables and functions */
#define  NAL_UNIT_CODED_SLICE_BLA_N_LP 133 
#define  NAL_UNIT_CODED_SLICE_BLA_W_LP 132 
#define  NAL_UNIT_CODED_SLICE_BLA_W_RADL 131 
#define  NAL_UNIT_CODED_SLICE_CRA 130 
#define  NAL_UNIT_CODED_SLICE_IDR_N_LP 129 
#define  NAL_UNIT_CODED_SLICE_IDR_W_RADL 128 

__attribute__((used)) static int is_keyframe(NalUnitType naltype)
{
    switch (naltype) {
    case NAL_UNIT_CODED_SLICE_BLA_W_LP:
    case NAL_UNIT_CODED_SLICE_BLA_W_RADL:
    case NAL_UNIT_CODED_SLICE_BLA_N_LP:
    case NAL_UNIT_CODED_SLICE_IDR_W_RADL:
    case NAL_UNIT_CODED_SLICE_IDR_N_LP:
    case NAL_UNIT_CODED_SLICE_CRA:
        return 1;
    default:
        return 0;
    }
}