#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_49__   TYPE_9__ ;
typedef  struct TYPE_48__   TYPE_8__ ;
typedef  struct TYPE_47__   TYPE_7__ ;
typedef  struct TYPE_46__   TYPE_6__ ;
typedef  struct TYPE_45__   TYPE_5__ ;
typedef  struct TYPE_44__   TYPE_4__ ;
typedef  struct TYPE_43__   TYPE_3__ ;
typedef  struct TYPE_42__   TYPE_2__ ;
typedef  struct TYPE_41__   TYPE_26__ ;
typedef  struct TYPE_40__   TYPE_21__ ;
typedef  struct TYPE_39__   TYPE_1__ ;
typedef  struct TYPE_38__   TYPE_16__ ;
typedef  struct TYPE_37__   TYPE_13__ ;
typedef  struct TYPE_36__   TYPE_12__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_49__ {TYPE_8__* ost; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  format; int /*<<< orphan*/ * filter; } ;
struct TYPE_48__ {char* avfilter; char const* file_index; char const* index; TYPE_6__* enc_ctx; TYPE_5__* filter; TYPE_4__* enc; TYPE_3__* st; int /*<<< orphan*/  encoder_opts; int /*<<< orphan*/  resample_opts; int /*<<< orphan*/  swr_opts; int /*<<< orphan*/  sws_dict; } ;
struct TYPE_47__ {scalar_t__ sub_queue; scalar_t__ frame; } ;
struct TYPE_46__ {int /*<<< orphan*/  frame_size; } ;
struct TYPE_45__ {int /*<<< orphan*/  filter; } ;
struct TYPE_44__ {scalar_t__ type; int capabilities; } ;
struct TYPE_43__ {TYPE_2__* codecpar; } ;
struct TYPE_42__ {int /*<<< orphan*/  codec_id; } ;
struct TYPE_41__ {int nb_filters; TYPE_1__** filters; int /*<<< orphan*/  nb_threads; int /*<<< orphan*/  scale_sws_opts; } ;
struct TYPE_40__ {TYPE_10__* ist; int /*<<< orphan*/  filter; scalar_t__ eof; scalar_t__ frame_queue; } ;
struct TYPE_39__ {int /*<<< orphan*/  hw_device_ctx; } ;
struct TYPE_38__ {int /*<<< orphan*/ * device_ref; } ;
struct TYPE_37__ {char* value; int /*<<< orphan*/  key; } ;
struct TYPE_36__ {struct TYPE_36__* next; } ;
struct TYPE_35__ {char* graph_desc; int nb_outputs; int reconfiguration; int nb_inputs; TYPE_21__** inputs; TYPE_9__** outputs; TYPE_26__* graph; } ;
struct TYPE_34__ {TYPE_7__ sub2video; } ;
typedef  TYPE_8__ OutputStream ;
typedef  TYPE_9__ OutputFilter ;
typedef  TYPE_10__ InputStream ;
typedef  TYPE_11__ FilterGraph ;
typedef  int /*<<< orphan*/ * AVSubtitle ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_12__ AVFilterInOut ;
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  TYPE_13__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int AV_CODEC_CAP_VARIABLE_FRAME_SIZE ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_buffer_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffersink_get_channel_layout (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffersink_get_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffersink_get_h (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffersink_get_sample_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffersink_get_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_buffersink_set_frame_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int av_buffersrc_add_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_13__* av_dict_get (int /*<<< orphan*/ ,char*,TYPE_13__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_fifo_generic_read (scalar_t__,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 scalar_t__ av_fifo_size (scalar_t__) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  av_opt_set (TYPE_26__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strdup (char*) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,int /*<<< orphan*/ ,char*) ; 
 char const* avcodec_get_name (int /*<<< orphan*/ ) ; 
 TYPE_26__* avfilter_graph_alloc () ; 
 int avfilter_graph_config (TYPE_26__*,int /*<<< orphan*/ *) ; 
 int avfilter_graph_parse2 (TYPE_26__*,char const*,TYPE_12__**,TYPE_12__**) ; 
 int /*<<< orphan*/  avfilter_inout_free (TYPE_12__**) ; 
 int /*<<< orphan*/  avsubtitle_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  cleanup_filtergraph (TYPE_11__*) ; 
 int configure_input_filter (TYPE_11__*,TYPE_21__*,TYPE_12__*) ; 
 int /*<<< orphan*/  configure_output_filter (TYPE_11__*,TYPE_9__*,TYPE_12__*) ; 
 int /*<<< orphan*/  filter_complex_nbthreads ; 
 TYPE_16__* filter_hw_device ; 
 int /*<<< orphan*/  filter_nbthreads ; 
 int filtergraph_is_simple (TYPE_11__*) ; 
 int /*<<< orphan*/ * hw_device_ctx ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  sub2video_update (TYPE_10__*,int /*<<< orphan*/ **) ; 

int configure_filtergraph(FilterGraph *fg)
{
    AVFilterInOut *inputs, *outputs, *cur;
    int ret, i, simple = filtergraph_is_simple(fg);
    const char *graph_desc = simple ? fg->outputs[0]->ost->avfilter :
                                      fg->graph_desc;

    cleanup_filtergraph(fg);
    if (!(fg->graph = avfilter_graph_alloc()))
        return AVERROR(ENOMEM);

    if (simple) {
        OutputStream *ost = fg->outputs[0]->ost;
        char args[512];
        AVDictionaryEntry *e = NULL;

        fg->graph->nb_threads = filter_nbthreads;

        args[0] = 0;
        while ((e = av_dict_get(ost->sws_dict, "", e,
                                AV_DICT_IGNORE_SUFFIX))) {
            av_strlcatf(args, sizeof(args), "%s=%s:", e->key, e->value);
        }
        if (strlen(args))
            args[strlen(args)-1] = 0;
        fg->graph->scale_sws_opts = av_strdup(args);

        args[0] = 0;
        while ((e = av_dict_get(ost->swr_opts, "", e,
                                AV_DICT_IGNORE_SUFFIX))) {
            av_strlcatf(args, sizeof(args), "%s=%s:", e->key, e->value);
        }
        if (strlen(args))
            args[strlen(args)-1] = 0;
        av_opt_set(fg->graph, "aresample_swr_opts", args, 0);

        args[0] = '\0';
        while ((e = av_dict_get(fg->outputs[0]->ost->resample_opts, "", e,
                                AV_DICT_IGNORE_SUFFIX))) {
            av_strlcatf(args, sizeof(args), "%s=%s:", e->key, e->value);
        }
        if (strlen(args))
            args[strlen(args) - 1] = '\0';

        e = av_dict_get(ost->encoder_opts, "threads", NULL, 0);
        if (e)
            av_opt_set(fg->graph, "threads", e->value, 0);
    } else {
        fg->graph->nb_threads = filter_complex_nbthreads;
    }

    if ((ret = avfilter_graph_parse2(fg->graph, graph_desc, &inputs, &outputs)) < 0)
        goto fail;

    if (filter_hw_device || hw_device_ctx) {
        AVBufferRef *device = filter_hw_device ? filter_hw_device->device_ref
                                               : hw_device_ctx;
        for (i = 0; i < fg->graph->nb_filters; i++) {
            fg->graph->filters[i]->hw_device_ctx = av_buffer_ref(device);
            if (!fg->graph->filters[i]->hw_device_ctx) {
                ret = AVERROR(ENOMEM);
                goto fail;
            }
        }
    }

    if (simple && (!inputs || inputs->next || !outputs || outputs->next)) {
        const char *num_inputs;
        const char *num_outputs;
        if (!outputs) {
            num_outputs = "0";
        } else if (outputs->next) {
            num_outputs = ">1";
        } else {
            num_outputs = "1";
        }
        if (!inputs) {
            num_inputs = "0";
        } else if (inputs->next) {
            num_inputs = ">1";
        } else {
            num_inputs = "1";
        }
        av_log(NULL, AV_LOG_ERROR, "Simple filtergraph '%s' was expected "
               "to have exactly 1 input and 1 output."
               " However, it had %s input(s) and %s output(s)."
               " Please adjust, or use a complex filtergraph (-filter_complex) instead.\n",
               graph_desc, num_inputs, num_outputs);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    for (cur = inputs, i = 0; cur; cur = cur->next, i++)
        if ((ret = configure_input_filter(fg, fg->inputs[i], cur)) < 0) {
            avfilter_inout_free(&inputs);
            avfilter_inout_free(&outputs);
            goto fail;
        }
    avfilter_inout_free(&inputs);

    for (cur = outputs, i = 0; cur; cur = cur->next, i++)
        configure_output_filter(fg, fg->outputs[i], cur);
    avfilter_inout_free(&outputs);

    if ((ret = avfilter_graph_config(fg->graph, NULL)) < 0)
        goto fail;

    /* limit the lists of allowed formats to the ones selected, to
     * make sure they stay the same if the filtergraph is reconfigured later */
    for (i = 0; i < fg->nb_outputs; i++) {
        OutputFilter *ofilter = fg->outputs[i];
        AVFilterContext *sink = ofilter->filter;

        ofilter->format = av_buffersink_get_format(sink);

        ofilter->width  = av_buffersink_get_w(sink);
        ofilter->height = av_buffersink_get_h(sink);

        ofilter->sample_rate    = av_buffersink_get_sample_rate(sink);
        ofilter->channel_layout = av_buffersink_get_channel_layout(sink);
    }

    fg->reconfiguration = 1;

    for (i = 0; i < fg->nb_outputs; i++) {
        OutputStream *ost = fg->outputs[i]->ost;
        if (!ost->enc) {
            /* identical to the same check in ffmpeg.c, needed because
               complex filter graphs are initialized earlier */
            av_log(NULL, AV_LOG_ERROR, "Encoder (codec %s) not found for output stream #%d:%d\n",
                     avcodec_get_name(ost->st->codecpar->codec_id), ost->file_index, ost->index);
            ret = AVERROR(EINVAL);
            goto fail;
        }
        if (ost->enc->type == AVMEDIA_TYPE_AUDIO &&
            !(ost->enc->capabilities & AV_CODEC_CAP_VARIABLE_FRAME_SIZE))
            av_buffersink_set_frame_size(ost->filter->filter,
                                         ost->enc_ctx->frame_size);
    }

    for (i = 0; i < fg->nb_inputs; i++) {
        while (av_fifo_size(fg->inputs[i]->frame_queue)) {
            AVFrame *tmp;
            av_fifo_generic_read(fg->inputs[i]->frame_queue, &tmp, sizeof(tmp), NULL);
            ret = av_buffersrc_add_frame(fg->inputs[i]->filter, tmp);
            av_frame_free(&tmp);
            if (ret < 0)
                goto fail;
        }
    }

    /* send the EOFs for the finished inputs */
    for (i = 0; i < fg->nb_inputs; i++) {
        if (fg->inputs[i]->eof) {
            ret = av_buffersrc_add_frame(fg->inputs[i]->filter, NULL);
            if (ret < 0)
                goto fail;
        }
    }

    /* process queued up subtitle packets */
    for (i = 0; i < fg->nb_inputs; i++) {
        InputStream *ist = fg->inputs[i]->ist;
        if (ist->sub2video.sub_queue && ist->sub2video.frame) {
            while (av_fifo_size(ist->sub2video.sub_queue)) {
                AVSubtitle tmp;
                av_fifo_generic_read(ist->sub2video.sub_queue, &tmp, sizeof(tmp), NULL);
                sub2video_update(ist, &tmp);
                avsubtitle_free(&tmp);
            }
        }
    }

    return 0;

fail:
    cleanup_filtergraph(fg);
    return ret;
}