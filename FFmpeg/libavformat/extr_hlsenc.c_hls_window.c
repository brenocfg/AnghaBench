#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  temp_vtt_filename ;
typedef  int /*<<< orphan*/  temp_filename ;
typedef  scalar_t__ int64_t ;
struct TYPE_15__ {char* m3u8_name; scalar_t__ discontinuity_set; char* vtt_m3u8_name; int /*<<< orphan*/  out; int /*<<< orphan*/  baseurl; TYPE_2__* segments; int /*<<< orphan*/  init_range_length; int /*<<< orphan*/  fmp4_init_filename; scalar_t__ has_video; int /*<<< orphan*/  initial_prog_date_time; scalar_t__ nb_entries; scalar_t__ sequence; } ;
typedef  TYPE_1__ VariantStream ;
struct TYPE_18__ {TYPE_3__* priv_data; } ;
struct TYPE_17__ {scalar_t__ start_sequence; int flags; scalar_t__ pl_type; scalar_t__ max_seg_size; int version; scalar_t__ segment_type; scalar_t__ master_pl_name; int /*<<< orphan*/  sub_m3u8_out; int /*<<< orphan*/  m3u8_out; int /*<<< orphan*/  allowcache; scalar_t__ ignore_io_errors; scalar_t__ key_info_file; scalar_t__ encrypt; } ;
struct TYPE_16__ {int duration; char const* key_uri; char* iv_string; int /*<<< orphan*/  sub_filename; int /*<<< orphan*/  pos; int /*<<< orphan*/  size; struct TYPE_16__* next; int /*<<< orphan*/  keyframe_pos; int /*<<< orphan*/  keyframe_size; int /*<<< orphan*/  filename; int /*<<< orphan*/  discont; } ;
typedef  TYPE_2__ HLSSegment ;
typedef  TYPE_3__ HLSContext ;
typedef  TYPE_4__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ FFMAX (scalar_t__,scalar_t__) ; 
 int HLS_DISCONT_START ; 
 int HLS_INDEPENDENT_SEGMENTS ; 
 int HLS_I_FRAMES_ONLY ; 
 int HLS_OMIT_ENDLIST ; 
 int HLS_PROGRAM_DATE_TIME ; 
 int HLS_ROUND_DURATIONS ; 
 int HLS_SINGLE_FILE ; 
 int HLS_TEMP_FILE ; 
 int MAX_URL_SIZE ; 
 scalar_t__ PLAYLIST_TYPE_NONE ; 
 scalar_t__ PLAYLIST_TYPE_VOD ; 
 scalar_t__ SEGMENT_TYPE_FMP4 ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_strcasecmp (char*,char*) ; 
 char* avio_find_protocol_name (char*) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ create_master_playlist (TYPE_4__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ff_hls_write_end_list (int /*<<< orphan*/ ) ; 
 int ff_hls_write_file_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ff_hls_write_init_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_hls_write_playlist_header (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ff_rename (char*,char*,TYPE_4__*) ; 
 int hlsenc_io_close (TYPE_4__*,int /*<<< orphan*/ *,char*) ; 
 int hlsenc_io_open (TYPE_4__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int lrint (int) ; 
 int /*<<< orphan*/  set_http_options (TYPE_4__*,int /*<<< orphan*/ **,TYPE_3__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int hls_window(AVFormatContext *s, int last, VariantStream *vs)
{
    HLSContext *hls = s->priv_data;
    HLSSegment *en;
    int target_duration = 0;
    int ret = 0;
    char temp_filename[MAX_URL_SIZE];
    char temp_vtt_filename[MAX_URL_SIZE];
    int64_t sequence = FFMAX(hls->start_sequence, vs->sequence - vs->nb_entries);
    const char *proto = avio_find_protocol_name(vs->m3u8_name);
    int is_file_proto = proto && !strcmp(proto, "file");
    int use_temp_file = is_file_proto && ((hls->flags & HLS_TEMP_FILE) || !(hls->pl_type == PLAYLIST_TYPE_VOD));
    static unsigned warned_non_file;
    char *key_uri = NULL;
    char *iv_string = NULL;
    AVDictionary *options = NULL;
    double prog_date_time = vs->initial_prog_date_time;
    double *prog_date_time_p = (hls->flags & HLS_PROGRAM_DATE_TIME) ? &prog_date_time : NULL;
    int byterange_mode = (hls->flags & HLS_SINGLE_FILE) || (hls->max_seg_size > 0);

    hls->version = 3;
    if (byterange_mode) {
        hls->version = 4;
        sequence = 0;
    }

    if (hls->flags & HLS_INDEPENDENT_SEGMENTS) {
        hls->version = 6;
    }

    if (hls->segment_type == SEGMENT_TYPE_FMP4) {
        hls->version = 7;
    }

    if (!is_file_proto && (hls->flags & HLS_TEMP_FILE) && !warned_non_file++)
        av_log(s, AV_LOG_ERROR, "Cannot use rename on non file protocol, this may lead to races and temporary partial files\n");

    set_http_options(s, &options, hls);
    snprintf(temp_filename, sizeof(temp_filename), use_temp_file ? "%s.tmp" : "%s", vs->m3u8_name);
    if ((ret = hlsenc_io_open(s, byterange_mode ? &hls->m3u8_out : &vs->out, temp_filename, &options)) < 0) {
        if (hls->ignore_io_errors)
            ret = 0;
        goto fail;
    }

    for (en = vs->segments; en; en = en->next) {
        if (target_duration <= en->duration)
            target_duration = lrint(en->duration);
    }

    vs->discontinuity_set = 0;
    ff_hls_write_playlist_header(byterange_mode ? hls->m3u8_out : vs->out, hls->version, hls->allowcache,
                                 target_duration, sequence, hls->pl_type, hls->flags & HLS_I_FRAMES_ONLY);

    if ((hls->flags & HLS_DISCONT_START) && sequence==hls->start_sequence && vs->discontinuity_set==0 ) {
        avio_printf(byterange_mode ? hls->m3u8_out : vs->out, "#EXT-X-DISCONTINUITY\n");
        vs->discontinuity_set = 1;
    }
    if (vs->has_video && (hls->flags & HLS_INDEPENDENT_SEGMENTS)) {
        avio_printf(byterange_mode ? hls->m3u8_out : vs->out, "#EXT-X-INDEPENDENT-SEGMENTS\n");
    }
    for (en = vs->segments; en; en = en->next) {
        if ((hls->encrypt || hls->key_info_file) && (!key_uri || strcmp(en->key_uri, key_uri) ||
                                    av_strcasecmp(en->iv_string, iv_string))) {
            avio_printf(byterange_mode ? hls->m3u8_out : vs->out, "#EXT-X-KEY:METHOD=AES-128,URI=\"%s\"", en->key_uri);
            if (*en->iv_string)
                avio_printf(byterange_mode ? hls->m3u8_out : vs->out, ",IV=0x%s", en->iv_string);
            avio_printf(byterange_mode ? hls->m3u8_out : vs->out, "\n");
            key_uri = en->key_uri;
            iv_string = en->iv_string;
        }

        if ((hls->segment_type == SEGMENT_TYPE_FMP4) && (en == vs->segments)) {
            ff_hls_write_init_file(byterange_mode ? hls->m3u8_out : vs->out, (hls->flags & HLS_SINGLE_FILE) ? en->filename : vs->fmp4_init_filename,
                                   hls->flags & HLS_SINGLE_FILE, vs->init_range_length, 0);
        }

        ret = ff_hls_write_file_entry(byterange_mode ? hls->m3u8_out : vs->out, en->discont, byterange_mode,
                                      en->duration, hls->flags & HLS_ROUND_DURATIONS,
                                      en->size, en->pos, vs->baseurl,
                                      en->filename, prog_date_time_p, en->keyframe_size, en->keyframe_pos, hls->flags & HLS_I_FRAMES_ONLY);
        if (ret < 0) {
            av_log(s, AV_LOG_WARNING, "ff_hls_write_file_entry get error\n");
        }
    }

    if (last && (hls->flags & HLS_OMIT_ENDLIST)==0)
        ff_hls_write_end_list(byterange_mode ? hls->m3u8_out : vs->out);

    if (vs->vtt_m3u8_name) {
        snprintf(temp_vtt_filename, sizeof(temp_vtt_filename), use_temp_file ? "%s.tmp" : "%s", vs->vtt_m3u8_name);
        if ((ret = hlsenc_io_open(s, &hls->sub_m3u8_out, temp_vtt_filename, &options)) < 0) {
            if (hls->ignore_io_errors)
                ret = 0;
            goto fail;
        }
        ff_hls_write_playlist_header(hls->sub_m3u8_out, hls->version, hls->allowcache,
                                     target_duration, sequence, PLAYLIST_TYPE_NONE, 0);
        for (en = vs->segments; en; en = en->next) {
            ret = ff_hls_write_file_entry(hls->sub_m3u8_out, 0, byterange_mode,
                                          en->duration, 0, en->size, en->pos,
                                          vs->baseurl, en->sub_filename, NULL, 0, 0, 0);
            if (ret < 0) {
                av_log(s, AV_LOG_WARNING, "ff_hls_write_file_entry get error\n");
            }
        }

        if (last)
            ff_hls_write_end_list(hls->sub_m3u8_out);

    }

fail:
    av_dict_free(&options);
    ret = hlsenc_io_close(s, byterange_mode ? &hls->m3u8_out : &vs->out, temp_filename);
    if (ret < 0) {
        return ret;
    }
    hlsenc_io_close(s, &hls->sub_m3u8_out, vs->vtt_m3u8_name);
    if (use_temp_file) {
        ff_rename(temp_filename, vs->m3u8_name, s);
        if (vs->vtt_m3u8_name)
            ff_rename(temp_vtt_filename, vs->vtt_m3u8_name, s);
    }
    if (ret >= 0 && hls->master_pl_name)
        if (create_master_playlist(s, vs) < 0)
            av_log(s, AV_LOG_WARNING, "Master playlist creation failed\n");

    return ret;
}