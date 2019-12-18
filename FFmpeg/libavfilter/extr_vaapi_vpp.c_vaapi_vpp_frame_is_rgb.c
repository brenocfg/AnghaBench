#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ format; TYPE_1__* hw_frames_ctx; } ;
struct TYPE_10__ {int /*<<< orphan*/  sw_format; } ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {scalar_t__ data; } ;
typedef  TYPE_2__ AVPixFmtDescriptor ;
typedef  TYPE_3__ AVHWFramesContext ;
typedef  TYPE_4__ AVFrame ;

/* Variables and functions */
 int AV_PIX_FMT_FLAG_RGB ; 
 scalar_t__ AV_PIX_FMT_VAAPI ; 
 int /*<<< orphan*/  av_assert0 (TYPE_2__ const*) ; 
 TYPE_2__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vaapi_vpp_frame_is_rgb(const AVFrame *frame)
{
    const AVHWFramesContext *hwfc;
    const AVPixFmtDescriptor *desc;
    av_assert0(frame->format == AV_PIX_FMT_VAAPI &&
               frame->hw_frames_ctx);
    hwfc = (const AVHWFramesContext*)frame->hw_frames_ctx->data;
    desc = av_pix_fmt_desc_get(hwfc->sw_format);
    av_assert0(desc);
    return !!(desc->flags & AV_PIX_FMT_FLAG_RGB);
}