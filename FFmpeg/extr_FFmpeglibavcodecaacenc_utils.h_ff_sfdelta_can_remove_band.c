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
typedef  size_t uint8_t ;
struct TYPE_3__ {int* sf_idx; } ;
typedef  TYPE_1__ SingleChannelElement ;

/* Variables and functions */
 int SCALE_MAX_DIFF ; 

__attribute__((used)) static inline int ff_sfdelta_can_remove_band(const SingleChannelElement *sce,
    const uint8_t *nextband, int prev_sf, int band)
{
    return prev_sf >= 0
        && sce->sf_idx[nextband[band]] >= (prev_sf - SCALE_MAX_DIFF)
        && sce->sf_idx[nextband[band]] <= (prev_sf + SCALE_MAX_DIFF);
}