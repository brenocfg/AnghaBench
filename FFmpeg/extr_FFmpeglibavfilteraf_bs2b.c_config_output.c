#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* filter_func ;
struct TYPE_7__ {TYPE_2__** inputs; TYPE_1__* priv; } ;
struct TYPE_6__ {int sample_rate; int format; TYPE_3__* src; } ;
struct TYPE_5__ {int /*<<< orphan*/  bs2bp; void* filter; } ;
typedef  TYPE_1__ Bs2bContext ;
typedef  TYPE_2__ AVFilterLink ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_BUG ; 
#define  AV_SAMPLE_FMT_DBL 132 
#define  AV_SAMPLE_FMT_FLT 131 
#define  AV_SAMPLE_FMT_S16 130 
#define  AV_SAMPLE_FMT_S32 129 
#define  AV_SAMPLE_FMT_U8 128 
 int BS2B_MAXSRATE ; 
 int BS2B_MINSRATE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  bs2b_cross_feed_d ; 
 int /*<<< orphan*/  bs2b_cross_feed_f ; 
 int /*<<< orphan*/  bs2b_cross_feed_s16 ; 
 int /*<<< orphan*/  bs2b_cross_feed_s32 ; 
 int /*<<< orphan*/  bs2b_cross_feed_u8 ; 
 int /*<<< orphan*/  bs2b_set_srate (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int config_output(AVFilterLink *outlink)
{
    AVFilterContext *ctx = outlink->src;
    Bs2bContext    *bs2b = ctx->priv;
    AVFilterLink *inlink = ctx->inputs[0];

    int srate = inlink->sample_rate;

    switch (inlink->format) {
    case AV_SAMPLE_FMT_U8:
        bs2b->filter = (filter_func) bs2b_cross_feed_u8;
        break;
    case AV_SAMPLE_FMT_S16:
        bs2b->filter = (filter_func) bs2b_cross_feed_s16;
        break;
    case AV_SAMPLE_FMT_S32:
        bs2b->filter = (filter_func) bs2b_cross_feed_s32;
        break;
    case AV_SAMPLE_FMT_FLT:
        bs2b->filter = (filter_func) bs2b_cross_feed_f;
        break;
    case AV_SAMPLE_FMT_DBL:
        bs2b->filter = (filter_func) bs2b_cross_feed_d;
        break;
    default:
        return AVERROR_BUG;
    }

    if ((srate < BS2B_MINSRATE) || (srate > BS2B_MAXSRATE))
        return AVERROR(ENOSYS);

    bs2b_set_srate(bs2b->bs2bp, srate);

    return 0;
}