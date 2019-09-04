#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_5__* priv_data; } ;
struct TYPE_19__ {int size; } ;
struct TYPE_18__ {TYPE_3__** pids; TYPE_6__* pkt; } ;
struct TYPE_17__ {scalar_t__ state; scalar_t__ data_index; } ;
struct TYPE_14__ {TYPE_4__* opaque; } ;
struct TYPE_15__ {TYPE_1__ pes_filter; } ;
struct TYPE_16__ {scalar_t__ type; TYPE_2__ u; } ;
typedef  TYPE_4__ PESContext ;
typedef  TYPE_5__ MpegTSContext ;
typedef  TYPE_6__ AVPacket ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ MPEGTS_PAYLOAD ; 
 scalar_t__ MPEGTS_PES ; 
 scalar_t__ MPEGTS_SKIP ; 
 int NB_PID_MAX ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_6__*) ; 
 int handle_packets (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int new_pes_packet (TYPE_4__*,TYPE_6__*) ; 

__attribute__((used)) static int mpegts_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    MpegTSContext *ts = s->priv_data;
    int ret, i;

    pkt->size = -1;
    ts->pkt = pkt;
    ret = handle_packets(ts, 0);
    if (ret < 0) {
        av_packet_unref(ts->pkt);
        /* flush pes data left */
        for (i = 0; i < NB_PID_MAX; i++)
            if (ts->pids[i] && ts->pids[i]->type == MPEGTS_PES) {
                PESContext *pes = ts->pids[i]->u.pes_filter.opaque;
                if (pes->state == MPEGTS_PAYLOAD && pes->data_index > 0) {
                    ret = new_pes_packet(pes, pkt);
                    if (ret < 0)
                        return ret;
                    pes->state = MPEGTS_SKIP;
                    ret = 0;
                    break;
                }
            }
    }

    if (!ret && pkt->size < 0)
        ret = AVERROR_INVALIDDATA;
    return ret;
}