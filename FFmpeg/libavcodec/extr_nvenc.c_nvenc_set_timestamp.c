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
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {scalar_t__ max_b_frames; TYPE_1__* priv_data; } ;
struct TYPE_10__ {scalar_t__ dts; int /*<<< orphan*/  pts; } ;
struct TYPE_9__ {int /*<<< orphan*/  outputTimeStamp; } ;
struct TYPE_8__ {int first_packet_output; scalar_t__* initial_pts; int /*<<< orphan*/  timestamp_list; } ;
typedef  TYPE_1__ NvencContext ;
typedef  TYPE_2__ NV_ENC_LOCK_BITSTREAM ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ERANGE ; 
 scalar_t__ INT64_MAX ; 
 scalar_t__ INT64_MIN ; 
 scalar_t__ timestamp_queue_dequeue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvenc_set_timestamp(AVCodecContext *avctx,
                               NV_ENC_LOCK_BITSTREAM *params,
                               AVPacket *pkt)
{
    NvencContext *ctx = avctx->priv_data;

    pkt->pts = params->outputTimeStamp;

    /* generate the first dts by linearly extrapolating the
     * first two pts values to the past */
    if (avctx->max_b_frames > 0 && !ctx->first_packet_output &&
        ctx->initial_pts[1] != AV_NOPTS_VALUE) {
        int64_t ts0 = ctx->initial_pts[0], ts1 = ctx->initial_pts[1];
        int64_t delta;

        if ((ts0 < 0 && ts1 > INT64_MAX + ts0) ||
            (ts0 > 0 && ts1 < INT64_MIN + ts0))
            return AVERROR(ERANGE);
        delta = ts1 - ts0;

        if ((delta < 0 && ts0 > INT64_MAX + delta) ||
            (delta > 0 && ts0 < INT64_MIN + delta))
            return AVERROR(ERANGE);
        pkt->dts = ts0 - delta;

        ctx->first_packet_output = 1;
        return 0;
    }

    pkt->dts = timestamp_queue_dequeue(ctx->timestamp_list);

    return 0;
}