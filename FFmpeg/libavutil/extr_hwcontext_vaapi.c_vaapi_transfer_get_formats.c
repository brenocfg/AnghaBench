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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVHWFrameTransferDirection { ____Placeholder_AVHWFrameTransferDirection } AVHWFrameTransferDirection ;
struct TYPE_10__ {int nb_formats; TYPE_3__* formats; } ;
typedef  TYPE_4__ VAAPIDeviceContext ;
struct TYPE_11__ {scalar_t__ sw_format; TYPE_2__* device_ctx; } ;
struct TYPE_9__ {scalar_t__ pix_fmt; } ;
struct TYPE_8__ {TYPE_1__* internal; } ;
struct TYPE_7__ {TYPE_4__* priv; } ;
typedef  TYPE_5__ AVHWFramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int* av_malloc (int) ; 

__attribute__((used)) static int vaapi_transfer_get_formats(AVHWFramesContext *hwfc,
                                      enum AVHWFrameTransferDirection dir,
                                      enum AVPixelFormat **formats)
{
    VAAPIDeviceContext *ctx = hwfc->device_ctx->internal->priv;
    enum AVPixelFormat *pix_fmts;
    int i, k, sw_format_available;

    sw_format_available = 0;
    for (i = 0; i < ctx->nb_formats; i++) {
        if (ctx->formats[i].pix_fmt == hwfc->sw_format)
            sw_format_available = 1;
    }

    pix_fmts = av_malloc((ctx->nb_formats + 1) * sizeof(*pix_fmts));
    if (!pix_fmts)
        return AVERROR(ENOMEM);

    if (sw_format_available) {
        pix_fmts[0] = hwfc->sw_format;
        k = 1;
    } else {
        k = 0;
    }
    for (i = 0; i < ctx->nb_formats; i++) {
        if (ctx->formats[i].pix_fmt == hwfc->sw_format)
            continue;
        av_assert0(k < ctx->nb_formats);
        pix_fmts[k++] = ctx->formats[i].pix_fmt;
    }
    pix_fmts[k] = AV_PIX_FMT_NONE;

    *formats = pix_fmts;
    return 0;
}