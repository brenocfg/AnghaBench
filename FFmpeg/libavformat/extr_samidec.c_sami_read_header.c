#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_11__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_25__ {int /*<<< orphan*/  str; int /*<<< orphan*/  len; } ;
struct TYPE_24__ {int /*<<< orphan*/  pb; TYPE_1__* priv_data; } ;
struct TYPE_23__ {int duration; int /*<<< orphan*/  pts; scalar_t__ pos; } ;
struct TYPE_22__ {TYPE_11__* codecpar; } ;
struct TYPE_21__ {int /*<<< orphan*/  q; } ;
struct TYPE_20__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_1__ SAMIContext ;
typedef  int /*<<< orphan*/  FFTextReader ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_CODEC_ID_SAMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_bprint_clear (TYPE_5__*) ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strncasecmp (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 int ff_bprint_to_codecpar_extradata (TYPE_11__*,TYPE_5__*) ; 
 int ff_smil_extract_next_text_chunk (int /*<<< orphan*/ *,TYPE_5__*,char*) ; 
 char* ff_smil_get_attr_ptr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_subtitles_queue_finalize (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* ff_subtitles_queue_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_text_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_text_init_avio (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ff_text_pos (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtol (char const*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sami_read_header(AVFormatContext *s)
{
    SAMIContext *sami = s->priv_data;
    AVStream *st = avformat_new_stream(s, NULL);
    AVBPrint buf, hdr_buf;
    char c = 0;
    int res = 0, got_first_sync_point = 0;
    FFTextReader tr;
    ff_text_init_avio(s, &tr, s->pb);

    if (!st)
        return AVERROR(ENOMEM);
    avpriv_set_pts_info(st, 64, 1, 1000);
    st->codecpar->codec_type = AVMEDIA_TYPE_SUBTITLE;
    st->codecpar->codec_id   = AV_CODEC_ID_SAMI;

    av_bprint_init(&buf,     0, AV_BPRINT_SIZE_UNLIMITED);
    av_bprint_init(&hdr_buf, 0, AV_BPRINT_SIZE_UNLIMITED);

    while (!ff_text_eof(&tr)) {
        AVPacket *sub;
        const int64_t pos = ff_text_pos(&tr) - (c != 0);
        int is_sync, is_body, n = ff_smil_extract_next_text_chunk(&tr, &buf, &c);

        if (n == 0)
            break;

        is_body = !av_strncasecmp(buf.str, "</BODY", 6);
        if (is_body) {
             av_bprint_clear(&buf);
             break;
        }

        is_sync = !av_strncasecmp(buf.str, "<SYNC", 5);
        if (is_sync)
            got_first_sync_point = 1;

        if (!got_first_sync_point) {
            av_bprintf(&hdr_buf, "%s", buf.str);
        } else {
            sub = ff_subtitles_queue_insert(&sami->q, buf.str, buf.len, !is_sync);
            if (!sub) {
                res = AVERROR(ENOMEM);
                goto end;
            }
            if (is_sync) {
                const char *p = ff_smil_get_attr_ptr(buf.str, "Start");
                sub->pos      = pos;
                sub->pts      = p ? strtol(p, NULL, 10) : 0;
                sub->duration = -1;
            }
        }
        av_bprint_clear(&buf);
    }

    res = ff_bprint_to_codecpar_extradata(st->codecpar, &hdr_buf);
    if (res < 0)
        goto end;

    ff_subtitles_queue_finalize(s, &sami->q);

end:
    av_bprint_finalize(&buf, NULL);
    return res;
}