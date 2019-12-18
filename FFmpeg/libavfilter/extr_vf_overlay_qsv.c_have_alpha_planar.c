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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_10__ {int format; TYPE_1__* hw_frames_ctx; } ;
struct TYPE_9__ {int sw_format; } ;
struct TYPE_8__ {int flags; } ;
struct TYPE_7__ {scalar_t__ data; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVFilterLink ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_ALPHA ; 
 scalar_t__ AV_PIX_FMT_QSV ; 
 TYPE_2__* av_pix_fmt_desc_get (int) ; 

__attribute__((used)) static int have_alpha_planar(AVFilterLink *link)
{
    enum AVPixelFormat pix_fmt = link->format;
    const AVPixFmtDescriptor *desc;
    AVHWFramesContext *fctx;

    if (link->format == AV_PIX_FMT_QSV) {
        fctx    = (AVHWFramesContext *)link->hw_frames_ctx->data;
        pix_fmt = fctx->sw_format;
    }

    desc = av_pix_fmt_desc_get(pix_fmt);
    if (!desc)
        return 0;

    return !!(desc->flags & AV_PIX_FMT_FLAG_ALPHA);
}