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
struct representation {int stream_index; scalar_t__ bandwidth; char* id; TYPE_1__* assoc_stream; } ;
typedef  int int64_t ;
struct TYPE_12__ {int duration; TYPE_1__** streams; int /*<<< orphan*/  pb; int /*<<< orphan*/  url; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int n_videos; int n_audios; int n_subtitles; struct representation** subtitles; struct representation** audios; struct representation** videos; void* is_init_section_common_audio; void* is_init_section_common_video; int /*<<< orphan*/  avio_opts; scalar_t__ media_presentation_duration; int /*<<< orphan*/  is_live; int /*<<< orphan*/ * interrupt_callback; } ;
struct TYPE_10__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_2__ DASHContext ;
typedef  int /*<<< orphan*/  AVProgram ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AV_TIME_BASE ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * av_new_program (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_program_add_stream_index (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int copy_init_section (struct representation*,struct representation*) ; 
 void* is_common_init_section_exist (struct representation**,int) ; 
 int open_demux_for_component (TYPE_3__*,struct representation*) ; 
 int parse_manifest (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int save_avio_options (TYPE_3__*) ; 

__attribute__((used)) static int dash_read_header(AVFormatContext *s)
{
    DASHContext *c = s->priv_data;
    struct representation *rep;
    int ret = 0;
    int stream_index = 0;
    int i;

    c->interrupt_callback = &s->interrupt_callback;

    if ((ret = save_avio_options(s)) < 0)
        goto fail;

    if ((ret = parse_manifest(s, s->url, s->pb)) < 0)
        goto fail;

    /* If this isn't a live stream, fill the total duration of the
     * stream. */
    if (!c->is_live) {
        s->duration = (int64_t) c->media_presentation_duration * AV_TIME_BASE;
    } else {
        av_dict_set(&c->avio_opts, "seekable", "0", 0);
    }

    if(c->n_videos)
        c->is_init_section_common_video = is_common_init_section_exist(c->videos, c->n_videos);

    /* Open the demuxer for video and audio components if available */
    for (i = 0; i < c->n_videos; i++) {
        rep = c->videos[i];
        if (i > 0 && c->is_init_section_common_video) {
            ret = copy_init_section(rep, c->videos[0]);
            if (ret < 0)
                goto fail;
        }
        ret = open_demux_for_component(s, rep);

        if (ret)
            goto fail;
        rep->stream_index = stream_index;
        ++stream_index;
    }

    if(c->n_audios)
        c->is_init_section_common_audio = is_common_init_section_exist(c->audios, c->n_audios);

    for (i = 0; i < c->n_audios; i++) {
        rep = c->audios[i];
        if (i > 0 && c->is_init_section_common_audio) {
            ret = copy_init_section(rep, c->audios[0]);
            if (ret < 0)
                goto fail;
        }
        ret = open_demux_for_component(s, rep);

        if (ret)
            goto fail;
        rep->stream_index = stream_index;
        ++stream_index;
    }

    if (c->n_subtitles)
        c->is_init_section_common_audio = is_common_init_section_exist(c->subtitles, c->n_subtitles);

    for (i = 0; i < c->n_subtitles; i++) {
        rep = c->subtitles[i];
        if (i > 0 && c->is_init_section_common_audio) {
            ret = copy_init_section(rep, c->subtitles[0]);
            if (ret < 0)
                goto fail;
        }
        ret = open_demux_for_component(s, rep);

        if (ret)
            goto fail;
        rep->stream_index = stream_index;
        ++stream_index;
    }

    if (!stream_index) {
        ret = AVERROR_INVALIDDATA;
        goto fail;
    }

    /* Create a program */
    if (!ret) {
        AVProgram *program;
        program = av_new_program(s, 0);
        if (!program) {
            goto fail;
        }

        for (i = 0; i < c->n_videos; i++) {
            rep = c->videos[i];
            av_program_add_stream_index(s, 0, rep->stream_index);
            rep->assoc_stream = s->streams[rep->stream_index];
            if (rep->bandwidth > 0)
                av_dict_set_int(&rep->assoc_stream->metadata, "variant_bitrate", rep->bandwidth, 0);
            if (rep->id[0])
                av_dict_set(&rep->assoc_stream->metadata, "id", rep->id, 0);
        }
        for (i = 0; i < c->n_audios; i++) {
            rep = c->audios[i];
            av_program_add_stream_index(s, 0, rep->stream_index);
            rep->assoc_stream = s->streams[rep->stream_index];
            if (rep->bandwidth > 0)
                av_dict_set_int(&rep->assoc_stream->metadata, "variant_bitrate", rep->bandwidth, 0);
            if (rep->id[0])
                av_dict_set(&rep->assoc_stream->metadata, "id", rep->id, 0);
        }
        for (i = 0; i < c->n_subtitles; i++) {
            rep = c->subtitles[i];
            av_program_add_stream_index(s, 0, rep->stream_index);
            rep->assoc_stream = s->streams[rep->stream_index];
            if (rep->id[0])
                av_dict_set(&rep->assoc_stream->metadata, "id", rep->id, 0);
        }
    }

    return 0;
fail:
    return ret;
}