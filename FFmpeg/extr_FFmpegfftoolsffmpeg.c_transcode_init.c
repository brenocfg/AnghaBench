#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_43__   TYPE_9__ ;
typedef  struct TYPE_42__   TYPE_8__ ;
typedef  struct TYPE_41__   TYPE_7__ ;
typedef  struct TYPE_40__   TYPE_6__ ;
typedef  struct TYPE_39__   TYPE_5__ ;
typedef  struct TYPE_38__   TYPE_4__ ;
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_2__ ;
typedef  struct TYPE_35__   TYPE_23__ ;
typedef  struct TYPE_34__   TYPE_1__ ;
typedef  struct TYPE_33__   TYPE_18__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  error ;
struct TYPE_43__ {TYPE_5__* ost; } ;
struct TYPE_42__ {size_t source_index; TYPE_16__* enc; scalar_t__ stream_copy; TYPE_10__* sync_ist; int /*<<< orphan*/  index; int /*<<< orphan*/  file_index; TYPE_6__* filter; scalar_t__ attachment_filename; int /*<<< orphan*/  enc_ctx; } ;
struct TYPE_41__ {int nb_programs; TYPE_13__** programs; } ;
struct TYPE_40__ {char* name; TYPE_23__* graph; } ;
struct TYPE_39__ {int source_index; } ;
struct TYPE_38__ {TYPE_10__* ist; } ;
struct TYPE_37__ {int /*<<< orphan*/  index; } ;
struct TYPE_36__ {TYPE_23__* graph; int /*<<< orphan*/  name; } ;
struct TYPE_35__ {char* index; } ;
struct TYPE_34__ {int flags; } ;
struct TYPE_33__ {TYPE_14__* ctx; } ;
struct TYPE_32__ {char* name; int /*<<< orphan*/  id; } ;
struct TYPE_31__ {char* name; } ;
struct TYPE_30__ {scalar_t__ nb_streams; TYPE_1__* oformat; } ;
struct TYPE_29__ {int nb_stream_indexes; size_t* stream_index; int discard; } ;
struct TYPE_28__ {int nb_outputs; int nb_inputs; TYPE_4__** inputs; TYPE_9__** outputs; } ;
struct TYPE_27__ {int nb_streams; int ist_index; TYPE_7__* ctx; scalar_t__ rate_emu; } ;
struct TYPE_26__ {int nb_filters; TYPE_16__* dec; TYPE_3__* st; int /*<<< orphan*/  file_index; TYPE_2__** filters; int /*<<< orphan*/  discard; int /*<<< orphan*/  start; } ;
typedef  TYPE_8__ OutputStream ;
typedef  TYPE_9__ OutputFilter ;
typedef  TYPE_10__ InputStream ;
typedef  TYPE_11__ InputFile ;
typedef  TYPE_12__ FilterGraph ;
typedef  TYPE_13__ AVProgram ;
typedef  TYPE_14__ AVFormatContext ;
typedef  TYPE_15__ AVCodecDescriptor ;
typedef  TYPE_16__ AVCodec ;

/* Variables and functions */
 int AVDISCARD_ALL ; 
 int AVDISCARD_DEFAULT ; 
 int AVFMT_NOSTREAMS ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  atomic_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_gettime_relative () ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  avcodec_close (int /*<<< orphan*/ ) ; 
 TYPE_15__* avcodec_descriptor_get (int /*<<< orphan*/ ) ; 
 int check_init_output_file (TYPE_18__*,int) ; 
 int /*<<< orphan*/  filtergraph_is_simple (TYPE_23__*) ; 
 TYPE_12__** filtergraphs ; 
 int init_input_stream (int,char*,int) ; 
 int init_output_stream (TYPE_8__*,char*,int) ; 
 TYPE_11__** input_files ; 
 TYPE_10__** input_streams ; 
 int nb_filtergraphs ; 
 int nb_input_files ; 
 int nb_input_streams ; 
 int nb_output_files ; 
 int nb_output_streams ; 
 TYPE_18__** output_files ; 
 TYPE_8__** output_streams ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  transcode_init_done ; 

