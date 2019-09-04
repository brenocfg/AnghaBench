#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct event_info {int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_20__ {int /*<<< orphan*/  len; } ;
struct TYPE_19__ {int /*<<< orphan*/  pb; TYPE_2__* priv_data; } ;
struct TYPE_18__ {TYPE_1__* codecpar; } ;
struct TYPE_17__ {int /*<<< orphan*/  q; } ;
struct TYPE_16__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ SRTContext ;
typedef  int /*<<< orphan*/  FFTextReader ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;
typedef  TYPE_5__ AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_SUBTITLE ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_CODEC_ID_SUBRIP ; 
 int /*<<< orphan*/  ENOMEM ; 
 int add_event (int /*<<< orphan*/ *,TYPE_5__*,char*,struct event_info*,int) ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_5__*,char*,char*) ; 
 TYPE_3__* avformat_new_stream (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  ff_subtitles_queue_finalize (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_subtitles_read_line (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ff_text_eof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_text_init_avio (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_text_pos (int /*<<< orphan*/ *) ; 
 scalar_t__ get_event_info (char*,struct event_info*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static int srt_read_header(AVFormatContext *s)
{
    SRTContext *srt = s->priv_data;
    AVBPrint buf;
    AVStream *st = avformat_new_stream(s, NULL);
    int res = 0;
    char line[4096], line_cache[4096];
    int has_event_info = 0;
    struct event_info ei;
    FFTextReader tr;
    ff_text_init_avio(s, &tr, s->pb);

    if (!st)
        return AVERROR(ENOMEM);
    avpriv_set_pts_info(st, 64, 1, 1000);
    st->codecpar->codec_type = AVMEDIA_TYPE_SUBTITLE;
    st->codecpar->codec_id   = AV_CODEC_ID_SUBRIP;

    av_bprint_init(&buf, 0, AV_BPRINT_SIZE_UNLIMITED);

    line_cache[0] = 0;

    while (!ff_text_eof(&tr)) {
        struct event_info tmp_ei;
        const int64_t pos = ff_text_pos(&tr);
        ptrdiff_t len = ff_subtitles_read_line(&tr, line, sizeof(line));

        if (len < 0)
            break;

        if (!len || !line[0])
            continue;

        if (get_event_info(line, &tmp_ei) < 0) {
            char *pline;

            if (!has_event_info)
                continue;

            if (line_cache[0]) {
                /* We got some cache and a new line so we assume the cached
                 * line was actually part of the payload */
                av_bprintf(&buf, "%s\n", line_cache);
                line_cache[0] = 0;
            }

            /* If the line doesn't start with a number, we assume it's part of
             * the payload, otherwise is likely an event number preceding the
             * timing information... but we can't be sure of this yet, so we
             * cache it */
            if (strtol(line, &pline, 10) < 0 || line == pline)
                av_bprintf(&buf, "%s\n", line);
            else
                strcpy(line_cache, line);
        } else {
            if (has_event_info) {
                /* We have the information of previous event, append it to the
                 * queue. We insert the cached line if and only if the payload
                 * is empty and the cached line is not a standalone number. */
                char *pline = NULL;
                const int standalone_number = strtol(line_cache, &pline, 10) >= 0 && pline && !*pline;
                res = add_event(&srt->q, &buf, line_cache, &ei, !buf.len && !standalone_number);
                if (res < 0)
                    goto end;
            } else {
                has_event_info = 1;
            }
            tmp_ei.pos = pos;
            ei = tmp_ei;
        }
    }

    /* Append the last event. Here we force the cache to be flushed, because a
     * trailing number is more likely to be geniune (for example a copyright
     * date) and not the event index of an inexistant event */
    if (has_event_info) {
        res = add_event(&srt->q, &buf, line_cache, &ei, 1);
        if (res < 0)
            goto end;
    }

    ff_subtitles_queue_finalize(s, &srt->q);

end:
    av_bprint_finalize(&buf, NULL);
    return res;
}