#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_15__ {scalar_t__ data; scalar_t__ size; int /*<<< orphan*/  flags; int /*<<< orphan*/  pos; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; int /*<<< orphan*/  stream_index; TYPE_3__* buf; } ;
struct TYPE_14__ {scalar_t__ data_index; scalar_t__ total_size; scalar_t__ pes_header_size; int stream_type; int extended_stream_id; int /*<<< orphan*/  stream_id; TYPE_3__* buffer; int /*<<< orphan*/  flags; int /*<<< orphan*/  ts_packet_pos; int /*<<< orphan*/  dts; int /*<<< orphan*/  pts; TYPE_2__* st; TYPE_1__* sub_st; int /*<<< orphan*/  stream; } ;
struct TYPE_13__ {scalar_t__ data; } ;
struct TYPE_12__ {int /*<<< orphan*/  index; } ;
struct TYPE_11__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_4__ PESContext ;
typedef  TYPE_5__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PKT_DATA_MPEGTS_STREAM_ID ; 
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ MAX_PES_PAYLOAD ; 
 scalar_t__ PES_START_SIZE ; 
 int /*<<< orphan*/  av_init_packet (TYPE_5__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_pes_packet_state (TYPE_4__*) ; 

__attribute__((used)) static int new_pes_packet(PESContext *pes, AVPacket *pkt)
{
    uint8_t *sd;

    av_init_packet(pkt);

    pkt->buf  = pes->buffer;
    pkt->data = pes->buffer->data;
    pkt->size = pes->data_index;

    if (pes->total_size != MAX_PES_PAYLOAD &&
        pes->pes_header_size + pes->data_index != pes->total_size +
        PES_START_SIZE) {
        av_log(pes->stream, AV_LOG_WARNING, "PES packet size mismatch\n");
        pes->flags |= AV_PKT_FLAG_CORRUPT;
    }
    memset(pkt->data + pkt->size, 0, AV_INPUT_BUFFER_PADDING_SIZE);

    // Separate out the AC3 substream from an HDMV combined TrueHD/AC3 PID
    if (pes->sub_st && pes->stream_type == 0x83 && pes->extended_stream_id == 0x76)
        pkt->stream_index = pes->sub_st->index;
    else
        pkt->stream_index = pes->st->index;
    pkt->pts = pes->pts;
    pkt->dts = pes->dts;
    /* store position of first TS packet of this PES packet */
    pkt->pos   = pes->ts_packet_pos;
    pkt->flags = pes->flags;

    pes->buffer = NULL;
    reset_pes_packet_state(pes);

    sd = av_packet_new_side_data(pkt, AV_PKT_DATA_MPEGTS_STREAM_ID, 1);
    if (!sd)
        return AVERROR(ENOMEM);
    *sd = pes->stream_id;

    return 0;
}