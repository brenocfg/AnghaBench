#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  roi_map; } ;
typedef  TYPE_1__ vpx_roi_map_t ;
struct TYPE_10__ {int /*<<< orphan*/  encoder; } ;
typedef  TYPE_2__ VPxContext ;
struct TYPE_11__ {TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  AVFrameSideData ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  VP8E_SET_ROI_MAP ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_encoder_error (TYPE_3__*,char*) ; 
 int set_roi_map (TYPE_3__*,int /*<<< orphan*/  const*,int,int,TYPE_1__*,int const,int const) ; 
 scalar_t__ vpx_codec_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int vp8_encode_set_roi(AVCodecContext *avctx, int frame_width, int frame_height, const AVFrameSideData *sd)
{
    vpx_roi_map_t roi_map;
    const int segment_cnt = 4;
    const int block_size = 16;
    VPxContext *ctx = avctx->priv_data;

    int ret = set_roi_map(avctx, sd, frame_width, frame_height, &roi_map, block_size, segment_cnt);
    if (ret) {
        log_encoder_error(avctx, "Failed to set_roi_map.\n");
        return ret;
    }

    if (vpx_codec_control(&ctx->encoder, VP8E_SET_ROI_MAP, &roi_map)) {
        log_encoder_error(avctx, "Failed to set VP8E_SET_ROI_MAP codec control.\n");
        ret = AVERROR_INVALIDDATA;
    }

    av_freep(&roi_map.roi_map);
    return ret;
}