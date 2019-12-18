#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  roi_map; int /*<<< orphan*/  ref_frame; } ;
typedef  TYPE_1__ vpx_roi_map_t ;
struct TYPE_11__ {scalar_t__ aq_mode; int cpu_used; scalar_t__ deadline; int roi_warned; int /*<<< orphan*/  encoder; } ;
typedef  TYPE_2__ VPxContext ;
struct TYPE_12__ {TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  AVFrameSideData ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  VP9E_SET_ROI_MAP ; 
 scalar_t__ VPX_DL_REALTIME ; 
 int VPX_VERSION_MAJOR (int) ; 
 int VPX_VERSION_MINOR (int) ; 
 int VPX_VERSION_PATCH (int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_encoder_error (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int set_roi_map (TYPE_3__*,int /*<<< orphan*/  const*,int,int,TYPE_1__*,int const,int const) ; 
 scalar_t__ vpx_codec_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int vpx_codec_version () ; 

__attribute__((used)) static int vp9_encode_set_roi(AVCodecContext *avctx, int frame_width, int frame_height, const AVFrameSideData *sd)
{
    VPxContext *ctx = avctx->priv_data;

#ifdef VPX_CTRL_VP9E_SET_ROI_MAP
    int version = vpx_codec_version();
    int major = VPX_VERSION_MAJOR(version);
    int minor = VPX_VERSION_MINOR(version);
    int patch = VPX_VERSION_PATCH(version);

    if (major > 1 || (major == 1 && minor > 8) || (major == 1 && minor == 8 && patch >= 1)) {
        vpx_roi_map_t roi_map;
        const int segment_cnt = 8;
        const int block_size = 8;
        int ret;

        if (ctx->aq_mode > 0 || ctx->cpu_used < 5 || ctx->deadline != VPX_DL_REALTIME) {
            if (!ctx->roi_warned) {
                ctx->roi_warned = 1;
                av_log(avctx, AV_LOG_WARNING, "ROI is only enabled when aq_mode is 0, cpu_used >= 5 "
                                              "and deadline is REALTIME, so skipping ROI.\n");
                return AVERROR(EINVAL);
            }
        }

        ret = set_roi_map(avctx, sd, frame_width, frame_height, &roi_map, block_size, segment_cnt);
        if (ret) {
            log_encoder_error(avctx, "Failed to set_roi_map.\n");
            return ret;
        }

        memset(roi_map.ref_frame, -1, sizeof(roi_map.ref_frame));

        if (vpx_codec_control(&ctx->encoder, VP9E_SET_ROI_MAP, &roi_map)) {
            log_encoder_error(avctx, "Failed to set VP9E_SET_ROI_MAP codec control.\n");
            ret = AVERROR_INVALIDDATA;
        }
        av_freep(&roi_map.roi_map);
        return ret;
    }
#endif

    if (!ctx->roi_warned) {
        ctx->roi_warned = 1;
        av_log(avctx, AV_LOG_WARNING, "ROI is not supported, please upgrade libvpx to version >= 1.8.1. "
                                      "You may need to rebuild ffmpeg.\n");
    }
    return 0;
}