#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int8_t ;

/* Variables and functions */
 int ALZHEIMER_DC_L0T_PRED8x8 ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
#define  DC_128_PRED8x8 130 
#define  LEFT_DC_PRED8x8 129 
#define  TOP_DC_PRED8x8 128 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*) ; 

int ff_h264_check_intra_pred_mode(void *logctx, int top_samples_available,
                                  int left_samples_available,
                                  int mode, int is_chroma)
{
    static const int8_t top[4]  = { LEFT_DC_PRED8x8, 1, -1, -1 };
    static const int8_t left[5] = { TOP_DC_PRED8x8, -1,  2, -1, DC_128_PRED8x8 };

    if (mode > 3U) {
        av_log(logctx, AV_LOG_ERROR,
               "out of range intra chroma pred mode\n");
        return AVERROR_INVALIDDATA;
    }

    if (!(top_samples_available & 0x8000)) {
        mode = top[mode];
        if (mode < 0) {
            av_log(logctx, AV_LOG_ERROR,
                   "top block unavailable for requested intra mode\n");
            return AVERROR_INVALIDDATA;
        }
    }

    if ((left_samples_available & 0x8080) != 0x8080) {
        mode = left[mode];
        if (mode < 0) {
            av_log(logctx, AV_LOG_ERROR,
                   "left block unavailable for requested intra mode\n");
            return AVERROR_INVALIDDATA;
        }
        if (is_chroma && (left_samples_available & 0x8080)) {
            // mad cow disease mode, aka MBAFF + constrained_intra_pred
            mode = ALZHEIMER_DC_L0T_PRED8x8 +
                   (!(left_samples_available & 0x8000)) +
                   2 * (mode == DC_128_PRED8x8);
        }
    }

    return mode;
}