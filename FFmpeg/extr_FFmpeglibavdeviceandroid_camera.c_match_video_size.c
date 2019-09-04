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
typedef  scalar_t__ int32_t ;
struct TYPE_8__ {scalar_t__* i32; } ;
struct TYPE_11__ {int count; TYPE_1__ data; } ;
struct TYPE_10__ {TYPE_2__* priv_data; } ;
struct TYPE_9__ {scalar_t__ requested_width; scalar_t__ requested_height; scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  camera_metadata; } ;
typedef  TYPE_2__ AndroidCameraCtx ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ ACameraMetadata_const_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ACAMERA_SCALER_AVAILABLE_STREAM_CONFIGURATIONS ; 
 int /*<<< orphan*/  ACameraMetadata_getConstEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ IMAGE_FORMAT_ANDROID ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void match_video_size(AVFormatContext *avctx)
{
    AndroidCameraCtx *ctx = avctx->priv_data;
    ACameraMetadata_const_entry available_configs;
    int found = 0;

    ACameraMetadata_getConstEntry(ctx->camera_metadata,
                                  ACAMERA_SCALER_AVAILABLE_STREAM_CONFIGURATIONS,
                                  &available_configs);

    for (int i = 0; i < available_configs.count; i++) {
        int32_t input = available_configs.data.i32[i * 4 + 3];
        int32_t format = available_configs.data.i32[i * 4 + 0];

        if (input) {
            continue;
        }

        if (format == IMAGE_FORMAT_ANDROID) {
            int32_t width = available_configs.data.i32[i * 4 + 1];
            int32_t height = available_configs.data.i32[i * 4 + 2];

            //Same ratio
            if ((ctx->requested_width == width && ctx->requested_height == height) ||
                    (ctx->requested_width == height && ctx->requested_height == width)) {
                ctx->width = width;
                ctx->height = height;
                found = 1;
                break;
            }
        }
    }

    if (!found || ctx->width == 0 || ctx->height == 0) {
        ctx->width = available_configs.data.i32[1];
        ctx->height = available_configs.data.i32[2];

        av_log(avctx, AV_LOG_WARNING,
               "Requested video_size %dx%d not available, falling back to %dx%d\n",
               ctx->requested_width, ctx->requested_height, ctx->width, ctx->height);
    }

    return;
}