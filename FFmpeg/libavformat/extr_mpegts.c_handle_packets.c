#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_19__ {int /*<<< orphan*/  pb; } ;
struct TYPE_18__ {scalar_t__ last_pos; int stop_parse; int /*<<< orphan*/  raw_packet_size; TYPE_4__** pids; TYPE_7__* stream; } ;
struct TYPE_17__ {int /*<<< orphan*/  state; scalar_t__ data_index; int /*<<< orphan*/  buffer; } ;
struct TYPE_14__ {int last_ver; } ;
struct TYPE_13__ {TYPE_5__* opaque; } ;
struct TYPE_15__ {TYPE_2__ section_filter; TYPE_1__ pes_filter; } ;
struct TYPE_16__ {scalar_t__ type; int last_cc; int last_pcr; TYPE_3__ u; } ;
typedef  TYPE_5__ PESContext ;
typedef  TYPE_6__ MpegTSContext ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ MPEGTS_PES ; 
 scalar_t__ MPEGTS_SECTION ; 
 int /*<<< orphan*/  MPEGTS_SKIP ; 
 int NB_PID_MAX ; 
 int TS_PACKET_SIZE ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finished_reading_packet (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int handle_packet (TYPE_6__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int read_packet (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static int handle_packets(MpegTSContext *ts, int64_t nb_packets)
{
    AVFormatContext *s = ts->stream;
    uint8_t packet[TS_PACKET_SIZE + AV_INPUT_BUFFER_PADDING_SIZE];
    const uint8_t *data;
    int64_t packet_num;
    int ret = 0;

    if (avio_tell(s->pb) != ts->last_pos) {
        int i;
        av_log(ts->stream, AV_LOG_TRACE, "Skipping after seek\n");
        /* seek detected, flush pes buffer */
        for (i = 0; i < NB_PID_MAX; i++) {
            if (ts->pids[i]) {
                if (ts->pids[i]->type == MPEGTS_PES) {
                    PESContext *pes = ts->pids[i]->u.pes_filter.opaque;
                    av_buffer_unref(&pes->buffer);
                    pes->data_index = 0;
                    pes->state = MPEGTS_SKIP; /* skip until pes header */
                } else if (ts->pids[i]->type == MPEGTS_SECTION) {
                    ts->pids[i]->u.section_filter.last_ver = -1;
                }
                ts->pids[i]->last_cc = -1;
                ts->pids[i]->last_pcr = -1;
            }
        }
    }

    ts->stop_parse = 0;
    packet_num = 0;
    memset(packet + TS_PACKET_SIZE, 0, AV_INPUT_BUFFER_PADDING_SIZE);
    for (;;) {
        packet_num++;
        if (nb_packets != 0 && packet_num >= nb_packets ||
            ts->stop_parse > 1) {
            ret = AVERROR(EAGAIN);
            break;
        }
        if (ts->stop_parse > 0)
            break;

        ret = read_packet(s, packet, ts->raw_packet_size, &data);
        if (ret != 0)
            break;
        ret = handle_packet(ts, data);
        finished_reading_packet(s, ts->raw_packet_size);
        if (ret != 0)
            break;
    }
    ts->last_pos = avio_tell(s->pb);
    return ret;
}