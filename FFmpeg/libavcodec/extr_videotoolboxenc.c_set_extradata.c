#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t extradata_size; int /*<<< orphan*/  extradata; } ;
typedef  int /*<<< orphan*/  CMVideoFormatDescriptionRef ;
typedef  int /*<<< orphan*/  CMSampleBufferRef ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CMSampleBufferGetFormatDescription (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_mallocz (scalar_t__) ; 
 int copy_param_sets (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int get_params_size (TYPE_1__*,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int set_extradata(AVCodecContext *avctx, CMSampleBufferRef sample_buffer)
{
    CMVideoFormatDescriptionRef vid_fmt;
    size_t total_size;
    int status;

    vid_fmt = CMSampleBufferGetFormatDescription(sample_buffer);
    if (!vid_fmt) {
        av_log(avctx, AV_LOG_ERROR, "No video format.\n");
        return AVERROR_EXTERNAL;
    }

    status = get_params_size(avctx, vid_fmt, &total_size);
    if (status) {
        av_log(avctx, AV_LOG_ERROR, "Could not get parameter sets.\n");
        return status;
    }

    avctx->extradata = av_mallocz(total_size + AV_INPUT_BUFFER_PADDING_SIZE);
    if (!avctx->extradata) {
        return AVERROR(ENOMEM);
    }
    avctx->extradata_size = total_size;

    status = copy_param_sets(avctx, vid_fmt, avctx->extradata, total_size);

    if (status) {
        av_log(avctx, AV_LOG_ERROR, "Could not copy param sets.\n");
        return status;
    }

    return 0;
}