#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int nfreqbands; int nchannels; int* dmix_scale; int hier_ofs; int /*<<< orphan*/ * deci_history; TYPE_1__* bands; int /*<<< orphan*/  hier_chset; } ;
struct TYPE_9__ {int nactivechsets; TYPE_2__* dcadsp; int /*<<< orphan*/  nframesamples; TYPE_4__* chset; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* dmix_scale ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {int /*<<< orphan*/ * msb_sample_buffer; } ;
typedef  TYPE_3__ DCAXllDecoder ;
typedef  TYPE_4__ DCAXllChSet ;

/* Variables and functions */
 int /*<<< orphan*/  DCA_XLL_DECI_HISTORY_MAX ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scale_down_mix(DCAXllDecoder *s, DCAXllChSet *o, int band)
{
    int i, j, nchannels = 0;
    DCAXllChSet *c;

    for (i = 0, c = s->chset; i < s->nactivechsets; i++, c++) {
        if (!c->hier_chset)
            continue;

        av_assert1(band < c->nfreqbands);
        for (j = 0; j < c->nchannels; j++) {
            int scale = o->dmix_scale[nchannels++];
            if (scale != (1 << 15)) {
                s->dcadsp->dmix_scale(c->bands[band].msb_sample_buffer[j],
                                      scale, s->nframesamples);
                if (band)
                    s->dcadsp->dmix_scale(c->deci_history[j],
                                          scale, DCA_XLL_DECI_HISTORY_MAX);
            }
        }

        if (nchannels >= o->hier_ofs)
            break;
    }
}