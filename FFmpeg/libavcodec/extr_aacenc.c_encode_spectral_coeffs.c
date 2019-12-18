#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  lambda; int /*<<< orphan*/  pb; TYPE_1__* coder; } ;
struct TYPE_9__ {int num_windows; int* group_len; int max_sfb; scalar_t__* swb_sizes; int /*<<< orphan*/ * window_clipping; } ;
struct TYPE_10__ {TYPE_2__ ics; int /*<<< orphan*/ * band_type; int /*<<< orphan*/ * sf_idx; int /*<<< orphan*/ * coeffs; scalar_t__* zeroes; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* quantize_and_encode_band ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ SingleChannelElement ;
typedef  TYPE_4__ AACEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void encode_spectral_coeffs(AACEncContext *s, SingleChannelElement *sce)
{
    int start, i, w, w2;

    for (w = 0; w < sce->ics.num_windows; w += sce->ics.group_len[w]) {
        start = 0;
        for (i = 0; i < sce->ics.max_sfb; i++) {
            if (sce->zeroes[w*16 + i]) {
                start += sce->ics.swb_sizes[i];
                continue;
            }
            for (w2 = w; w2 < w + sce->ics.group_len[w]; w2++) {
                s->coder->quantize_and_encode_band(s, &s->pb,
                                                   &sce->coeffs[start + w2*128],
                                                   NULL, sce->ics.swb_sizes[i],
                                                   sce->sf_idx[w*16 + i],
                                                   sce->band_type[w*16 + i],
                                                   s->lambda,
                                                   sce->ics.window_clipping[w]);
            }
            start += sce->ics.swb_sizes[i];
        }
    }
}