#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_12__ {char* data; int /*<<< orphan*/  pos; void* duration; void* pts; int /*<<< orphan*/  stream_index; } ;
struct TYPE_11__ {int /*<<< orphan*/  index; } ;
struct TYPE_10__ {int /*<<< orphan*/  queue_end; int /*<<< orphan*/  queue; } ;
typedef  int /*<<< orphan*/  MatroskaTrack ;
typedef  TYPE_1__ MatroskaDemuxContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_PKT_DATA_WEBVTT_IDENTIFIER ; 
 int /*<<< orphan*/  AV_PKT_DATA_WEBVTT_SETTINGS ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_new_packet (TYPE_3__*,int) ; 
 char* av_packet_new_side_data (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_3__*) ; 
 int ff_packet_list_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int matroska_parse_webvtt(MatroskaDemuxContext *matroska,
                                 MatroskaTrack *track,
                                 AVStream *st,
                                 uint8_t *data, int data_len,
                                 uint64_t timecode,
                                 uint64_t duration,
                                 int64_t pos)
{
    AVPacket pktl, *pkt = &pktl;
    uint8_t *id, *settings, *text, *buf;
    int id_len, settings_len, text_len;
    uint8_t *p, *q;
    int err;

    if (data_len <= 0)
        return AVERROR_INVALIDDATA;

    p = data;
    q = data + data_len;

    id = p;
    id_len = -1;
    while (p < q) {
        if (*p == '\r' || *p == '\n') {
            id_len = p - id;
            if (*p == '\r')
                p++;
            break;
        }
        p++;
    }

    if (p >= q || *p != '\n')
        return AVERROR_INVALIDDATA;
    p++;

    settings = p;
    settings_len = -1;
    while (p < q) {
        if (*p == '\r' || *p == '\n') {
            settings_len = p - settings;
            if (*p == '\r')
                p++;
            break;
        }
        p++;
    }

    if (p >= q || *p != '\n')
        return AVERROR_INVALIDDATA;
    p++;

    text = p;
    text_len = q - p;
    while (text_len > 0) {
        const int len = text_len - 1;
        const uint8_t c = p[len];
        if (c != '\r' && c != '\n')
            break;
        text_len = len;
    }

    if (text_len <= 0)
        return AVERROR_INVALIDDATA;

    err = av_new_packet(pkt, text_len);
    if (err < 0) {
        return err;
    }

    memcpy(pkt->data, text, text_len);

    if (id_len > 0) {
        buf = av_packet_new_side_data(pkt,
                                      AV_PKT_DATA_WEBVTT_IDENTIFIER,
                                      id_len);
        if (!buf) {
            av_packet_unref(pkt);
            return AVERROR(ENOMEM);
        }
        memcpy(buf, id, id_len);
    }

    if (settings_len > 0) {
        buf = av_packet_new_side_data(pkt,
                                      AV_PKT_DATA_WEBVTT_SETTINGS,
                                      settings_len);
        if (!buf) {
            av_packet_unref(pkt);
            return AVERROR(ENOMEM);
        }
        memcpy(buf, settings, settings_len);
    }

    // Do we need this for subtitles?
    // pkt->flags = AV_PKT_FLAG_KEY;

    pkt->stream_index = st->index;
    pkt->pts = timecode;

    // Do we need this for subtitles?
    // pkt->dts = timecode;

    pkt->duration = duration;
    pkt->pos = pos;

    err = ff_packet_list_put(&matroska->queue, &matroska->queue_end, pkt, 0);
    if (err < 0) {
        av_packet_unref(pkt);
        return AVERROR(ENOMEM);
    }

    return 0;
}