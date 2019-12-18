#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int (* get_param_set_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ;} ;
typedef  TYPE_1__ VTEncContext ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
typedef  int /*<<< orphan*/  CMVideoFormatDescriptionRef ;
typedef  int /*<<< orphan*/  CMSampleBufferRef ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CMSampleBufferGetFormatDescription (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,...) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int get_length_code_size(
    AVCodecContext    *avctx,
    CMSampleBufferRef sample_buffer,
    size_t            *size)
{
    VTEncContext *vtctx = avctx->priv_data;
    CMVideoFormatDescriptionRef vid_fmt;
    int isize;
    int status;

    vid_fmt = CMSampleBufferGetFormatDescription(sample_buffer);
    if (!vid_fmt) {
        av_log(avctx, AV_LOG_ERROR, "Error getting buffer format description.\n");
        return AVERROR_EXTERNAL;
    }

    status = vtctx->get_param_set_func(vid_fmt,
                                       0,
                                       NULL,
                                       NULL,
                                       NULL,
                                       &isize);
    if (status) {
        av_log(avctx, AV_LOG_ERROR, "Error getting length code size: %d\n", status);
        return AVERROR_EXTERNAL;
    }

    *size = isize;
    return 0;
}