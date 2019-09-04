#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {int* pts_reorder_error_count; scalar_t__* pts_reorder_error; TYPE_3__* internal; TYPE_1__* codecpar; } ;
struct TYPE_8__ {TYPE_2__* avctx; } ;
struct TYPE_7__ {int has_b_frames; } ;
struct TYPE_6__ {scalar_t__ codec_id; } ;
typedef  TYPE_4__ AVStream ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_HEVC ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 scalar_t__ FFABS (scalar_t__) ; 
 scalar_t__ FFMAX (scalar_t__,scalar_t__) ; 
 scalar_t__ INT64_MAX ; 

__attribute__((used)) static int64_t select_from_pts_buffer(AVStream *st, int64_t *pts_buffer, int64_t dts) {
    int onein_oneout = st->codecpar->codec_id != AV_CODEC_ID_H264 &&
                       st->codecpar->codec_id != AV_CODEC_ID_HEVC;

    if(!onein_oneout) {
        int delay = st->internal->avctx->has_b_frames;
        int i;

        if (dts == AV_NOPTS_VALUE) {
            int64_t best_score = INT64_MAX;
            for (i = 0; i<delay; i++) {
                if (st->pts_reorder_error_count[i]) {
                    int64_t score = st->pts_reorder_error[i] / st->pts_reorder_error_count[i];
                    if (score < best_score) {
                        best_score = score;
                        dts = pts_buffer[i];
                    }
                }
            }
        } else {
            for (i = 0; i<delay; i++) {
                if (pts_buffer[i] != AV_NOPTS_VALUE) {
                    int64_t diff =  FFABS(pts_buffer[i] - dts)
                                    + (uint64_t)st->pts_reorder_error[i];
                    diff = FFMAX(diff, st->pts_reorder_error[i]);
                    st->pts_reorder_error[i] = diff;
                    st->pts_reorder_error_count[i]++;
                    if (st->pts_reorder_error_count[i] > 250) {
                        st->pts_reorder_error[i] >>= 1;
                        st->pts_reorder_error_count[i] >>= 1;
                    }
                }
            }
        }
    }

    if (dts == AV_NOPTS_VALUE)
        dts = pts_buffer[0];

    return dts;
}