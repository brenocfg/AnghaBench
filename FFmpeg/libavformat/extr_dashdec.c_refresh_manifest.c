#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct representation {int fragment_timescale; scalar_t__ fragments; void* cur_seq_no; scalar_t__ timelines; } ;
typedef  int int64_t ;
struct TYPE_12__ {int /*<<< orphan*/  url; TYPE_1__* priv_data; } ;
struct TYPE_11__ {int n_videos; int n_audios; int n_subtitles; char* base_url; struct representation** videos; struct representation** audios; struct representation** subtitles; } ;
typedef  TYPE_1__ DASHContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int) ; 
 void* calc_next_seg_no_from_timelines (struct representation*,int) ; 
 int /*<<< orphan*/  free_audio_list (TYPE_1__*) ; 
 int /*<<< orphan*/  free_subtitle_list (TYPE_1__*) ; 
 int /*<<< orphan*/  free_video_list (TYPE_1__*) ; 
 int get_segment_start_time_based_on_timeline (struct representation*,void*) ; 
 int /*<<< orphan*/  move_segments (struct representation*,struct representation*,TYPE_1__*) ; 
 int /*<<< orphan*/  move_timelines (struct representation*,struct representation*,TYPE_1__*) ; 
 int parse_manifest (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int refresh_manifest(AVFormatContext *s)
{
    int ret = 0, i;
    DASHContext *c = s->priv_data;
    // save current context
    int n_videos = c->n_videos;
    struct representation **videos = c->videos;
    int n_audios = c->n_audios;
    struct representation **audios = c->audios;
    int n_subtitles = c->n_subtitles;
    struct representation **subtitles = c->subtitles;
    char *base_url = c->base_url;

    c->base_url = NULL;
    c->n_videos = 0;
    c->videos = NULL;
    c->n_audios = 0;
    c->audios = NULL;
    c->n_subtitles = 0;
    c->subtitles = NULL;
    ret = parse_manifest(s, s->url, NULL);
    if (ret)
        goto finish;

    if (c->n_videos != n_videos) {
        av_log(c, AV_LOG_ERROR,
               "new manifest has mismatched no. of video representations, %d -> %d\n",
               n_videos, c->n_videos);
        return AVERROR_INVALIDDATA;
    }
    if (c->n_audios != n_audios) {
        av_log(c, AV_LOG_ERROR,
               "new manifest has mismatched no. of audio representations, %d -> %d\n",
               n_audios, c->n_audios);
        return AVERROR_INVALIDDATA;
    }
    if (c->n_subtitles != n_subtitles) {
        av_log(c, AV_LOG_ERROR,
               "new manifest has mismatched no. of subtitles representations, %d -> %d\n",
               n_subtitles, c->n_subtitles);
        return AVERROR_INVALIDDATA;
    }

    for (i = 0; i < n_videos; i++) {
        struct representation *cur_video = videos[i];
        struct representation *ccur_video = c->videos[i];
        if (cur_video->timelines) {
            // calc current time
            int64_t currentTime = get_segment_start_time_based_on_timeline(cur_video, cur_video->cur_seq_no) / cur_video->fragment_timescale;
            // update segments
            ccur_video->cur_seq_no = calc_next_seg_no_from_timelines(ccur_video, currentTime * cur_video->fragment_timescale - 1);
            if (ccur_video->cur_seq_no >= 0) {
                move_timelines(ccur_video, cur_video, c);
            }
        }
        if (cur_video->fragments) {
            move_segments(ccur_video, cur_video, c);
        }
    }
    for (i = 0; i < n_audios; i++) {
        struct representation *cur_audio = audios[i];
        struct representation *ccur_audio = c->audios[i];
        if (cur_audio->timelines) {
            // calc current time
            int64_t currentTime = get_segment_start_time_based_on_timeline(cur_audio, cur_audio->cur_seq_no) / cur_audio->fragment_timescale;
            // update segments
            ccur_audio->cur_seq_no = calc_next_seg_no_from_timelines(ccur_audio, currentTime * cur_audio->fragment_timescale - 1);
            if (ccur_audio->cur_seq_no >= 0) {
                move_timelines(ccur_audio, cur_audio, c);
            }
        }
        if (cur_audio->fragments) {
            move_segments(ccur_audio, cur_audio, c);
        }
    }

finish:
    // restore context
    if (c->base_url)
        av_free(base_url);
    else
        c->base_url  = base_url;

    if (c->subtitles)
        free_subtitle_list(c);
    if (c->audios)
        free_audio_list(c);
    if (c->videos)
        free_video_list(c);

    c->n_subtitles = n_subtitles;
    c->subtitles = subtitles;
    c->n_audios = n_audios;
    c->audios = audios;
    c->n_videos = n_videos;
    c->videos = videos;
    return ret;
}