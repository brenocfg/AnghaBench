#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_19__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_33__ {int nb_streams; TYPE_8__** streams; } ;
struct TYPE_32__ {size_t index; TYPE_1__* codecpar; } ;
struct TYPE_31__ {int nb_inputs; TYPE_19__** inputs; int /*<<< orphan*/  graph_desc; } ;
struct TYPE_30__ {scalar_t__ user_set_discard; int nb_filters; TYPE_19__** filters; TYPE_5__* st; int /*<<< orphan*/  decoding_needed; scalar_t__ discard; TYPE_2__* dec_ctx; } ;
struct TYPE_29__ {TYPE_4__* codecpar; int /*<<< orphan*/  discard; } ;
struct TYPE_28__ {int /*<<< orphan*/  codec_type; } ;
struct TYPE_27__ {int /*<<< orphan*/  name; int /*<<< orphan*/  input_pads; } ;
struct TYPE_26__ {int codec_type; } ;
struct TYPE_25__ {int codec_type; } ;
struct TYPE_24__ {int format; int /*<<< orphan*/  frame_queue; int /*<<< orphan*/  name; int /*<<< orphan*/  type; TYPE_7__* graph; TYPE_6__* ist; } ;
struct TYPE_23__ {size_t ist_index; TYPE_9__* ctx; } ;
struct TYPE_22__ {char* pad_idx; TYPE_3__* filter_ctx; scalar_t__ name; } ;
typedef  TYPE_6__ InputStream ;
typedef  TYPE_7__ FilterGraph ;
typedef  TYPE_8__ AVStream ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_9__ AVFormatContext ;
typedef  TYPE_10__ AVFilterInOut ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 int /*<<< orphan*/  AVDISCARD_NONE ; 
 int AVMEDIA_TYPE_AUDIO ; 
 int AVMEDIA_TYPE_SUBTITLE ; 
 int AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  DECODING_FOR_FILTER ; 
 int /*<<< orphan*/  GROW_ARRAY (TYPE_19__**,int) ; 
 int /*<<< orphan*/  av_assert0 (TYPE_6__*) ; 
 int /*<<< orphan*/  av_fifo_alloc (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_19__* av_mallocz (int) ; 
 int avfilter_pad_get_type (int /*<<< orphan*/ ,char*) ; 
 int check_stream_specifier (TYPE_9__*,TYPE_8__*,char*) ; 
 int /*<<< orphan*/  describe_filter_link (TYPE_7__*,TYPE_10__*,int) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 TYPE_12__** input_files ; 
 TYPE_6__** input_streams ; 
 int nb_input_files ; 
 int nb_input_streams ; 
 int strtol (scalar_t__,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_input_filter(FilterGraph *fg, AVFilterInOut *in)
{
    InputStream *ist = NULL;
    enum AVMediaType type = avfilter_pad_get_type(in->filter_ctx->input_pads, in->pad_idx);
    int i;

    // TODO: support other filter types
    if (type != AVMEDIA_TYPE_VIDEO && type != AVMEDIA_TYPE_AUDIO) {
        av_log(NULL, AV_LOG_FATAL, "Only video and audio filters supported "
               "currently.\n");
        exit_program(1);
    }

    if (in->name) {
        AVFormatContext *s;
        AVStream       *st = NULL;
        char *p;
        int file_idx = strtol(in->name, &p, 0);

        if (file_idx < 0 || file_idx >= nb_input_files) {
            av_log(NULL, AV_LOG_FATAL, "Invalid file index %d in filtergraph description %s.\n",
                   file_idx, fg->graph_desc);
            exit_program(1);
        }
        s = input_files[file_idx]->ctx;

        for (i = 0; i < s->nb_streams; i++) {
            enum AVMediaType stream_type = s->streams[i]->codecpar->codec_type;
            if (stream_type != type &&
                !(stream_type == AVMEDIA_TYPE_SUBTITLE &&
                  type == AVMEDIA_TYPE_VIDEO /* sub2video hack */))
                continue;
            if (check_stream_specifier(s, s->streams[i], *p == ':' ? p + 1 : p) == 1) {
                st = s->streams[i];
                break;
            }
        }
        if (!st) {
            av_log(NULL, AV_LOG_FATAL, "Stream specifier '%s' in filtergraph description %s "
                   "matches no streams.\n", p, fg->graph_desc);
            exit_program(1);
        }
        ist = input_streams[input_files[file_idx]->ist_index + st->index];
        if (ist->user_set_discard == AVDISCARD_ALL) {
            av_log(NULL, AV_LOG_FATAL, "Stream specifier '%s' in filtergraph description %s "
                   "matches a disabled input stream.\n", p, fg->graph_desc);
            exit_program(1);
        }
    } else {
        /* find the first unused stream of corresponding type */
        for (i = 0; i < nb_input_streams; i++) {
            ist = input_streams[i];
            if (ist->user_set_discard == AVDISCARD_ALL)
                continue;
            if (ist->dec_ctx->codec_type == type && ist->discard)
                break;
        }
        if (i == nb_input_streams) {
            av_log(NULL, AV_LOG_FATAL, "Cannot find a matching stream for "
                   "unlabeled input pad %d on filter %s\n", in->pad_idx,
                   in->filter_ctx->name);
            exit_program(1);
        }
    }
    av_assert0(ist);

    ist->discard         = 0;
    ist->decoding_needed |= DECODING_FOR_FILTER;
    ist->st->discard = AVDISCARD_NONE;

    GROW_ARRAY(fg->inputs, fg->nb_inputs);
    if (!(fg->inputs[fg->nb_inputs - 1] = av_mallocz(sizeof(*fg->inputs[0]))))
        exit_program(1);
    fg->inputs[fg->nb_inputs - 1]->ist   = ist;
    fg->inputs[fg->nb_inputs - 1]->graph = fg;
    fg->inputs[fg->nb_inputs - 1]->format = -1;
    fg->inputs[fg->nb_inputs - 1]->type = ist->st->codecpar->codec_type;
    fg->inputs[fg->nb_inputs - 1]->name = describe_filter_link(fg, in, 1);

    fg->inputs[fg->nb_inputs - 1]->frame_queue = av_fifo_alloc(8 * sizeof(AVFrame*));
    if (!fg->inputs[fg->nb_inputs - 1]->frame_queue)
        exit_program(1);

    GROW_ARRAY(ist->filters, ist->nb_filters);
    ist->filters[ist->nb_filters - 1] = fg->inputs[fg->nb_inputs - 1];
}