#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int bits_per_raw_sample; int /*<<< orphan*/  sample_fmt; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16P ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S32P ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_U8P ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int set_bps_params(AVCodecContext *avctx)
{
    switch (avctx->bits_per_raw_sample) {
    case 8:
        avctx->sample_fmt = AV_SAMPLE_FMT_U8P;
        break;
    case 16:
        avctx->sample_fmt = AV_SAMPLE_FMT_S16P;
        break;
    case 24:
        avctx->sample_fmt = AV_SAMPLE_FMT_S32P;
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "invalid/unsupported bits per sample: %d\n",
               avctx->bits_per_raw_sample);
        return AVERROR_INVALIDDATA;
    }

    return 0;
}