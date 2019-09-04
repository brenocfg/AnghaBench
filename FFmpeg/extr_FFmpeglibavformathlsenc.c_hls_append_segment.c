#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {int dummy; } ;
typedef  void* int64_t ;
struct TYPE_19__ {scalar_t__ nb_entries; double initial_prog_date_time; int /*<<< orphan*/  sequence; TYPE_4__* old_segments; TYPE_4__* segments; TYPE_4__* last_segment; scalar_t__ discontinuity; TYPE_2__* vtt_avf; scalar_t__ has_subtitle; TYPE_1__* avf; int /*<<< orphan*/  var_stream_idx; } ;
typedef  TYPE_3__ VariantStream ;
struct TYPE_21__ {int flags; scalar_t__ max_seg_size; char const* key_uri; char const* iv_string; scalar_t__ pl_type; scalar_t__ max_nb_segments; scalar_t__ encrypt; scalar_t__ key_info_file; scalar_t__ use_localtime_mkdir; } ;
struct TYPE_20__ {char* filename; char* sub_filename; double duration; int discont; char* key_uri; char* iv_string; struct TYPE_20__* next; void* size; void* pos; int /*<<< orphan*/  var_stream_idx; } ;
struct TYPE_18__ {char* url; } ;
struct TYPE_17__ {char* url; } ;
typedef  TYPE_4__ HLSSegment ;
typedef  TYPE_5__ HLSContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HLS_DELETE_SEGMENTS ; 
 int HLS_SINGLE_FILE ; 
 scalar_t__ PLAYLIST_TYPE_NONE ; 
 char const* av_basename (char*) ; 
 int /*<<< orphan*/  av_free (TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_4__* av_malloc (int) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char const*,int) ; 
 scalar_t__ find_segment_by_filename (TYPE_4__*,char const*) ; 
 int hls_delete_old_segments (struct AVFormatContext*,TYPE_5__*,TYPE_3__*) ; 
 int sls_flags_filename_process (struct AVFormatContext*,TYPE_5__*,TYPE_3__*,TYPE_4__*,double,void*,void*) ; 

__attribute__((used)) static int hls_append_segment(struct AVFormatContext *s, HLSContext *hls,
                              VariantStream *vs, double duration, int64_t pos,
                              int64_t size)
{
    HLSSegment *en = av_malloc(sizeof(*en));
    const char  *filename;
    int byterange_mode = (hls->flags & HLS_SINGLE_FILE) || (hls->max_seg_size > 0);
    int ret;

    if (!en)
        return AVERROR(ENOMEM);

    en->var_stream_idx = vs->var_stream_idx;
    ret = sls_flags_filename_process(s, hls, vs, en, duration, pos, size);
    if (ret < 0) {
        return ret;
    }

    filename = av_basename(vs->avf->url);

    if (hls->use_localtime_mkdir) {
        filename = vs->avf->url;
    }
    if ((find_segment_by_filename(vs->segments, filename) || find_segment_by_filename(vs->old_segments, filename))
        && !byterange_mode) {
        av_log(hls, AV_LOG_WARNING, "Duplicated segment filename detected: %s\n", filename);
    }
    av_strlcpy(en->filename, filename, sizeof(en->filename));

    if(vs->has_subtitle)
        av_strlcpy(en->sub_filename, av_basename(vs->vtt_avf->url), sizeof(en->sub_filename));
    else
        en->sub_filename[0] = '\0';

    en->duration = duration;
    en->pos      = pos;
    en->size     = size;
    en->next     = NULL;
    en->discont  = 0;

    if (vs->discontinuity) {
        en->discont = 1;
        vs->discontinuity = 0;
    }

    if (hls->key_info_file || hls->encrypt) {
        av_strlcpy(en->key_uri, hls->key_uri, sizeof(en->key_uri));
        av_strlcpy(en->iv_string, hls->iv_string, sizeof(en->iv_string));
    }

    if (!vs->segments)
        vs->segments = en;
    else
        vs->last_segment->next = en;

    vs->last_segment = en;

    // EVENT or VOD playlists imply sliding window cannot be used
    if (hls->pl_type != PLAYLIST_TYPE_NONE)
        hls->max_nb_segments = 0;

    if (hls->max_nb_segments && vs->nb_entries >= hls->max_nb_segments) {
        en = vs->segments;
        vs->initial_prog_date_time += en->duration;
        vs->segments = en->next;
        if (en && hls->flags & HLS_DELETE_SEGMENTS &&
#if FF_API_HLS_WRAP
                !(hls->flags & HLS_SINGLE_FILE || hls->wrap)) {
#else
                !(hls->flags & HLS_SINGLE_FILE)) {
#endif
            en->next = vs->old_segments;
            vs->old_segments = en;
            if ((ret = hls_delete_old_segments(s, hls, vs)) < 0)
                return ret;
        } else
            av_free(en);
    } else
        vs->nb_entries++;

    if (hls->max_seg_size > 0) {
        return 0;
    }
    vs->sequence++;

    return 0;
}