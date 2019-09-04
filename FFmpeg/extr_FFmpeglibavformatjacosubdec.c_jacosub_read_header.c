#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_21__ {int nb_subs; TYPE_3__* subs; } ;
struct TYPE_20__ {TYPE_1__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_19__ {int /*<<< orphan*/  duration; int /*<<< orphan*/  pts; int /*<<< orphan*/  data; int /*<<< orphan*/  pos; } ;
struct TYPE_18__ {TYPE_12__* codecpar; } ;
struct TYPE_17__ {int timeres; TYPE_9__ q; int /*<<< orphan*/  shift; } ;
struct TYPE_16__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_1__ JACOsubContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AV_CODEC_ID_JACOSUB ; 
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int JSS_MAX_LINESIZE ; 
 int /*<<< orphan*/  av_bprint_init (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  av_bprintf (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ av_strncasecmp (char const*,int*,int) ; 
 TYPE_2__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 int** cmds ; 
 int ff_bprint_to_codecpar_extradata (TYPE_12__*,int /*<<< orphan*/ *) ; 
 int ff_get_line (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ff_subtitles_queue_finalize (TYPE_4__*,TYPE_9__*) ; 
 TYPE_3__* ff_subtitles_queue_insert (TYPE_9__*,char*,int,int) ; 
 int get_jss_cmd (char const) ; 
 int /*<<< orphan*/  get_shift (int,char const*) ; 
 int /*<<< orphan*/  jacosub_read_close (TYPE_4__*) ; 
 char* jss_skip_whitespace (char const*) ; 
 int /*<<< orphan*/  read_ts (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (int*) ; 
 int strtol (char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ timed_line (char const*) ; 

__attribute__((used)) static int jacosub_read_header(AVFormatContext *s)
{
    AVBPrint header;
    AVIOContext *pb = s->pb;
    char line[JSS_MAX_LINESIZE];
    JACOsubContext *jacosub = s->priv_data;
    int shift_set = 0; // only the first shift matters
    int merge_line = 0;
    int i, ret;

    AVStream *st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    avpriv_set_pts_info(st, 64, 1, 100);
    st->codecpar->codec_type = AVMEDIA_TYPE_SUBTITLE;
    st->codecpar->codec_id   = AV_CODEC_ID_JACOSUB;

    jacosub->timeres = 30;

    av_bprint_init(&header, 1024+AV_INPUT_BUFFER_PADDING_SIZE, 4096);

    while (!avio_feof(pb)) {
        int cmd_len;
        const char *p = line;
        int64_t pos = avio_tell(pb);
        int len = ff_get_line(pb, line, sizeof(line));

        p = jss_skip_whitespace(p);

        /* queue timed line */
        if (merge_line || timed_line(p)) {
            AVPacket *sub;

            sub = ff_subtitles_queue_insert(&jacosub->q, line, len, merge_line);
            if (!sub)
                return AVERROR(ENOMEM);
            sub->pos = pos;
            merge_line = len > 1 && !strcmp(&line[len - 2], "\\\n");
            continue;
        }

        /* skip all non-compiler commands and focus on the command */
        if (*p != '#')
            continue;
        p++;
        i = get_jss_cmd(p[0]);
        if (i == -1)
            continue;

        /* trim command + spaces */
        cmd_len = strlen(cmds[i]);
        if (av_strncasecmp(p, cmds[i], cmd_len) == 0)
            p += cmd_len;
        else
            p++;
        p = jss_skip_whitespace(p);

        /* handle commands which affect the whole script */
        switch (cmds[i][0]) {
        case 'S': // SHIFT command affect the whole script...
            if (!shift_set) {
                jacosub->shift = get_shift(jacosub->timeres, p);
                shift_set = 1;
            }
            av_bprintf(&header, "#S %s", p);
            break;
        case 'T': // ...but must be placed after TIMERES
            jacosub->timeres = strtol(p, NULL, 10);
            if (!jacosub->timeres)
                jacosub->timeres = 30;
            else
                av_bprintf(&header, "#T %s", p);
            break;
        }
    }

    /* general/essential directives in the extradata */
    ret = ff_bprint_to_codecpar_extradata(st->codecpar, &header);
    if (ret < 0)
        goto fail;

    /* SHIFT and TIMERES affect the whole script so packet timing can only be
     * done in a second pass */
    for (i = 0; i < jacosub->q.nb_subs; i++) {
        AVPacket *sub = &jacosub->q.subs[i];
        read_ts(jacosub, sub->data, &sub->pts, &sub->duration);
    }
    ff_subtitles_queue_finalize(s, &jacosub->q);

    return 0;
fail:
    jacosub_read_close(s);
    return ret;
}