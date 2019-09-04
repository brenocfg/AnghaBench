#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ num; scalar_t__ den; } ;
struct TYPE_13__ {TYPE_2__* internal; TYPE_4__ avg_frame_rate; TYPE_4__ r_frame_rate; } ;
struct TYPE_12__ {TYPE_1__* avctx; } ;
struct TYPE_11__ {int ticks_per_frame; TYPE_4__ framerate; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVRational ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 TYPE_4__ av_div_q (TYPE_4__,TYPE_4__) ; 
 double av_q2d (TYPE_4__) ; 
 double fabs (double) ; 

AVRational av_guess_frame_rate(AVFormatContext *format, AVStream *st, AVFrame *frame)
{
    AVRational fr = st->r_frame_rate;
    AVRational codec_fr = st->internal->avctx->framerate;
    AVRational   avg_fr = st->avg_frame_rate;

    if (avg_fr.num > 0 && avg_fr.den > 0 && fr.num > 0 && fr.den > 0 &&
        av_q2d(avg_fr) < 70 && av_q2d(fr) > 210) {
        fr = avg_fr;
    }


    if (st->internal->avctx->ticks_per_frame > 1) {
        if (   codec_fr.num > 0 && codec_fr.den > 0 &&
            (fr.num == 0 || av_q2d(codec_fr) < av_q2d(fr)*0.7 && fabs(1.0 - av_q2d(av_div_q(avg_fr, fr))) > 0.1))
            fr = codec_fr;
    }

    return fr;
}