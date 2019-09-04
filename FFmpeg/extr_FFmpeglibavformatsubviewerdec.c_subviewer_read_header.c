#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  key ;
typedef  void* int64_t ;
struct TYPE_16__ {int /*<<< orphan*/  extradata; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_15__ {int /*<<< orphan*/  pb; int /*<<< orphan*/  metadata; TYPE_1__* priv_data; } ;
struct TYPE_14__ {int duration; void* pts; void* pos; } ;
struct TYPE_13__ {TYPE_8__* codecpar; } ;
struct TYPE_12__ {int /*<<< orphan*/  q; } ;
typedef  TYPE_1__ SubViewerContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_CODEC_ID_SUBVIEWER ; 
 void* AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  av_bprint_finalize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 char av_tolower (char) ; 
 TYPE_2__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ ) ; 
 int avio_rb24 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 int ff_bprint_to_codecpar_extradata (TYPE_8__*,int /*<<< orphan*/ *) ; 
 int ff_get_line (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ff_subtitles_queue_finalize (TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* ff_subtitles_queue_insert (int /*<<< orphan*/ *,char*,int,int) ; 
 int ffio_ensure_seekback (int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_ts (char*,void**,int*) ; 
 size_t strcspn (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static int subviewer_read_header(AVFormatContext *s)
{
    SubViewerContext *subviewer = s->priv_data;
    AVStream *st = avformat_new_stream(s, NULL);
    AVBPrint header;
    int res = 0, new_event = 1;
    int64_t pts_start = AV_NOPTS_VALUE;
    int duration = -1;
    AVPacket *sub = NULL;

    if (!st)
        return AVERROR(ENOMEM);
    res = ffio_ensure_seekback(s->pb, 3);
    if (res < 0)
        return res;
    if (avio_rb24(s->pb) != 0xefbbbf)
        avio_seek(s->pb, -3, SEEK_CUR);
    avpriv_set_pts_info(st, 64, 1, 100);
    st->codecpar->codec_type = AVMEDIA_TYPE_SUBTITLE;
    st->codecpar->codec_id   = AV_CODEC_ID_SUBVIEWER;

    av_bprint_init(&header, 0, AV_BPRINT_SIZE_UNLIMITED);

    while (!avio_feof(s->pb)) {
        char line[2048];
        int64_t pos = 0;
        int len = ff_get_line(s->pb, line, sizeof(line));

        if (!len)
            break;

        line[strcspn(line, "\r\n")] = 0;

        if (line[0] == '[' && strncmp(line, "[br]", 4)) {

            /* ignore event style, XXX: add to side_data? */
            if (strstr(line, "[COLF]") || strstr(line, "[SIZE]") ||
                strstr(line, "[FONT]") || strstr(line, "[STYLE]"))
                continue;

            if (!st->codecpar->extradata) { // header not finalized yet
                av_bprintf(&header, "%s\n", line);
                if (!strncmp(line, "[END INFORMATION]", 17) || !strncmp(line, "[SUBTITLE]", 10)) {
                    /* end of header */
                    res = ff_bprint_to_codecpar_extradata(st->codecpar, &header);
                    if (res < 0)
                        goto end;
                } else if (strncmp(line, "[INFORMATION]", 13)) {
                    /* assume file metadata at this point */
                    int i, j = 0;
                    char key[32], value[128];

                    for (i = 1; i < sizeof(key) - 1 && line[i] && line[i] != ']'; i++)
                        key[i - 1] = av_tolower(line[i]);
                    key[i - 1] = 0;

                    if (line[i] == ']')
                        i++;
                    while (line[i] == ' ')
                        i++;
                    while (j < sizeof(value) - 1 && line[i] && line[i] != ']')
                        value[j++] = line[i++];
                    value[j] = 0;

                    av_dict_set(&s->metadata, key, value, 0);
                }
            }
        } else if (read_ts(line, &pts_start, &duration) >= 0) {
            new_event = 1;
            pos = avio_tell(s->pb);
        } else if (*line) {
            if (!new_event) {
                sub = ff_subtitles_queue_insert(&subviewer->q, "\n", 1, 1);
                if (!sub) {
                    res = AVERROR(ENOMEM);
                    goto end;
                }
            }
            sub = ff_subtitles_queue_insert(&subviewer->q, line, strlen(line), !new_event);
            if (!sub) {
                res = AVERROR(ENOMEM);
                goto end;
            }
            if (new_event) {
                sub->pos = pos;
                sub->pts = pts_start;
                sub->duration = duration;
            }
            new_event = 0;
        }
    }

    ff_subtitles_queue_finalize(s, &subviewer->q);

end:
    av_bprint_finalize(&header, NULL);
    return res;
}