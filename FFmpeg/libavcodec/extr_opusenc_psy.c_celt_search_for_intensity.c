#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int end_band; int intensity_stereo; } ;
struct TYPE_9__ {float avg_is_band; TYPE_1__* avctx; } ;
struct TYPE_8__ {int channels; } ;
typedef  TYPE_2__ OpusPsyContext ;
typedef  TYPE_3__ CeltFrame ;

/* Variables and functions */
 int CELT_MAX_BANDS ; 
 float FLT_MAX ; 
 int /*<<< orphan*/  bands_dist (TYPE_2__*,TYPE_3__*,float*) ; 

__attribute__((used)) static void celt_search_for_intensity(OpusPsyContext *s, CeltFrame *f)
{
    int i, best_band = CELT_MAX_BANDS - 1;
    float dist, best_dist = FLT_MAX;
    /* TODO: fix, make some heuristic up here using the lambda value */
    float end_band = 0;

    if (s->avctx->channels < 2)
        return;

    for (i = f->end_band; i >= end_band; i--) {
        f->intensity_stereo = i;
        bands_dist(s, f, &dist);
        if (best_dist > dist) {
            best_dist = dist;
            best_band = i;
        }
    }

    f->intensity_stereo = best_band;
    s->avg_is_band = (s->avg_is_band + f->intensity_stereo)/2.0f;
}