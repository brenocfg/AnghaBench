#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int m3u8_created; int number; char* agroup; int is_default; unsigned int nb_streams; char* ccgroup; int /*<<< orphan*/  codec_attr; TYPE_5__** streams; scalar_t__ has_subtitle; scalar_t__ has_video; int /*<<< orphan*/  m3u8_name; int /*<<< orphan*/  language; } ;
typedef  TYPE_2__ VariantStream ;
struct TYPE_21__ {TYPE_3__* priv_data; } ;
struct TYPE_20__ {TYPE_1__* codecpar; } ;
struct TYPE_19__ {char* ccgroup; char* instreamid; char* language; } ;
struct TYPE_18__ {int master_m3u8_created; unsigned int nb_varstreams; int master_publish_rate; char* master_m3u8_url; unsigned int nb_ccstreams; int /*<<< orphan*/  m3u8_out; int /*<<< orphan*/  has_video_m3u8; scalar_t__ has_default_key; TYPE_4__* cc_streams; TYPE_2__* var_streams; int /*<<< orphan*/  version; } ;
struct TYPE_16__ {scalar_t__ codec_type; scalar_t__ bit_rate; } ;
typedef  TYPE_3__ HLSContext ;
typedef  TYPE_4__ ClosedCaptionsStream ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 char* av_malloc (int) ; 
 int /*<<< orphan*/  av_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ff_hls_write_audio_rendition (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  ff_hls_write_playlist_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_hls_write_stream_info (TYPE_5__*,int /*<<< orphan*/ ,int,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int get_relative_url (char*,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ get_stream_bit_rate (TYPE_5__*) ; 
 int /*<<< orphan*/  hlsenc_io_close (TYPE_6__*,int /*<<< orphan*/ *,char*) ; 
 int hlsenc_io_open (TYPE_6__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_http_options (TYPE_6__*,int /*<<< orphan*/ **,TYPE_3__*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_master_playlist(AVFormatContext *s,
                                  VariantStream * const input_vs)
{
    HLSContext *hls = s->priv_data;
    VariantStream *vs, *temp_vs;
    AVStream *vid_st, *aud_st;
    AVDictionary *options = NULL;
    unsigned int i, j;
    int m3u8_name_size, ret, bandwidth;
    char *m3u8_rel_name, *ccgroup;
    ClosedCaptionsStream *ccs;

    input_vs->m3u8_created = 1;
    if (!hls->master_m3u8_created) {
        /* For the first time, wait until all the media playlists are created */
        for (i = 0; i < hls->nb_varstreams; i++)
            if (!hls->var_streams[i].m3u8_created)
                return 0;
    } else {
         /* Keep publishing the master playlist at the configured rate */
        if (&hls->var_streams[0] != input_vs || !hls->master_publish_rate ||
            input_vs->number % hls->master_publish_rate)
            return 0;
    }

    set_http_options(s, &options, hls);

    ret = hlsenc_io_open(s, &hls->m3u8_out, hls->master_m3u8_url, &options);
    av_dict_free(&options);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to open master play list file '%s'\n",
                hls->master_m3u8_url);
        goto fail;
    }

    ff_hls_write_playlist_version(hls->m3u8_out, hls->version);

    for (i = 0; i < hls->nb_ccstreams; i++) {
        ccs = &(hls->cc_streams[i]);
        avio_printf(hls->m3u8_out, "#EXT-X-MEDIA:TYPE=CLOSED-CAPTIONS");
        avio_printf(hls->m3u8_out, ",GROUP-ID=\"%s\"", ccs->ccgroup);
        avio_printf(hls->m3u8_out, ",NAME=\"%s\"", ccs->instreamid);
        if (ccs->language)
            avio_printf(hls->m3u8_out, ",LANGUAGE=\"%s\"", ccs->language);
        avio_printf(hls->m3u8_out, ",INSTREAM-ID=\"%s\"\n", ccs->instreamid);
    }

    /* For audio only variant streams add #EXT-X-MEDIA tag with attributes*/
    for (i = 0; i < hls->nb_varstreams; i++) {
        vs = &(hls->var_streams[i]);

        if (vs->has_video || vs->has_subtitle || !vs->agroup)
            continue;

        m3u8_name_size = strlen(vs->m3u8_name) + 1;
        m3u8_rel_name = av_malloc(m3u8_name_size);
        if (!m3u8_rel_name) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        av_strlcpy(m3u8_rel_name, vs->m3u8_name, m3u8_name_size);
        ret = get_relative_url(hls->master_m3u8_url, vs->m3u8_name,
                               m3u8_rel_name, m3u8_name_size);
        if (ret < 0) {
            av_log(s, AV_LOG_ERROR, "Unable to find relative URL\n");
            goto fail;
        }

        ff_hls_write_audio_rendition(hls->m3u8_out, vs->agroup, m3u8_rel_name, vs->language, i, hls->has_default_key ? vs->is_default : 1);

        av_freep(&m3u8_rel_name);
    }

    /* For variant streams with video add #EXT-X-STREAM-INF tag with attributes*/
    for (i = 0; i < hls->nb_varstreams; i++) {
        vs = &(hls->var_streams[i]);

        m3u8_name_size = strlen(vs->m3u8_name) + 1;
        m3u8_rel_name = av_malloc(m3u8_name_size);
        if (!m3u8_rel_name) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        av_strlcpy(m3u8_rel_name, vs->m3u8_name, m3u8_name_size);
        ret = get_relative_url(hls->master_m3u8_url, vs->m3u8_name,
                               m3u8_rel_name, m3u8_name_size);
        if (ret < 0) {
            av_log(NULL, AV_LOG_ERROR, "Unable to find relative URL\n");
            goto fail;
        }

        vid_st = NULL;
        aud_st = NULL;
        for (j = 0; j < vs->nb_streams; j++) {
            if (vs->streams[j]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
                vid_st = vs->streams[j];
            else if (vs->streams[j]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
                aud_st = vs->streams[j];
        }

        if (!vid_st && !aud_st) {
            av_log(NULL, AV_LOG_WARNING, "Media stream not found\n");
            continue;
        }

        /**
         * Traverse through the list of audio only rendition streams and find
         * the rendition which has highest bitrate in the same audio group
         */
        if (vs->agroup) {
            for (j = 0; j < hls->nb_varstreams; j++) {
                temp_vs = &(hls->var_streams[j]);
                if (!temp_vs->has_video && !temp_vs->has_subtitle &&
                    temp_vs->agroup &&
                    !av_strcasecmp(temp_vs->agroup, vs->agroup)) {
                    if (!aud_st)
                        aud_st = temp_vs->streams[0];
                    if (temp_vs->streams[0]->codecpar->bit_rate >
                            aud_st->codecpar->bit_rate)
                        aud_st = temp_vs->streams[0];
                }
            }
        }

        bandwidth = 0;
        if (vid_st)
            bandwidth += get_stream_bit_rate(vid_st);
        if (aud_st)
            bandwidth += get_stream_bit_rate(aud_st);
        bandwidth += bandwidth / 10;

        ccgroup = NULL;
        if (vid_st && vs->ccgroup) {
            /* check if this group name is available in the cc map string */
            for (j = 0; j < hls->nb_ccstreams; j++) {
                ccs = &(hls->cc_streams[j]);
                if (!av_strcasecmp(ccs->ccgroup, vs->ccgroup)) {
                    ccgroup = vs->ccgroup;
                    break;
                }
            }
            if (j == hls->nb_ccstreams)
                av_log(NULL, AV_LOG_WARNING, "mapping ccgroup %s not found\n",
                        vs->ccgroup);
        }

        if (!hls->has_default_key || !hls->has_video_m3u8) {
            ff_hls_write_stream_info(vid_st, hls->m3u8_out, bandwidth, m3u8_rel_name,
                    aud_st ? vs->agroup : NULL, vs->codec_attr, ccgroup);
        } else {
            if (vid_st) {
                ff_hls_write_stream_info(vid_st, hls->m3u8_out, bandwidth, m3u8_rel_name,
                                         aud_st ? vs->agroup : NULL, vs->codec_attr, ccgroup);
            }
        }

        av_freep(&m3u8_rel_name);
    }
fail:
    if(ret >=0)
        hls->master_m3u8_created = 1;
    av_freep(&m3u8_rel_name);
    hlsenc_io_close(s, &hls->m3u8_out, hls->master_m3u8_url);
    return ret;
}