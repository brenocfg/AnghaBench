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
struct TYPE_4__ {scalar_t__ codec_id; int sample_rate; int channels; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channel_layout; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_PATCHWELCOME ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 scalar_t__ AV_CODEC_ID_AMR_WB ; 
 int /*<<< orphan*/  AV_SAMPLE_FMT_S16 ; 
 int /*<<< orphan*/  avpriv_report_missing_feature (TYPE_1__*,char*) ; 

__attribute__((used)) static int amr_decode_fix_avctx(AVCodecContext *avctx)
{
    const int is_amr_wb = 1 + (avctx->codec_id == AV_CODEC_ID_AMR_WB);

    if (!avctx->sample_rate)
        avctx->sample_rate = 8000 * is_amr_wb;

    if (avctx->channels > 1) {
        avpriv_report_missing_feature(avctx, "multi-channel AMR");
        return AVERROR_PATCHWELCOME;
    }

    avctx->channels       = 1;
    avctx->channel_layout = AV_CH_LAYOUT_MONO;
    avctx->sample_fmt     = AV_SAMPLE_FMT_S16;
    return 0;
}