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
struct TYPE_9__ {int nb_decoded_frames; TYPE_3__* internal; int /*<<< orphan*/  info; TYPE_1__* codecpar; } ;
struct TYPE_8__ {TYPE_2__* avctx; } ;
struct TYPE_7__ {int has_b_frames; } ;
struct TYPE_6__ {scalar_t__ codec_id; } ;
typedef  TYPE_4__ AVStream ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_H264 ; 

__attribute__((used)) static int has_decode_delay_been_guessed(AVStream *st)
{
    if (st->codecpar->codec_id != AV_CODEC_ID_H264) return 1;
    if (!st->info) // if we have left find_stream_info then nb_decoded_frames won't increase anymore for stream copy
        return 1;
#if CONFIG_H264_DECODER
    if (st->internal->avctx->has_b_frames &&
       avpriv_h264_has_num_reorder_frames(st->internal->avctx) == st->internal->avctx->has_b_frames)
        return 1;
#endif
    if (st->internal->avctx->has_b_frames<3)
        return st->nb_decoded_frames >= 7;
    else if (st->internal->avctx->has_b_frames<4)
        return st->nb_decoded_frames >= 18;
    else
        return st->nb_decoded_frames >= 20;
}