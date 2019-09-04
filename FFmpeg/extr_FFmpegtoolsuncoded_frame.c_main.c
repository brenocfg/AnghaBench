#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_9__ ;
typedef  struct TYPE_35__   TYPE_6__ ;
typedef  struct TYPE_34__   TYPE_5__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
struct TYPE_36__ {scalar_t__ pb; int /*<<< orphan*/  url; TYPE_1__* oformat; } ;
struct TYPE_35__ {int nb_inputs; int nb_outputs; int /*<<< orphan*/ * outputs; int /*<<< orphan*/ * inputs; } ;
struct TYPE_34__ {int nb_filters; TYPE_6__** filters; } ;
struct TYPE_33__ {scalar_t__ pts; } ;
struct TYPE_32__ {TYPE_9__* mux; TYPE_10__* stream; int /*<<< orphan*/  sink; } ;
struct TYPE_31__ {int codec_type; void* format; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  channels; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  sample_aspect_ratio; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_30__ {int flags; } ;
struct TYPE_29__ {int /*<<< orphan*/  index; int /*<<< orphan*/  time_base; TYPE_2__* codecpar; int /*<<< orphan*/  r_frame_rate; int /*<<< orphan*/  avg_frame_rate; } ;
typedef  TYPE_3__ Stream ;
typedef  TYPE_4__ AVFrame ;
typedef  TYPE_5__ AVFilterGraph ;
typedef  TYPE_6__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVFMT_NOFILE ; 
 int /*<<< orphan*/  AVIO_FLAG_WRITE ; 
#define  AVMEDIA_TYPE_AUDIO 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  AV_BUFFERSINK_FLAG_NO_REQUEST ; 
 int /*<<< orphan*/  AV_CODEC_ID_RAWVIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_buffersink_get_channel_layout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffersink_get_channels (int /*<<< orphan*/ ) ; 
 void* av_buffersink_get_format (int /*<<< orphan*/ ) ; 
 int av_buffersink_get_frame_flags (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffersink_get_frame_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffersink_get_h (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffersink_get_sample_aspect_ratio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffersink_get_sample_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffersink_get_time_base (int /*<<< orphan*/ ) ; 
 int av_buffersink_get_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_buffersink_get_w (int /*<<< orphan*/ ) ; 
 TYPE_3__* av_calloc (int,int) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 TYPE_4__* av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (TYPE_4__**) ; 
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 int /*<<< orphan*/  av_get_pcm_codec (void*,int) ; 
 int av_interleaved_write_uncoded_frame (TYPE_9__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  av_log (TYPE_9__*,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_write_trailer (TYPE_9__*) ; 
 int av_write_uncoded_frame_query (TYPE_9__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avdevice_register_all () ; 
 TYPE_5__* avfilter_graph_alloc () ; 
 int avfilter_graph_config (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avfilter_graph_free (TYPE_5__**) ; 
 int avfilter_graph_parse_ptr (TYPE_5__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avfilter_graph_request_oldest (TYPE_5__*) ; 
 int avformat_alloc_output_context2 (TYPE_9__**,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  avformat_free_context (TYPE_9__*) ; 
 TYPE_10__* avformat_new_stream (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int avformat_write_header (TYPE_9__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_closep (scalar_t__*) ; 
 int avio_open2 (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int create_sink (int /*<<< orphan*/ ,TYPE_5__*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* strchr (char*,char) ; 

int main(int argc, char **argv)
{
    char *in_graph_desc, **out_dev_name;
    int nb_out_dev = 0, nb_streams = 0;
    AVFilterGraph *in_graph = NULL;
    Stream *streams = NULL, *st;
    AVFrame *frame = NULL;
    int i, j, run = 1, ret;

    //av_log_set_level(AV_LOG_DEBUG);

    if (argc < 3) {
        av_log(NULL, AV_LOG_ERROR,
               "Usage: %s filter_graph dev:out [dev2:out2...]\n\n"
               "Examples:\n"
               "%s movie=file.nut:s=v+a xv:- alsa:default\n"
               "%s movie=file.nut:s=v+a uncodedframecrc:pipe:0\n",
               argv[0], argv[0], argv[0]);
        exit(1);
    }
    in_graph_desc = argv[1];
    out_dev_name = argv + 2;
    nb_out_dev = argc - 2;

    avdevice_register_all();

    /* Create input graph */
    if (!(in_graph = avfilter_graph_alloc())) {
        ret = AVERROR(ENOMEM);
        av_log(NULL, AV_LOG_ERROR, "Unable to alloc graph graph: %s\n",
               av_err2str(ret));
        goto fail;
    }
    ret = avfilter_graph_parse_ptr(in_graph, in_graph_desc, NULL, NULL, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Unable to parse graph: %s\n",
               av_err2str(ret));
        goto fail;
    }
    nb_streams = 0;
    for (i = 0; i < in_graph->nb_filters; i++) {
        AVFilterContext *f = in_graph->filters[i];
        for (j = 0; j < f->nb_inputs; j++) {
            if (!f->inputs[j]) {
                av_log(NULL, AV_LOG_ERROR, "Graph has unconnected inputs\n");
                ret = AVERROR(EINVAL);
                goto fail;
            }
        }
        for (j = 0; j < f->nb_outputs; j++)
            if (!f->outputs[j])
                nb_streams++;
    }
    if (!nb_streams) {
        av_log(NULL, AV_LOG_ERROR, "Graph has no output stream\n");
        ret = AVERROR(EINVAL);
        goto fail;
    }
    if (nb_out_dev != 1 && nb_out_dev != nb_streams) {
        av_log(NULL, AV_LOG_ERROR,
               "Graph has %d output streams, %d devices given\n",
               nb_streams, nb_out_dev);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    if (!(streams = av_calloc(nb_streams, sizeof(*streams)))) {
        ret = AVERROR(ENOMEM);
        av_log(NULL, AV_LOG_ERROR, "Could not allocate streams\n");
    }
    st = streams;
    for (i = 0; i < in_graph->nb_filters; i++) {
        AVFilterContext *f = in_graph->filters[i];
        for (j = 0; j < f->nb_outputs; j++) {
            if (!f->outputs[j]) {
                if ((ret = create_sink(st++, in_graph, f, j)) < 0)
                    goto fail;
            }
        }
    }
    av_assert0(st - streams == nb_streams);
    if ((ret = avfilter_graph_config(in_graph, NULL)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to configure graph\n");
        goto fail;
    }

    /* Create output devices */
    for (i = 0; i < nb_out_dev; i++) {
        char *fmt = NULL, *dev = out_dev_name[i];
        st = &streams[i];
        if ((dev = strchr(dev, ':'))) {
            *(dev++) = 0;
            fmt = out_dev_name[i];
        }
        ret = avformat_alloc_output_context2(&st->mux, NULL, fmt, dev);
        if (ret < 0) {
            av_log(NULL, AV_LOG_ERROR, "Failed to allocate output: %s\n",
                   av_err2str(ret));
            goto fail;
        }
        if (!(st->mux->oformat->flags & AVFMT_NOFILE)) {
            ret = avio_open2(&st->mux->pb, st->mux->url, AVIO_FLAG_WRITE,
                             NULL, NULL);
            if (ret < 0) {
                av_log(st->mux, AV_LOG_ERROR, "Failed to init output: %s\n",
                       av_err2str(ret));
                goto fail;
            }
        }
    }
    for (; i < nb_streams; i++)
        streams[i].mux = streams[0].mux;

    /* Create output device streams */
    for (i = 0; i < nb_streams; i++) {
        st = &streams[i];
        if (!(st->stream = avformat_new_stream(st->mux, NULL))) {
            ret = AVERROR(ENOMEM);
            av_log(NULL, AV_LOG_ERROR, "Failed to create output stream\n");
            goto fail;
        }
        st->stream->codecpar->codec_type = av_buffersink_get_type(st->sink);
        st->stream->time_base = av_buffersink_get_time_base(st->sink);
        switch (av_buffersink_get_type(st->sink)) {
        case AVMEDIA_TYPE_VIDEO:
            st->stream->codecpar->codec_id = AV_CODEC_ID_RAWVIDEO;
            st->stream->avg_frame_rate =
            st->stream->  r_frame_rate = av_buffersink_get_frame_rate(st->sink);
            st->stream->codecpar->width               = av_buffersink_get_w(st->sink);
            st->stream->codecpar->height              = av_buffersink_get_h(st->sink);
            st->stream->codecpar->sample_aspect_ratio = av_buffersink_get_sample_aspect_ratio(st->sink);
            st->stream->codecpar->format              = av_buffersink_get_format(st->sink);
            break;
        case AVMEDIA_TYPE_AUDIO:
            st->stream->codecpar->channel_layout = av_buffersink_get_channel_layout(st->sink);
            st->stream->codecpar->channels       = av_buffersink_get_channels(st->sink);
            st->stream->codecpar->sample_rate    = av_buffersink_get_sample_rate(st->sink);
            st->stream->codecpar->format         = av_buffersink_get_format(st->sink);
            st->stream->codecpar->codec_id       = av_get_pcm_codec(st->stream->codecpar->format, -1);
            break;
        default:
            av_assert0(!"reached");
        }
    }

    /* Init output devices */
    for (i = 0; i < nb_out_dev; i++) {
        st = &streams[i];
        if ((ret = avformat_write_header(st->mux, NULL)) < 0) {
            av_log(st->mux, AV_LOG_ERROR, "Failed to init output: %s\n",
                   av_err2str(ret));
            goto fail;
        }
    }

    /* Check output devices */
    for (i = 0; i < nb_streams; i++) {
        st = &streams[i];
        ret = av_write_uncoded_frame_query(st->mux, st->stream->index);
        if (ret < 0) {
            av_log(st->mux, AV_LOG_ERROR,
                   "Uncoded frames not supported on stream #%d: %s\n",
                   i, av_err2str(ret));
            goto fail;
        }
    }

    while (run) {
        ret = avfilter_graph_request_oldest(in_graph);
        if (ret < 0) {
            if (ret == AVERROR_EOF) {
                run = 0;
            } else {
                av_log(NULL, AV_LOG_ERROR, "Error filtering: %s\n",
                       av_err2str(ret));
                break;
            }
        }
        for (i = 0; i < nb_streams; i++) {
            st = &streams[i];
            while (1) {
                if (!frame && !(frame = av_frame_alloc())) {
                    ret = AVERROR(ENOMEM);
                    av_log(NULL, AV_LOG_ERROR, "Could not allocate frame\n");
                    goto fail;
                }
                ret = av_buffersink_get_frame_flags(st->sink, frame,
                                                    AV_BUFFERSINK_FLAG_NO_REQUEST);
                if (ret < 0) {
                    if (ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
                        av_log(NULL, AV_LOG_WARNING, "Error in sink: %s\n",
                               av_err2str(ret));
                    break;
                }
                if (frame->pts != AV_NOPTS_VALUE)
                    frame->pts = av_rescale_q(frame->pts,
                                              av_buffersink_get_time_base(st->sink),
                                              st->stream->time_base);
                ret = av_interleaved_write_uncoded_frame(st->mux,
                                                         st->stream->index,
                                                         frame);
                frame = NULL;
                if (ret < 0) {
                    av_log(st->mux, AV_LOG_ERROR,
                           "Error writing frame: %s\n", av_err2str(ret));
                    goto fail;
                }
            }
        }
    }
    ret = 0;

    for (i = 0; i < nb_out_dev; i++) {
        st = &streams[i];
        av_write_trailer(st->mux);
    }

fail:
    av_frame_free(&frame);
    avfilter_graph_free(&in_graph);
    if (streams) {
        for (i = 0; i < nb_out_dev; i++) {
            st = &streams[i];
            if (st->mux) {
                if (st->mux->pb)
                    avio_closep(&st->mux->pb);
                avformat_free_context(st->mux);
            }
        }
    }
    av_freep(&streams);
    return ret < 0;
}