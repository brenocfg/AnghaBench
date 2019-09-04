#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* int64_t ;
struct TYPE_18__ {int /*<<< orphan*/  q; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ WebVTTContext ;
struct TYPE_22__ {char* str; int /*<<< orphan*/  len; } ;
struct TYPE_21__ {int /*<<< orphan*/  pb; TYPE_2__* priv_data; } ;
struct TYPE_20__ {void* duration; void* pts; void* pos; } ;
struct TYPE_19__ {int /*<<< orphan*/  disposition; TYPE_1__* codecpar; } ;
struct TYPE_17__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_CODEC_ID_WEBVTT ; 
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  AV_PKT_DATA_WEBVTT_IDENTIFIER ; 
 int /*<<< orphan*/  AV_PKT_DATA_WEBVTT_SETTINGS ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_packet_new_side_data (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 void* avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  ff_subtitles_queue_finalize (TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* ff_subtitles_queue_insert (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_subtitles_read_chunk (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 void* read_ts (char const*) ; 
 int strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int webvtt_read_header(AVFormatContext *s)
{
    WebVTTContext *webvtt = s->priv_data;
    AVBPrint header, cue;
    int res = 0;
    AVStream *st = avformat_new_stream(s, NULL);

    if (!st)
        return AVERROR(ENOMEM);
    avpriv_set_pts_info(st, 64, 1, 1000);
    st->codecpar->codec_type = AVMEDIA_TYPE_SUBTITLE;
    st->codecpar->codec_id   = AV_CODEC_ID_WEBVTT;
    st->disposition |= webvtt->kind;

    av_bprint_init(&header, 0, AV_BPRINT_SIZE_UNLIMITED);
    av_bprint_init(&cue,    0, AV_BPRINT_SIZE_UNLIMITED);

    for (;;) {
        int i;
        int64_t pos;
        AVPacket *sub;
        const char *p, *identifier, *settings;
        int identifier_len, settings_len;
        int64_t ts_start, ts_end;

        ff_subtitles_read_chunk(s->pb, &cue);

        if (!cue.len)
            break;

        p = identifier = cue.str;
        pos = avio_tell(s->pb);

        /* ignore header chunk */
        if (!strncmp(p, "\xEF\xBB\xBFWEBVTT", 9) ||
            !strncmp(p, "WEBVTT", 6) ||
            !strncmp(p, "NOTE", 4))
            continue;

        /* optional cue identifier (can be a number like in SRT or some kind of
         * chaptering id) */
        for (i = 0; p[i] && p[i] != '\n' && p[i] != '\r'; i++) {
            if (!strncmp(p + i, "-->", 3)) {
                identifier = NULL;
                break;
            }
        }
        if (!identifier)
            identifier_len = 0;
        else {
            identifier_len = strcspn(p, "\r\n");
            p += identifier_len;
            if (*p == '\r')
                p++;
            if (*p == '\n')
                p++;
        }

        /* cue timestamps */
        if ((ts_start = read_ts(p)) == AV_NOPTS_VALUE)
            break;
        if (!(p = strstr(p, "-->")))
            break;
        p += 2;
        do p++; while (*p == ' ' || *p == '\t');
        if ((ts_end = read_ts(p)) == AV_NOPTS_VALUE)
            break;

        /* optional cue settings */
        p += strcspn(p, "\n\t ");
        while (*p == '\t' || *p == ' ')
            p++;
        settings = p;
        settings_len = strcspn(p, "\r\n");
        p += settings_len;
        if (*p == '\r')
            p++;
        if (*p == '\n')
            p++;

        /* create packet */
        sub = ff_subtitles_queue_insert(&webvtt->q, p, strlen(p), 0);
        if (!sub) {
            res = AVERROR(ENOMEM);
            goto end;
        }
        sub->pos = pos;
        sub->pts = ts_start;
        sub->duration = ts_end - ts_start;

#define SET_SIDE_DATA(name, type) do {                                  \
    if (name##_len) {                                                   \
        uint8_t *buf = av_packet_new_side_data(sub, type, name##_len);  \
        if (!buf) {                                                     \
            res = AVERROR(ENOMEM);                                      \
            goto end;                                                   \
        }                                                               \
        memcpy(buf, name, name##_len);                                  \
    }                                                                   \
} while (0)

        SET_SIDE_DATA(identifier, AV_PKT_DATA_WEBVTT_IDENTIFIER);
        SET_SIDE_DATA(settings,   AV_PKT_DATA_WEBVTT_SETTINGS);
    }

    ff_subtitles_queue_finalize(s, &webvtt->q);

end:
    av_bprint_finalize(&cue,    NULL);
    av_bprint_finalize(&header, NULL);
    return res;
}