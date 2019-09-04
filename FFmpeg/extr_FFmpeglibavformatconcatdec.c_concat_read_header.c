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
typedef  char uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_22__ {char* str; } ;
struct TYPE_21__ {int nb_streams; scalar_t__ duration; TYPE_1__** streams; int /*<<< orphan*/  pb; TYPE_4__* priv_data; } ;
struct TYPE_20__ {int safe; int nb_files; int seekable; int /*<<< orphan*/  stream_match_mode; TYPE_2__* files; } ;
struct TYPE_19__ {int /*<<< orphan*/  metadata; scalar_t__ outpoint; scalar_t__ inpoint; scalar_t__ user_duration; } ;
struct TYPE_18__ {scalar_t__ start_time; scalar_t__ user_duration; scalar_t__ inpoint; scalar_t__ outpoint; scalar_t__ duration; } ;
struct TYPE_17__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ ConcatFile ;
typedef  TYPE_4__ ConcatContext ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVERROR_EOF ; 
 int /*<<< orphan*/  AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_BPRINT_SIZE_UNLIMITED ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  FAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MATCH_EXACT_ID ; 
 int /*<<< orphan*/  MATCH_ONE_TO_ONE ; 
 int /*<<< orphan*/  SPACE_CHARS ; 
 scalar_t__ add_file (TYPE_5__*,char*,TYPE_3__**,unsigned int*) ; 
 int /*<<< orphan*/  av_bprint_finalize (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_bprint_init (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ av_dict_parse_string (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_get_token (char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ av_parse_time (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  concat_read_close (TYPE_5__*) ; 
 scalar_t__ ff_read_line_to_bprint_overwrite (int /*<<< orphan*/ ,TYPE_6__*) ; 
 char* get_keyword (char**) ; 
 scalar_t__ open_file (TYPE_5__*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int concat_read_header(AVFormatContext *avf)
{
    ConcatContext *cat = avf->priv_data;
    AVBPrint bp;
    uint8_t *cursor, *keyword;
    int line = 0, i;
    unsigned nb_files_alloc = 0;
    ConcatFile *file = NULL;
    int64_t ret, time = 0;

    av_bprint_init(&bp, 0, AV_BPRINT_SIZE_UNLIMITED);

    while ((ret = ff_read_line_to_bprint_overwrite(avf->pb, &bp)) >= 0) {
        line++;
        cursor = bp.str;
        keyword = get_keyword(&cursor);
        if (!*keyword || *keyword == '#')
            continue;

        if (!strcmp(keyword, "file")) {
            char *filename = av_get_token((const char **)&cursor, SPACE_CHARS);
            if (!filename) {
                av_log(avf, AV_LOG_ERROR, "Line %d: filename required\n", line);
                FAIL(AVERROR_INVALIDDATA);
            }
            if ((ret = add_file(avf, filename, &file, &nb_files_alloc)) < 0)
                goto fail;
        } else if (!strcmp(keyword, "duration") || !strcmp(keyword, "inpoint") || !strcmp(keyword, "outpoint")) {
            char *dur_str = get_keyword(&cursor);
            int64_t dur;
            if (!file) {
                av_log(avf, AV_LOG_ERROR, "Line %d: %s without file\n",
                       line, keyword);
                FAIL(AVERROR_INVALIDDATA);
            }
            if ((ret = av_parse_time(&dur, dur_str, 1)) < 0) {
                av_log(avf, AV_LOG_ERROR, "Line %d: invalid %s '%s'\n",
                       line, keyword, dur_str);
                goto fail;
            }
            if (!strcmp(keyword, "duration"))
                file->user_duration = dur;
            else if (!strcmp(keyword, "inpoint"))
                file->inpoint = dur;
            else if (!strcmp(keyword, "outpoint"))
                file->outpoint = dur;
        } else if (!strcmp(keyword, "file_packet_metadata")) {
            char *metadata;
            if (!file) {
                av_log(avf, AV_LOG_ERROR, "Line %d: %s without file\n",
                       line, keyword);
                FAIL(AVERROR_INVALIDDATA);
            }
            metadata = av_get_token((const char **)&cursor, SPACE_CHARS);
            if (!metadata) {
                av_log(avf, AV_LOG_ERROR, "Line %d: packet metadata required\n", line);
                FAIL(AVERROR_INVALIDDATA);
            }
            if ((ret = av_dict_parse_string(&file->metadata, metadata, "=", "", 0)) < 0) {
                av_log(avf, AV_LOG_ERROR, "Line %d: failed to parse metadata string\n", line);
                av_freep(&metadata);
                FAIL(AVERROR_INVALIDDATA);
            }
            av_freep(&metadata);
        } else if (!strcmp(keyword, "stream")) {
            if (!avformat_new_stream(avf, NULL))
                FAIL(AVERROR(ENOMEM));
        } else if (!strcmp(keyword, "exact_stream_id")) {
            if (!avf->nb_streams) {
                av_log(avf, AV_LOG_ERROR, "Line %d: exact_stream_id without stream\n",
                       line);
                FAIL(AVERROR_INVALIDDATA);
            }
            avf->streams[avf->nb_streams - 1]->id =
                strtol(get_keyword(&cursor), NULL, 0);
        } else if (!strcmp(keyword, "ffconcat")) {
            char *ver_kw  = get_keyword(&cursor);
            char *ver_val = get_keyword(&cursor);
            if (strcmp(ver_kw, "version") || strcmp(ver_val, "1.0")) {
                av_log(avf, AV_LOG_ERROR, "Line %d: invalid version\n", line);
                FAIL(AVERROR_INVALIDDATA);
            }
            if (cat->safe < 0)
                cat->safe = 1;
        } else {
            av_log(avf, AV_LOG_ERROR, "Line %d: unknown keyword '%s'\n",
                   line, keyword);
            FAIL(AVERROR_INVALIDDATA);
        }
    }
    if (ret != AVERROR_EOF && ret < 0)
        goto fail;
    if (!cat->nb_files)
        FAIL(AVERROR_INVALIDDATA);

    for (i = 0; i < cat->nb_files; i++) {
        if (cat->files[i].start_time == AV_NOPTS_VALUE)
            cat->files[i].start_time = time;
        else
            time = cat->files[i].start_time;
        if (cat->files[i].user_duration == AV_NOPTS_VALUE) {
            if (cat->files[i].inpoint == AV_NOPTS_VALUE || cat->files[i].outpoint == AV_NOPTS_VALUE)
                break;
            cat->files[i].user_duration = cat->files[i].outpoint - cat->files[i].inpoint;
        }
        cat->files[i].duration = cat->files[i].user_duration;
        time += cat->files[i].user_duration;
    }
    if (i == cat->nb_files) {
        avf->duration = time;
        cat->seekable = 1;
    }

    cat->stream_match_mode = avf->nb_streams ? MATCH_EXACT_ID :
                                               MATCH_ONE_TO_ONE;
    if ((ret = open_file(avf, 0)) < 0)
        goto fail;
    av_bprint_finalize(&bp, NULL);
    return 0;

fail:
    av_bprint_finalize(&bp, NULL);
    concat_read_close(avf);
    return ret;
}