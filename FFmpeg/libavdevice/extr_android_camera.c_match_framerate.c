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
typedef  int int32_t ;
struct TYPE_8__ {int* i32; } ;
struct TYPE_11__ {int count; TYPE_1__ data; } ;
struct TYPE_10__ {TYPE_2__* priv_data; } ;
struct TYPE_9__ {int* framerate_range; int /*<<< orphan*/  camera_metadata; int /*<<< orphan*/  framerate; } ;
typedef  TYPE_2__ AndroidCameraCtx ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ ACameraMetadata_const_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ACAMERA_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES ; 
 int /*<<< orphan*/  ACameraMetadata_getConstEntry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void match_framerate(AVFormatContext *avctx)
{
    AndroidCameraCtx *ctx = avctx->priv_data;
    ACameraMetadata_const_entry available_framerates;
    int found = 0;
    int current_best_match = -1;
    int requested_framerate = av_q2d(ctx->framerate);

    ACameraMetadata_getConstEntry(ctx->camera_metadata,
                                  ACAMERA_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES,
                                  &available_framerates);

    for (int i = 0; i < available_framerates.count; i++) {
        int32_t min = available_framerates.data.i32[i * 2 + 0];
        int32_t max = available_framerates.data.i32[i * 2 + 1];

        if (requested_framerate == max) {
            if (min == max) {
                ctx->framerate_range[0] = min;
                ctx->framerate_range[1] = max;
                found = 1;
                break;
            } else if (current_best_match >= 0) {
                int32_t current_best_match_min = available_framerates.data.i32[current_best_match * 2 + 0];
                if (min > current_best_match_min) {
                    current_best_match = i;
                }
            } else {
                current_best_match = i;
            }
        }
    }

    if (!found) {
        if (current_best_match >= 0) {
            ctx->framerate_range[0] = available_framerates.data.i32[current_best_match * 2 + 0];
            ctx->framerate_range[1] = available_framerates.data.i32[current_best_match * 2 + 1];

        } else {
            ctx->framerate_range[0] = available_framerates.data.i32[0];
            ctx->framerate_range[1] = available_framerates.data.i32[1];
        }

        av_log(avctx, AV_LOG_WARNING,
               "Requested framerate %d not available, falling back to min: %d and max: %d fps\n",
               requested_framerate, ctx->framerate_range[0], ctx->framerate_range[1]);
    }

    return;
}