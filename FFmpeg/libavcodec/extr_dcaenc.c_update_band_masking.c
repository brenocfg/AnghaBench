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
typedef  scalar_t__ int32_t ;
struct TYPE_3__ {scalar_t__* eff_masking_curve_cb; scalar_t__* band_masking_cb; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */

__attribute__((used)) static void update_band_masking(DCAEncContext *c, int band1, int band2,
                                int f, int32_t spectrum1, int32_t spectrum2,
                                int channel, int32_t * arg)
{
    int32_t value = c->eff_masking_curve_cb[f] - spectrum1;

    if (value < c->band_masking_cb[band1])
        c->band_masking_cb[band1] = value;
}