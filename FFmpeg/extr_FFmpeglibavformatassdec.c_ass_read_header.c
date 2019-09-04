#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_14__ ;
typedef  struct TYPE_23__   TYPE_11__ ;

/* Type definitions */
typedef  void* int64_t ;
struct TYPE_23__ {int keep_duplicates; } ;
struct TYPE_29__ {TYPE_11__ q; } ;
struct TYPE_28__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * str; } ;
struct TYPE_27__ {int /*<<< orphan*/  pb; TYPE_5__* priv_data; } ;
struct TYPE_26__ {int duration; void* pts; void* pos; } ;
struct TYPE_25__ {TYPE_14__* codecpar; } ;
struct TYPE_24__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  int /*<<< orphan*/  FFTextReader ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVPacket ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVBPrint ;
typedef  TYPE_5__ ASSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_CODEC_ID_ASS ; 
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_4__*,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_1__*,int,int,int) ; 
 int ff_bprint_to_codecpar_extradata (TYPE_14__*,TYPE_4__*) ; 
 int /*<<< orphan*/  ff_subtitles_queue_finalize (TYPE_3__*,TYPE_11__*) ; 
 TYPE_2__* ff_subtitles_queue_insert (TYPE_11__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_text_init_avio (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* get_line (TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ read_dialogue (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *,void**,int*) ; 

__attribute__((used)) static int ass_read_header(AVFormatContext *s)
{
    ASSContext *ass = s->priv_data;
    AVBPrint header, line, rline;
    int res = 0;
    AVStream *st;
    FFTextReader tr;
    ff_text_init_avio(s, &tr, s->pb);

    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    avpriv_set_pts_info(st, 64, 1, 100);
    st->codecpar->codec_type = AVMEDIA_TYPE_SUBTITLE;
    st->codecpar->codec_id   = AV_CODEC_ID_ASS;

    av_bprint_init(&header, 0, AV_BPRINT_SIZE_UNLIMITED);
    av_bprint_init(&line,   0, AV_BPRINT_SIZE_UNLIMITED);
    av_bprint_init(&rline,  0, AV_BPRINT_SIZE_UNLIMITED);

    ass->q.keep_duplicates = 1;

    for (;;) {
        int64_t pos = get_line(&line, &tr);
        int64_t ts_start = AV_NOPTS_VALUE;
        int duration = -1;
        AVPacket *sub;

        if (!line.str[0]) // EOF
            break;

        if (read_dialogue(ass, &rline, line.str, &ts_start, &duration) < 0) {
            av_bprintf(&header, "%s", line.str);
            continue;
        }
        sub = ff_subtitles_queue_insert(&ass->q, rline.str, rline.len, 0);
        if (!sub) {
            res = AVERROR(ENOMEM);
            goto end;
        }
        sub->pos = pos;
        sub->pts = ts_start;
        sub->duration = duration;
    }

    res = ff_bprint_to_codecpar_extradata(st->codecpar, &header);
    if (res < 0)
        goto end;

    ff_subtitles_queue_finalize(s, &ass->q);

end:
    av_bprint_finalize(&header, NULL);
    av_bprint_finalize(&line,   NULL);
    av_bprint_finalize(&rline,  NULL);
    return res;
}