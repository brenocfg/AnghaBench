#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  str; } ;
struct TYPE_19__ {int /*<<< orphan*/ * metadata; } ;
struct TYPE_18__ {int nb_chapters; TYPE_2__** chapters; int /*<<< orphan*/  duration; scalar_t__ start_time; int /*<<< orphan*/  pb; int /*<<< orphan*/ * metadata; } ;
struct TYPE_17__ {int /*<<< orphan*/ * metadata; TYPE_1__* codecpar; } ;
struct TYPE_16__ {int /*<<< orphan*/  time_base; int /*<<< orphan*/  end; } ;
struct TYPE_15__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  TYPE_5__ AVChapter ;
typedef  TYPE_6__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_DATA ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_CODEC_ID_FFMETADATA ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ID_CHAPTER ; 
 int /*<<< orphan*/  ID_STREAM ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_rescale_q (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bprint_line (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* read_chapter (TYPE_4__*) ; 
 int /*<<< orphan*/  read_tag (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_header(AVFormatContext *s)
{
    AVDictionary **m = &s->metadata;
    AVBPrint bp;

    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_UNLIMITED);

    while(!avio_feof(s->pb)) {
        get_bprint_line(s->pb, &bp);

        if (!memcmp(bp.str, ID_STREAM, strlen(ID_STREAM))) {
            AVStream *st = avformat_new_stream(s, NULL);

            if (!st)
                return AVERROR(ENOMEM);

            st->codecpar->codec_type = AVMEDIA_TYPE_DATA;
            st->codecpar->codec_id   = AV_CODEC_ID_FFMETADATA;

            m = &st->metadata;
        } else if (!memcmp(bp.str, ID_CHAPTER, strlen(ID_CHAPTER))) {
            AVChapter *ch = read_chapter(s);

            if (!ch)
                return AVERROR(ENOMEM);

            m = &ch->metadata;
        } else
            read_tag(bp.str, m);
    }

    av_bprint_finalize(&bp, NULL);

    s->start_time = 0;
    if (s->nb_chapters)
        s->duration = av_rescale_q(s->chapters[s->nb_chapters - 1]->end,
                                   s->chapters[s->nb_chapters - 1]->time_base,
                                   AV_TIME_BASE_Q);

    return 0;
}