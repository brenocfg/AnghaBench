#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/  sample_rate; TYPE_5__* dst; } ;
struct TYPE_8__ {double freq; int /*<<< orphan*/  pwidth; int /*<<< orphan*/  amount; int /*<<< orphan*/  srate; int /*<<< orphan*/  offset; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {double freq; int /*<<< orphan*/  pwidth; int /*<<< orphan*/  amount; int /*<<< orphan*/  srate; int /*<<< orphan*/  offset; int /*<<< orphan*/  mode; } ;
struct TYPE_9__ {int timing; int bpm; int ms; double hertz; int /*<<< orphan*/  pwidth; TYPE_2__ lfoR; TYPE_1__ lfoL; int /*<<< orphan*/  amount; int /*<<< orphan*/  offset_r; int /*<<< orphan*/  offset_l; int /*<<< orphan*/  mode; } ;
typedef  TYPE_3__ AudioPulsatorContext ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
#define  UNIT_BPM 130 
#define  UNIT_HZ 129 
#define  UNIT_MS 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    AudioPulsatorContext *s = ctx->priv;
    double freq;

    switch (s->timing) {
    case UNIT_BPM:  freq = s->bpm / 60;         break;
    case UNIT_MS:   freq = 1 / (s->ms / 1000.); break;
    case UNIT_HZ:   freq = s->hertz;            break;
    default: av_assert0(0);
    }

    s->lfoL.freq   = freq;
    s->lfoR.freq   = freq;
    s->lfoL.mode   = s->mode;
    s->lfoR.mode   = s->mode;
    s->lfoL.offset = s->offset_l;
    s->lfoR.offset = s->offset_r;
    s->lfoL.srate  = inlink->sample_rate;
    s->lfoR.srate  = inlink->sample_rate;
    s->lfoL.amount = s->amount;
    s->lfoR.amount = s->amount;
    s->lfoL.pwidth = s->pwidth;
    s->lfoR.pwidth = s->pwidth;

    return 0;
}