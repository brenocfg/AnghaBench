#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_16__ {int /*<<< orphan*/  pb; TYPE_2__* priv_data; } ;
struct TYPE_15__ {int duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  pos; } ;
struct TYPE_14__ {TYPE_1__* codecpar; } ;
struct TYPE_13__ {int /*<<< orphan*/  q; } ;
struct TYPE_12__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ MPL2Context ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AV_CODEC_ID_MPL2 ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 TYPE_3__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ ) ; 
 int avio_rb24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int ff_get_line (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ff_subtitles_queue_finalize (TYPE_5__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* ff_subtitles_queue_insert (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_ts (char**,int /*<<< orphan*/ *,int*) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int mpl2_read_header(AVFormatContext *s)
{
    MPL2Context *mpl2 = s->priv_data;
    AVStream *st = avformat_new_stream(s, NULL);
    int res = 0;

    if (!st)
        return AVERROR(ENOMEM);
    avpriv_set_pts_info(st, 64, 1, 10);
    st->codecpar->codec_type = AVMEDIA_TYPE_SUBTITLE;
    st->codecpar->codec_id   = AV_CODEC_ID_MPL2;

    if (avio_rb24(s->pb) != 0xefbbbf)
        avio_seek(s->pb, -3, SEEK_CUR);

    while (!avio_feof(s->pb)) {
        char line[4096];
        char *p = line;
        const int64_t pos = avio_tell(s->pb);
        int len = ff_get_line(s->pb, line, sizeof(line));
        int64_t pts_start;
        int duration;

        if (!len)
            break;

        line[strcspn(line, "\r\n")] = 0;

        if (!read_ts(&p, &pts_start, &duration)) {
            AVPacket *sub;

            sub = ff_subtitles_queue_insert(&mpl2->q, p, strlen(p), 0);
            if (!sub)
                return AVERROR(ENOMEM);
            sub->pos = pos;
            sub->pts = pts_start;
            sub->duration = duration;
        }
    }

    ff_subtitles_queue_finalize(s, &mpl2->q);
    return res;
}