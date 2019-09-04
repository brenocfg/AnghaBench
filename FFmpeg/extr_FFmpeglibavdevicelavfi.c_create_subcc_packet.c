#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int stream_index; int /*<<< orphan*/  pos; int /*<<< orphan*/  pts; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_1__* priv_data; } ;
struct TYPE_10__ {int nb_side_data; int /*<<< orphan*/  pkt_pos; int /*<<< orphan*/  pts; TYPE_2__** side_data; } ;
struct TYPE_9__ {scalar_t__ type; int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {int* sink_stream_subcc_map; TYPE_7__ subcc_packet; } ;
typedef  TYPE_1__ LavfiContext ;
typedef  TYPE_2__ AVFrameSideData ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AV_FRAME_DATA_A53_CC ; 
 int av_new_packet (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_subcc_packet(AVFormatContext *avctx, AVFrame *frame,
                               int sink_idx)
{
    LavfiContext *lavfi = avctx->priv_data;
    AVFrameSideData *sd;
    int stream_idx, i, ret;

    if ((stream_idx = lavfi->sink_stream_subcc_map[sink_idx]) < 0)
        return 0;
    for (i = 0; i < frame->nb_side_data; i++)
        if (frame->side_data[i]->type == AV_FRAME_DATA_A53_CC)
            break;
    if (i >= frame->nb_side_data)
        return 0;
    sd = frame->side_data[i];
    if ((ret = av_new_packet(&lavfi->subcc_packet, sd->size)) < 0)
        return ret;
    memcpy(lavfi->subcc_packet.data, sd->data, sd->size);
    lavfi->subcc_packet.stream_index = stream_idx;
    lavfi->subcc_packet.pts = frame->pts;
    lavfi->subcc_packet.pos = frame->pkt_pos;
    return 0;
}