__attribute__((used)) static int transcode_init(void)
{
    int ret = 0, i, j, k;
    AVFormatContext *oc;
    OutputStream *ost;
    InputStream *ist;
    char error[1024] = {0};

    for (i = 0; i < nb_filtergraphs; i++) {
        FilterGraph *fg = filtergraphs[i];
        for (j = 0; j < fg->nb_outputs; j++) {
            OutputFilter *ofilter = fg->outputs[j];
            if (!ofilter->ost || ofilter->ost->source_index >= 0)
                continue;
            if (fg->nb_inputs != 1)
                continue;
            for (k = nb_input_streams-1; k >= 0 ; k--)
                if (fg->inputs[0]->ist == input_streams[k])
                    break;
            ofilter->ost->source_index = k;
        }
    }

    /* init framerate emulation */
    for (i = 0; i < nb_input_files; i++) {
        InputFile *ifile = input_files[i];
        if (ifile->rate_emu)
            for (j = 0; j < ifile->nb_streams; j++)
                input_streams[j + ifile->ist_index]->start = av_gettime_relative();
    }

    /* init input streams */
    for (i = 0; i < nb_input_streams; i++)
        if ((ret = init_input_stream(i, error, sizeof(error))) < 0) {
            for (i = 0; i < nb_output_streams; i++) {
                ost = output_streams[i];
                avcodec_close(ost->enc_ctx);
            }
            goto dump_format;
        }

    /* open each encoder */
    for (i = 0; i < nb_output_streams; i++) {
        // skip streams fed from filtergraphs until we have a frame for them
        if (output_streams[i]->filter)
            continue;

        ret = init_output_stream(output_streams[i], error, sizeof(error));
        if (ret < 0)
            goto dump_format;
    }

    /* discard unused programs */
    for (i = 0; i < nb_input_files; i++) {
        InputFile *ifile = input_files[i];
        for (j = 0; j < ifile->ctx->nb_programs; j++) {
            AVProgram *p = ifile->ctx->programs[j];
            int discard  = AVDISCARD_ALL;

            for (k = 0; k < p->nb_stream_indexes; k++)
                if (!input_streams[ifile->ist_index + p->stream_index[k]]->discard) {
                    discard = AVDISCARD_DEFAULT;
                    break;
                }
            p->discard = discard;
        }
    }

    /* write headers for files with no streams */
    for (i = 0; i < nb_output_files; i++) {
        oc = output_files[i]->ctx;
        if (oc->oformat->flags & AVFMT_NOSTREAMS && oc->nb_streams == 0) {
            ret = check_init_output_file(output_files[i], i);
            if (ret < 0)
                goto dump_format;
        }
    }

 dump_format:
    /* dump the stream mapping */
    av_log(NULL, AV_LOG_INFO, "Stream mapping:\n");
    for (i = 0; i < nb_input_streams; i++) {
        ist = input_streams[i];

        for (j = 0; j < ist->nb_filters; j++) {
            if (!filtergraph_is_simple(ist->filters[j]->graph)) {
                av_log(NULL, AV_LOG_INFO, "  Stream #%d:%d (%s) -> %s",
                       ist->file_index, ist->st->index, ist->dec ? ist->dec->name : "?",
                       ist->filters[j]->name);
                if (nb_filtergraphs > 1)
                    av_log(NULL, AV_LOG_INFO, " (graph %d)", ist->filters[j]->graph->index);
                av_log(NULL, AV_LOG_INFO, "\n");
            }
        }
    }

    for (i = 0; i < nb_output_streams; i++) {
        ost = output_streams[i];

        if (ost->attachment_filename) {
            /* an attached file */
            av_log(NULL, AV_LOG_INFO, "  File %s -> Stream #%d:%d\n",
                   ost->attachment_filename, ost->file_index, ost->index);
            continue;
        }

        if (ost->filter && !filtergraph_is_simple(ost->filter->graph)) {
            /* output from a complex graph */
            av_log(NULL, AV_LOG_INFO, "  %s", ost->filter->name);
            if (nb_filtergraphs > 1)
                av_log(NULL, AV_LOG_INFO, " (graph %d)", ost->filter->graph->index);

            av_log(NULL, AV_LOG_INFO, " -> Stream #%d:%d (%s)\n", ost->file_index,
                   ost->index, ost->enc ? ost->enc->name : "?");
            continue;
        }

        av_log(NULL, AV_LOG_INFO, "  Stream #%d:%d -> #%d:%d",
               input_streams[ost->source_index]->file_index,
               input_streams[ost->source_index]->st->index,
               ost->file_index,
               ost->index);
        if (ost->sync_ist != input_streams[ost->source_index])
            av_log(NULL, AV_LOG_INFO, " [sync #%d:%d]",
                   ost->sync_ist->file_index,
                   ost->sync_ist->st->index);
        if (ost->stream_copy)
            av_log(NULL, AV_LOG_INFO, " (copy)");
        else {
            const AVCodec *in_codec    = input_streams[ost->source_index]->dec;
            const AVCodec *out_codec   = ost->enc;
            const char *decoder_name   = "?";
            const char *in_codec_name  = "?";
            const char *encoder_name   = "?";
            const char *out_codec_name = "?";
            const AVCodecDescriptor *desc;

            if (in_codec) {
                decoder_name  = in_codec->name;
                desc = avcodec_descriptor_get(in_codec->id);
                if (desc)
                    in_codec_name = desc->name;
                if (!strcmp(decoder_name, in_codec_name))
                    decoder_name = "native";
            }

            if (out_codec) {
                encoder_name   = out_codec->name;
                desc = avcodec_descriptor_get(out_codec->id);
                if (desc)
                    out_codec_name = desc->name;
                if (!strcmp(encoder_name, out_codec_name))
                    encoder_name = "native";
            }

            av_log(NULL, AV_LOG_INFO, " (%s (%s) -> %s (%s))",
                   in_codec_name, decoder_name,
                   out_codec_name, encoder_name);
        }
        av_log(NULL, AV_LOG_INFO, "\n");
    }

    if (ret) {
        av_log(NULL, AV_LOG_ERROR, "%s\n", error);
        return ret;
    }

    atomic_store(&transcode_init_done, 1);

    return 0;
}