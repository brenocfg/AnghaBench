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
struct TYPE_3__ {int profile_idc; int cpb_br_nal_factor; } ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__*) ; 
 TYPE_1__* h264_br_factors ; 

__attribute__((used)) static int h264_get_br_factor(int profile_idc)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(h264_br_factors); i++) {
        if (h264_br_factors[i].profile_idc == profile_idc)
            return h264_br_factors[i].cpb_br_nal_factor;
    }
    // Default to the non-high profile value if not specified.
    return 1200;
}