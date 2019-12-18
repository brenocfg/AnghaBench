#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int int64_t ;
struct TYPE_24__ {TYPE_4__* codecpar; } ;
struct TYPE_23__ {int current_pid; int pos47_full; scalar_t__ scan_all_pmts; int nb_prg; int raw_packet_size; TYPE_14__* stream; TYPE_3__* prg; TYPE_6__** pids; scalar_t__ auto_guess; } ;
struct TYPE_17__ {int (* pes_cb ) (TYPE_6__*,int const*,int,int,int) ;TYPE_5__* opaque; } ;
struct TYPE_18__ {TYPE_1__ pes_filter; } ;
struct TYPE_22__ {int last_cc; scalar_t__ type; int last_pcr; TYPE_2__ u; scalar_t__ discard; } ;
struct TYPE_21__ {int /*<<< orphan*/  flags; } ;
struct TYPE_20__ {int codec_type; } ;
struct TYPE_19__ {int /*<<< orphan*/  pmt_found; } ;
struct TYPE_16__ {int ctx_flags; int nb_streams; TYPE_8__** streams; int /*<<< orphan*/  pb; } ;
typedef  TYPE_5__ PESContext ;
typedef  TYPE_6__ MpegTSFilter ;
typedef  TYPE_7__ MpegTSContext ;
typedef  TYPE_8__ AVStream ;

/* Variables and functions */
 int AVFMTCTX_NOHEADER ; 
 int AVMEDIA_TYPE_AUDIO ; 
 int AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_PKT_FLAG_CORRUPT ; 
 int AV_RB16 (int const*) ; 
 scalar_t__ MPEGTS_PES ; 
 scalar_t__ MPEGTS_SECTION ; 
 int TS_PACKET_SIZE ; 
 int /*<<< orphan*/  add_pes_stream (TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_log (TYPE_14__*,int /*<<< orphan*/ ,char*,...) ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 scalar_t__ discard_pid (TYPE_7__*,int) ; 
 scalar_t__ parse_pcr (int*,int*,int const*) ; 
 int stub1 (TYPE_6__*,int const*,int,int,int) ; 
 int /*<<< orphan*/  write_section_data (TYPE_7__*,TYPE_6__*,int const*,int,int) ; 

__attribute__((used)) static int handle_packet(MpegTSContext *ts, const uint8_t *packet)
{
    MpegTSFilter *tss;
    int len, pid, cc, expected_cc, cc_ok, afc, is_start, is_discontinuity,
        has_adaptation, has_payload;
    const uint8_t *p, *p_end;
    int64_t pos;

    pid = AV_RB16(packet + 1) & 0x1fff;
    is_start = packet[1] & 0x40;
    tss = ts->pids[pid];
    if (ts->auto_guess && !tss && is_start) {
        add_pes_stream(ts, pid, -1);
        tss = ts->pids[pid];
    }
    if (!tss)
        return 0;
    if (is_start)
        tss->discard = discard_pid(ts, pid);
    if (tss->discard)
        return 0;
    ts->current_pid = pid;

    afc = (packet[3] >> 4) & 3;
    if (afc == 0) /* reserved value */
        return 0;
    has_adaptation   = afc & 2;
    has_payload      = afc & 1;
    is_discontinuity = has_adaptation &&
                       packet[4] != 0 && /* with length > 0 */
                       (packet[5] & 0x80); /* and discontinuity indicated */

    /* continuity check (currently not used) */
    cc = (packet[3] & 0xf);
    expected_cc = has_payload ? (tss->last_cc + 1) & 0x0f : tss->last_cc;
    cc_ok = pid == 0x1FFF || // null packet PID
            is_discontinuity ||
            tss->last_cc < 0 ||
            expected_cc == cc;

    tss->last_cc = cc;
    if (!cc_ok) {
        av_log(ts->stream, AV_LOG_DEBUG,
               "Continuity check failed for pid %d expected %d got %d\n",
               pid, expected_cc, cc);
        if (tss->type == MPEGTS_PES) {
            PESContext *pc = tss->u.pes_filter.opaque;
            pc->flags |= AV_PKT_FLAG_CORRUPT;
        }
    }

    if (packet[1] & 0x80) {
        av_log(ts->stream, AV_LOG_DEBUG, "Packet had TEI flag set; marking as corrupt\n");
        if (tss->type == MPEGTS_PES) {
            PESContext *pc = tss->u.pes_filter.opaque;
            pc->flags |= AV_PKT_FLAG_CORRUPT;
        }
    }

    p = packet + 4;
    if (has_adaptation) {
        int64_t pcr_h;
        int pcr_l;
        if (parse_pcr(&pcr_h, &pcr_l, packet) == 0)
            tss->last_pcr = pcr_h * 300 + pcr_l;
        /* skip adaptation field */
        p += p[0] + 1;
    }
    /* if past the end of packet, ignore */
    p_end = packet + TS_PACKET_SIZE;
    if (p >= p_end || !has_payload)
        return 0;

    pos = avio_tell(ts->stream->pb);
    if (pos >= 0) {
        av_assert0(pos >= TS_PACKET_SIZE);
        ts->pos47_full = pos - TS_PACKET_SIZE;
    }

    if (tss->type == MPEGTS_SECTION) {
        if (is_start) {
            /* pointer field present */
            len = *p++;
            if (len > p_end - p)
                return 0;
            if (len && cc_ok) {
                /* write remaining section bytes */
                write_section_data(ts, tss,
                                   p, len, 0);
                /* check whether filter has been closed */
                if (!ts->pids[pid])
                    return 0;
            }
            p += len;
            if (p < p_end) {
                write_section_data(ts, tss,
                                   p, p_end - p, 1);
            }
        } else {
            if (cc_ok) {
                write_section_data(ts, tss,
                                   p, p_end - p, 0);
            }
        }

        // stop find_stream_info from waiting for more streams
        // when all programs have received a PMT
        if (ts->stream->ctx_flags & AVFMTCTX_NOHEADER && ts->scan_all_pmts <= 0) {
            int i;
            for (i = 0; i < ts->nb_prg; i++) {
                if (!ts->prg[i].pmt_found)
                    break;
            }
            if (i == ts->nb_prg && ts->nb_prg > 0) {
                int types = 0;
                for (i = 0; i < ts->stream->nb_streams; i++) {
                    AVStream *st = ts->stream->streams[i];
                    if (st->codecpar->codec_type >= 0)
                        types |= 1<<st->codecpar->codec_type;
                }
                if ((types & (1<<AVMEDIA_TYPE_AUDIO) && types & (1<<AVMEDIA_TYPE_VIDEO)) || pos > 100000) {
                    av_log(ts->stream, AV_LOG_DEBUG, "All programs have pmt, headers found\n");
                    ts->stream->ctx_flags &= ~AVFMTCTX_NOHEADER;
                }
            }
        }

    } else {
        int ret;
        // Note: The position here points actually behind the current packet.
        if (tss->type == MPEGTS_PES) {
            if ((ret = tss->u.pes_filter.pes_cb(tss, p, p_end - p, is_start,
                                                pos - ts->raw_packet_size)) < 0)
                return ret;
        }
    }

    return 0;
}