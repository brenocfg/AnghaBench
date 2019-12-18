#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_18__ {int /*<<< orphan*/  stream_index; } ;
struct TYPE_17__ {int stop_parse; TYPE_10__* epg_stream; TYPE_8__* pkt; int /*<<< orphan*/  stream; } ;
struct TYPE_12__ {TYPE_6__* opaque; } ;
struct TYPE_13__ {TYPE_1__ section_filter; } ;
struct TYPE_16__ {TYPE_2__ u; } ;
struct TYPE_15__ {scalar_t__ tid; int id; } ;
struct TYPE_14__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_11__ {scalar_t__ discard; int /*<<< orphan*/  index; TYPE_3__* codecpar; int /*<<< orphan*/  id; } ;
typedef  TYPE_4__ SectionHeader ;
typedef  TYPE_5__ MpegTSFilter ;
typedef  TYPE_6__ MpegTSContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_DATA ; 
 int /*<<< orphan*/  AV_CODEC_ID_EPG ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  EIT_PID ; 
 scalar_t__ EIT_TID ; 
 scalar_t__ OEITS_END_TID ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_10__* avformat_new_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_data_packet (int /*<<< orphan*/  const*,int,TYPE_8__*) ; 
 scalar_t__ parse_section_header (TYPE_4__*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void eit_cb(MpegTSFilter *filter, const uint8_t *section, int section_len)
{
    MpegTSContext *ts = filter->u.section_filter.opaque;
    const uint8_t *p, *p_end;
    SectionHeader h1, *h = &h1;

    /*
     * Sometimes we receive EPG packets but SDT table do not have
     * eit_pres_following or eit_sched turned on, so we open EPG
     * stream directly here.
     */
    if (!ts->epg_stream) {
        ts->epg_stream = avformat_new_stream(ts->stream, NULL);
        if (!ts->epg_stream)
            return;
        ts->epg_stream->id = EIT_PID;
        ts->epg_stream->codecpar->codec_type = AVMEDIA_TYPE_DATA;
        ts->epg_stream->codecpar->codec_id = AV_CODEC_ID_EPG;
    }

    if (ts->epg_stream->discard == AVDISCARD_ALL)
        return;

    p_end = section + section_len - 4;
    p     = section;

    if (parse_section_header(h, &p, p_end) < 0)
        return;
    if (h->tid < EIT_TID || h->tid > OEITS_END_TID)
        return;

    av_log(ts->stream, AV_LOG_TRACE, "EIT: tid received = %.02x\n", h->tid);

    /**
     * Service_id 0xFFFF is reserved, it indicates that the current EIT table
     * is scrambled.
     */
    if (h->id == 0xFFFF) {
        av_log(ts->stream, AV_LOG_TRACE, "Scrambled EIT table received.\n");
        return;
    }

    /**
     * In case we receive an EPG packet before mpegts context is fully
     * initialized.
     */
    if (!ts->pkt)
        return;

    new_data_packet(section, section_len, ts->pkt);
    ts->pkt->stream_index = ts->epg_stream->index;
    ts->stop_parse = 1;
}