#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fullband_channels; int /*<<< orphan*/  downsampled_lfe; void* lfe_peak_cb; scalar_t__ lfe_channel; int /*<<< orphan*/ ** subband; void*** peak_cb; } ;
typedef  TYPE_1__ DCAEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  DCA_LFE_SAMPLES ; 
 int /*<<< orphan*/  SUBBAND_SAMPLES ; 
 void* find_peak (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void find_peaks(DCAEncContext *c)
{
    int band, ch;

    for (ch = 0; ch < c->fullband_channels; ch++) {
        for (band = 0; band < 32; band++)
            c->peak_cb[ch][band] = find_peak(c, c->subband[ch][band],
                                             SUBBAND_SAMPLES);
    }

    if (c->lfe_channel)
        c->lfe_peak_cb = find_peak(c, c->downsampled_lfe, DCA_LFE_SAMPLES);
}