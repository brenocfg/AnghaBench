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
struct TYPE_11__ {int nb_streams; TYPE_2__* priv_data; } ;
struct TYPE_10__ {TYPE_1__* codecpar; } ;
struct TYPE_9__ {int nb_sinks; int* stream_sink_map; int* sink_stream_subcc_map; } ;
struct TYPE_8__ {int /*<<< orphan*/  codec_type; int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_2__ LavfiContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AV_CODEC_ID_EIA_608 ; 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int create_subcc_streams(AVFormatContext *avctx)
{
    LavfiContext *lavfi = avctx->priv_data;
    AVStream *st;
    int stream_idx, sink_idx;

    for (stream_idx = 0; stream_idx < lavfi->nb_sinks; stream_idx++) {
        sink_idx = lavfi->stream_sink_map[stream_idx];
        if (lavfi->sink_stream_subcc_map[sink_idx]) {
            lavfi->sink_stream_subcc_map[sink_idx] = avctx->nb_streams;
            if (!(st = avformat_new_stream(avctx, NULL)))
                return AVERROR(ENOMEM);
            st->codecpar->codec_id = AV_CODEC_ID_EIA_608;
            st->codecpar->codec_type = AVMEDIA_TYPE_SUBTITLE;
        } else {
            lavfi->sink_stream_subcc_map[sink_idx] = -1;
        }
    }
    return 0;
}