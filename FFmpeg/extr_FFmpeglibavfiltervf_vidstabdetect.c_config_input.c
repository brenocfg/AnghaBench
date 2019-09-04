#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VSMotionDetect ;
struct TYPE_15__ {int bytesPerPixel; scalar_t__ log2ChromaW; scalar_t__ log2ChromaH; } ;
typedef  TYPE_1__ VSFrameInfo ;
struct TYPE_20__ {int algo; char* modName; int /*<<< orphan*/  show; int /*<<< orphan*/  virtualTripod; int /*<<< orphan*/  contrastThreshold; int /*<<< orphan*/  stepSize; int /*<<< orphan*/  accuracy; int /*<<< orphan*/  shakiness; } ;
struct TYPE_19__ {TYPE_2__* priv; } ;
struct TYPE_18__ {int /*<<< orphan*/  format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_5__* dst; } ;
struct TYPE_17__ {int flags; scalar_t__ log2_chroma_w; scalar_t__ log2_chroma_h; } ;
struct TYPE_16__ {int /*<<< orphan*/  result; int /*<<< orphan*/ * f; TYPE_6__ conf; int /*<<< orphan*/  md; } ;
typedef  TYPE_2__ StabData ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int AV_PIX_FMT_FLAG_PLANAR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ VS_OK ; 
 int av_get_bits_per_pixel (TYPE_3__ const*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_av2vs_pixfmt (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vsFrameInfoInit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsMotionDetectGetConfig (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ vsMotionDetectInit (int /*<<< orphan*/ *,TYPE_6__*,TYPE_1__*) ; 
 scalar_t__ vsPrepareFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    StabData *s = ctx->priv;

    VSMotionDetect* md = &(s->md);
    VSFrameInfo fi;
    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int is_planar = desc->flags & AV_PIX_FMT_FLAG_PLANAR;

    vsFrameInfoInit(&fi, inlink->w, inlink->h,
                    ff_av2vs_pixfmt(ctx, inlink->format));
    if (!is_planar && fi.bytesPerPixel != av_get_bits_per_pixel(desc)/8) {
        av_log(ctx, AV_LOG_ERROR, "pixel-format error: wrong bits/per/pixel, please report a BUG");
        return AVERROR(EINVAL);
    }
    if (fi.log2ChromaW != desc->log2_chroma_w) {
        av_log(ctx, AV_LOG_ERROR, "pixel-format error: log2_chroma_w, please report a BUG");
        return AVERROR(EINVAL);
    }

    if (fi.log2ChromaH != desc->log2_chroma_h) {
        av_log(ctx, AV_LOG_ERROR, "pixel-format error: log2_chroma_h, please report a BUG");
        return AVERROR(EINVAL);
    }

    // set values that are not initialized by the options
    s->conf.algo     = 1;
    s->conf.modName  = "vidstabdetect";
    if (vsMotionDetectInit(md, &s->conf, &fi) != VS_OK) {
        av_log(ctx, AV_LOG_ERROR, "initialization of Motion Detection failed, please report a BUG");
        return AVERROR(EINVAL);
    }

    vsMotionDetectGetConfig(&s->conf, md);
    av_log(ctx, AV_LOG_INFO, "Video stabilization settings (pass 1/2):\n");
    av_log(ctx, AV_LOG_INFO, "     shakiness = %d\n", s->conf.shakiness);
    av_log(ctx, AV_LOG_INFO, "      accuracy = %d\n", s->conf.accuracy);
    av_log(ctx, AV_LOG_INFO, "      stepsize = %d\n", s->conf.stepSize);
    av_log(ctx, AV_LOG_INFO, "   mincontrast = %f\n", s->conf.contrastThreshold);
    av_log(ctx, AV_LOG_INFO, "        tripod = %d\n", s->conf.virtualTripod);
    av_log(ctx, AV_LOG_INFO, "          show = %d\n", s->conf.show);
    av_log(ctx, AV_LOG_INFO, "        result = %s\n", s->result);

    s->f = fopen(s->result, "w");
    if (s->f == NULL) {
        av_log(ctx, AV_LOG_ERROR, "cannot open transform file %s\n", s->result);
        return AVERROR(EINVAL);
    } else {
        if (vsPrepareFile(md, s->f) != VS_OK) {
            av_log(ctx, AV_LOG_ERROR, "cannot write to transform file %s\n", s->result);
            return AVERROR(EINVAL);
        }
    }
    return 0;
}