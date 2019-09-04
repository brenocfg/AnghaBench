#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_5__ {int /*<<< orphan*/  sample_fmt; } ;
struct TYPE_4__ {int internal_ftype; int channels; int** offset; TYPE_3__* avctx; int /*<<< orphan*/  nmean; } ;
typedef  TYPE_1__ ShortenContext ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16P ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_U8P ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
#define  TYPE_S16HL 130 
#define  TYPE_S16LH 129 
#define  TYPE_U8 128 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int init_offset(ShortenContext *s)
{
    int32_t mean = 0;
    int chan, i;
    int nblock = FFMAX(1, s->nmean);
    /* initialise offset */
    switch (s->internal_ftype) {
    case TYPE_U8:
        s->avctx->sample_fmt = AV_SAMPLE_FMT_U8P;
        mean = 0x80;
        break;
    case TYPE_S16HL:
    case TYPE_S16LH:
        s->avctx->sample_fmt = AV_SAMPLE_FMT_S16P;
        break;
    default:
        av_log(s->avctx, AV_LOG_ERROR, "unknown audio type\n");
        return AVERROR_PATCHWELCOME;
    }

    for (chan = 0; chan < s->channels; chan++)
        for (i = 0; i < nblock; i++)
            s->offset[chan][i] = mean;
    return 0;
}