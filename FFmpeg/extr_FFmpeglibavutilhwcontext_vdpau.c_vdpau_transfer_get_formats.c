#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVHWFrameTransferDirection { ____Placeholder_AVHWFrameTransferDirection } AVHWFrameTransferDirection ;
struct TYPE_7__ {int nb_pix_fmts; int /*<<< orphan*/  pix_fmts; } ;
typedef  TYPE_2__ VDPAUFramesContext ;
struct TYPE_8__ {TYPE_1__* internal; } ;
struct TYPE_6__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ AVHWFramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int* av_malloc_array (int,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vdpau_transfer_get_formats(AVHWFramesContext *ctx,
                                      enum AVHWFrameTransferDirection dir,
                                      enum AVPixelFormat **formats)
{
    VDPAUFramesContext *priv  = ctx->internal->priv;

    enum AVPixelFormat *fmts;

    if (priv->nb_pix_fmts == 1) {
        av_log(ctx, AV_LOG_ERROR,
               "No target formats are supported for this chroma type\n");
        return AVERROR(ENOSYS);
    }

    fmts = av_malloc_array(priv->nb_pix_fmts, sizeof(*fmts));
    if (!fmts)
        return AVERROR(ENOMEM);

    memcpy(fmts, priv->pix_fmts, sizeof(*fmts) * (priv->nb_pix_fmts));
    *formats = fmts;

    return 0;
}