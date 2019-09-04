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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
typedef  enum AVHWFrameTransferDirection { ____Placeholder_AVHWFrameTransferDirection } AVHWFrameTransferDirection ;
struct TYPE_7__ {int sw_format; TYPE_1__* internal; } ;
struct TYPE_6__ {scalar_t__ format; } ;
struct TYPE_5__ {TYPE_2__* priv; } ;
typedef  TYPE_2__ D3D11VAFramesContext ;
typedef  TYPE_3__ AVHWFramesContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_PIX_FMT_NONE ; 
 scalar_t__ DXGI_FORMAT_420_OPAQUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int* av_malloc_array (int,int) ; 

__attribute__((used)) static int d3d11va_transfer_get_formats(AVHWFramesContext *ctx,
                                        enum AVHWFrameTransferDirection dir,
                                        enum AVPixelFormat **formats)
{
    D3D11VAFramesContext *s = ctx->internal->priv;
    enum AVPixelFormat *fmts;

    fmts = av_malloc_array(2, sizeof(*fmts));
    if (!fmts)
        return AVERROR(ENOMEM);

    fmts[0] = ctx->sw_format;
    fmts[1] = AV_PIX_FMT_NONE;

    // Don't signal support for opaque formats. Actual access would fail.
    if (s->format == DXGI_FORMAT_420_OPAQUE)
        fmts[0] = AV_PIX_FMT_NONE;

    *formats = fmts;

    return 0;
}