#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct AVFormatContext {TYPE_2__* priv_data; } ;
struct TYPE_17__ {int init_range_length; int start_pos; int size; struct TYPE_17__* language; struct TYPE_17__* instreamid; struct TYPE_17__* ccgroup; TYPE_4__* avf; TYPE_4__* vtt_avf; scalar_t__ dpp; scalar_t__ duration; scalar_t__ out; int /*<<< orphan*/  base_output_dirname; scalar_t__ packets_written; } ;
typedef  TYPE_1__ VariantStream ;
struct TYPE_19__ {scalar_t__ pb; scalar_t__* url; } ;
struct TYPE_18__ {int nb_varstreams; scalar_t__ segment_type; int flags; scalar_t__ max_seg_size; int nb_ccstreams; TYPE_1__* master_m3u8_url; TYPE_1__* cc_streams; TYPE_1__* var_streams; TYPE_1__* key_basename; scalar_t__ sub_m3u8_out; scalar_t__ m3u8_out; } ;
typedef  TYPE_2__ HLSContext ;
typedef  TYPE_1__ ClosedCaptionsStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int HLS_SINGLE_FILE ; 
 int HLS_TEMP_FILE ; 
 scalar_t__ SEGMENT_TYPE_FMP4 ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  av_log (struct AVFormatContext*,int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 char* av_strdup (scalar_t__*) ; 
 int /*<<< orphan*/  av_write_frame (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_write_trailer (TYPE_4__*) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_4__*) ; 
 int avio_close_dyn_buf (scalar_t__,char**) ; 
 char* avio_find_protocol_name (scalar_t__*) ; 
 int /*<<< orphan*/  avio_flush (scalar_t__) ; 
 int /*<<< orphan*/  avio_open_dyn_buf (scalar_t__*) ; 
 void* avio_tell (scalar_t__) ; 
 int /*<<< orphan*/  avio_write (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  ff_format_io_close (struct AVFormatContext*,scalar_t__*) ; 
 int flush_dynbuf (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  hls_append_segment (struct AVFormatContext*,TYPE_2__*,TYPE_1__*,scalar_t__,void*,int) ; 
 int /*<<< orphan*/  hls_free_variant_streams (TYPE_2__*) ; 
 int /*<<< orphan*/  hls_rename_temp_file (struct AVFormatContext*,TYPE_4__*) ; 
 int /*<<< orphan*/  hls_window (struct AVFormatContext*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  hlsenc_io_close (struct AVFormatContext*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int hlsenc_io_open (struct AVFormatContext*,scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sls_flag_file_rename (TYPE_2__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  write_styp (scalar_t__) ; 

__attribute__((used)) static int hls_write_trailer(struct AVFormatContext *s)
{
    HLSContext *hls = s->priv_data;
    AVFormatContext *oc = NULL;
    AVFormatContext *vtt_oc = NULL;
    char *old_filename = NULL;
    const char *proto = NULL;
    int use_temp_file = 0;
    int i;
    int ret = 0;
    VariantStream *vs = NULL;

    for (i = 0; i < hls->nb_varstreams; i++) {
        vs = &hls->var_streams[i];

        oc = vs->avf;
        vtt_oc = vs->vtt_avf;
        old_filename = av_strdup(vs->avf->url);
        use_temp_file = 0;

        if (!old_filename) {
            return AVERROR(ENOMEM);
        }
        if ( hls->segment_type == SEGMENT_TYPE_FMP4) {
            int range_length = 0;
            if (!vs->init_range_length) {
                uint8_t *buffer = NULL;
                int range_length, byterange_mode;
                av_write_frame(vs->avf, NULL); /* Flush any buffered data */
                avio_flush(oc->pb);

                range_length = avio_close_dyn_buf(oc->pb, &buffer);
                avio_write(vs->out, buffer, range_length);
                av_free(buffer);
                vs->init_range_length = range_length;
                avio_open_dyn_buf(&oc->pb);
                vs->packets_written = 0;
                vs->start_pos = range_length;
                byterange_mode = (hls->flags & HLS_SINGLE_FILE) || (hls->max_seg_size > 0);
                if (!byterange_mode) {
                    ff_format_io_close(s, &vs->out);
                    hlsenc_io_close(s, &vs->out, vs->base_output_dirname);
                }
            }
            if (!(hls->flags & HLS_SINGLE_FILE)) {
                ret = hlsenc_io_open(s, &vs->out, vs->avf->url, NULL);
                if (ret < 0) {
                    av_log(s, AV_LOG_ERROR, "Failed to open file '%s'\n", vs->avf->url);
                    goto failed;
                }
                write_styp(vs->out);
            }
            ret = flush_dynbuf(vs, &range_length);
            if (ret < 0) {
                goto failed;
            }
            vs->size = range_length;
            ff_format_io_close(s, &vs->out);
        }

failed:
        av_write_trailer(oc);

        if (oc->url[0]) {
            proto = avio_find_protocol_name(oc->url);
            use_temp_file = proto && !strcmp(proto, "file") && (hls->flags & HLS_TEMP_FILE);
        }

        if (oc->pb) {
            if (hls->segment_type != SEGMENT_TYPE_FMP4) {
                vs->size = avio_tell(vs->avf->pb) - vs->start_pos;
                ff_format_io_close(s, &oc->pb);
            }

            // rename that segment from .tmp to the real one
            if (use_temp_file && !(hls->flags & HLS_SINGLE_FILE)) {
                hls_rename_temp_file(s, oc);
                av_free(old_filename);
                old_filename = av_strdup(vs->avf->url);

                if (!old_filename) {
                    return AVERROR(ENOMEM);
                }
            }

            /* after av_write_trailer, then duration + 1 duration per packet */
            hls_append_segment(s, hls, vs, vs->duration + vs->dpp, vs->start_pos, vs->size);
        }

        sls_flag_file_rename(hls, vs, old_filename);

        if (vtt_oc) {
            if (vtt_oc->pb)
                av_write_trailer(vtt_oc);
            vs->size = avio_tell(vs->vtt_avf->pb) - vs->start_pos;
            ff_format_io_close(s, &vtt_oc->pb);
            avformat_free_context(vtt_oc);
        }
        avformat_free_context(oc);

        vs->avf = NULL;
        hls_window(s, 1, vs);
        av_free(old_filename);
    }

    hls_free_variant_streams(hls);

    for (i = 0; i < hls->nb_ccstreams; i++) {
        ClosedCaptionsStream *ccs = &hls->cc_streams[i];
        av_freep(&ccs->ccgroup);
        av_freep(&ccs->instreamid);
        av_freep(&ccs->language);
    }

    ff_format_io_close(s, &hls->m3u8_out);
    ff_format_io_close(s, &hls->sub_m3u8_out);
    av_freep(&hls->key_basename);
    av_freep(&hls->var_streams);
    av_freep(&hls->cc_streams);
    av_freep(&hls->master_m3u8_url);
    return 0;
}