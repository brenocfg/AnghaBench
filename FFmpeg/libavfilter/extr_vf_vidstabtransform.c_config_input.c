#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VSTransformData ;
typedef  int /*<<< orphan*/  VSManyLocalMotions ;
struct TYPE_16__ {int bytesPerPixel; scalar_t__ log2ChromaH; int /*<<< orphan*/  log2ChromaW; } ;
typedef  TYPE_1__ VSFrameInfo ;
struct TYPE_21__ {char* modName; scalar_t__ camPathAlgo; int optZoom; int /*<<< orphan*/  interpolType; int /*<<< orphan*/  zoomSpeed; int /*<<< orphan*/  zoom; scalar_t__ invert; scalar_t__ relative; scalar_t__ crop; int /*<<< orphan*/  maxAngle; int /*<<< orphan*/  maxShift; int /*<<< orphan*/  smoothing; scalar_t__ smoothZoom; scalar_t__ storeTransforms; scalar_t__ simpleMotionCalculation; scalar_t__ verbose; } ;
struct TYPE_17__ {int /*<<< orphan*/  trans; int /*<<< orphan*/  input; TYPE_6__ conf; scalar_t__ debug; scalar_t__ tripod; int /*<<< orphan*/  td; } ;
typedef  TYPE_2__ TransformContext ;
struct TYPE_20__ {TYPE_2__* priv; } ;
struct TYPE_19__ {int /*<<< orphan*/  format; int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_5__* dst; } ;
struct TYPE_18__ {int flags; scalar_t__ log2_chroma_h; int /*<<< orphan*/  log2_chroma_w; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_3__ AVPixFmtDescriptor ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int AV_PIX_FMT_FLAG_PLANAR ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ VSGaussian ; 
 scalar_t__ VSOptimalL1 ; 
 scalar_t__ VS_OK ; 
 int av_get_bits_per_pixel (TYPE_3__ const*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_av2vs_pixfmt (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getInterpolationTypeName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsFrameInfoInit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vsLocalmotions2Transforms (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vsPreprocessTransforms (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vsReadLocalMotionsFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsReadOldTransforms (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vsTransformDataInit (int /*<<< orphan*/ *,TYPE_6__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vsTransformGetConfig (TYPE_6__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int config_input(AVFilterLink *inlink)
{
    AVFilterContext *ctx = inlink->dst;
    TransformContext *tc = ctx->priv;
    FILE *f;

    const AVPixFmtDescriptor *desc = av_pix_fmt_desc_get(inlink->format);
    int is_planar = desc->flags & AV_PIX_FMT_FLAG_PLANAR;

    VSTransformData *td = &(tc->td);

    VSFrameInfo fi_src;
    VSFrameInfo fi_dest;

    if (!vsFrameInfoInit(&fi_src, inlink->w, inlink->h,
                         ff_av2vs_pixfmt(ctx, inlink->format)) ||
        !vsFrameInfoInit(&fi_dest, inlink->w, inlink->h,
                         ff_av2vs_pixfmt(ctx, inlink->format))) {
        av_log(ctx, AV_LOG_ERROR, "unknown pixel format: %i (%s)",
               inlink->format, desc->name);
        return AVERROR(EINVAL);
    }

    if ((!is_planar && fi_src.bytesPerPixel != av_get_bits_per_pixel(desc)/8) ||
        fi_src.log2ChromaW != desc->log2_chroma_w ||
        fi_src.log2ChromaH != desc->log2_chroma_h) {
        av_log(ctx, AV_LOG_ERROR, "pixel-format error: bpp %i<>%i  ",
               fi_src.bytesPerPixel, av_get_bits_per_pixel(desc)/8);
        av_log(ctx, AV_LOG_ERROR, "chroma_subsampl: w: %i<>%i  h: %i<>%i\n",
               fi_src.log2ChromaW, desc->log2_chroma_w,
               fi_src.log2ChromaH, desc->log2_chroma_h);
        return AVERROR(EINVAL);
    }

    // set values that are not initializes by the options
    tc->conf.modName = "vidstabtransform";
    tc->conf.verbose = 1 + tc->debug;
    if (tc->tripod) {
        av_log(ctx, AV_LOG_INFO, "Virtual tripod mode: relative=0, smoothing=0\n");
        tc->conf.relative  = 0;
        tc->conf.smoothing = 0;
    }
    tc->conf.simpleMotionCalculation = 0;
    tc->conf.storeTransforms         = tc->debug;
    tc->conf.smoothZoom              = 0;

    if (vsTransformDataInit(td, &tc->conf, &fi_src, &fi_dest) != VS_OK) {
        av_log(ctx, AV_LOG_ERROR, "initialization of vid.stab transform failed, please report a BUG\n");
        return AVERROR(EINVAL);
    }

    vsTransformGetConfig(&tc->conf, td);
    av_log(ctx, AV_LOG_INFO, "Video transformation/stabilization settings (pass 2/2):\n");
    av_log(ctx, AV_LOG_INFO, "    input     = %s\n", tc->input);
    av_log(ctx, AV_LOG_INFO, "    smoothing = %d\n", tc->conf.smoothing);
    av_log(ctx, AV_LOG_INFO, "    optalgo   = %s\n",
           tc->conf.camPathAlgo == VSOptimalL1 ? "opt" :
           (tc->conf.camPathAlgo == VSGaussian ? "gauss" : "avg"));
    av_log(ctx, AV_LOG_INFO, "    maxshift  = %d\n", tc->conf.maxShift);
    av_log(ctx, AV_LOG_INFO, "    maxangle  = %f\n", tc->conf.maxAngle);
    av_log(ctx, AV_LOG_INFO, "    crop      = %s\n", tc->conf.crop ? "Black" : "Keep");
    av_log(ctx, AV_LOG_INFO, "    relative  = %s\n", tc->conf.relative ? "True": "False");
    av_log(ctx, AV_LOG_INFO, "    invert    = %s\n", tc->conf.invert ? "True" : "False");
    av_log(ctx, AV_LOG_INFO, "    zoom      = %f\n", tc->conf.zoom);
    av_log(ctx, AV_LOG_INFO, "    optzoom   = %s\n",
           tc->conf.optZoom == 1 ? "Static (1)" : (tc->conf.optZoom == 2 ? "Dynamic (2)" : "Off (0)"));
    if (tc->conf.optZoom == 2)
        av_log(ctx, AV_LOG_INFO, "    zoomspeed = %g\n", tc->conf.zoomSpeed);
    av_log(ctx, AV_LOG_INFO, "    interpol  = %s\n", getInterpolationTypeName(tc->conf.interpolType));

    f = fopen(tc->input, "r");
    if (!f) {
        int ret = AVERROR(errno);
        av_log(ctx, AV_LOG_ERROR, "cannot open input file %s\n", tc->input);
        return ret;
    } else {
        VSManyLocalMotions mlms;
        if (vsReadLocalMotionsFile(f, &mlms) == VS_OK) {
            // calculate the actual transforms from the local motions
            if (vsLocalmotions2Transforms(td, &mlms, &tc->trans) != VS_OK) {
                av_log(ctx, AV_LOG_ERROR, "calculating transformations failed\n");
                return AVERROR(EINVAL);
            }
        } else { // try to read old format
            if (!vsReadOldTransforms(td, f, &tc->trans)) { /* read input file */
                av_log(ctx, AV_LOG_ERROR, "error parsing input file %s\n", tc->input);
                return AVERROR(EINVAL);
            }
        }
    }
    fclose(f);

    if (vsPreprocessTransforms(td, &tc->trans) != VS_OK) {
        av_log(ctx, AV_LOG_ERROR, "error while preprocessing transforms\n");
        return AVERROR(EINVAL);
    }

    // TODO: add sharpening, so far the user needs to call the unsharp filter manually
    return 0;
}