#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;

/* Type definitions */
struct TYPE_28__ {scalar_t__ key; } ;
struct TYPE_27__ {int nb_streams; TYPE_4__** streams; } ;
struct TYPE_26__ {int /*<<< orphan*/  index; TYPE_1__* codec; int /*<<< orphan*/  avg_frame_rate; int /*<<< orphan*/  time_base; TYPE_15__* codecpar; } ;
struct TYPE_25__ {int nb_streams; TYPE_5__* fmt_ctx; TYPE_2__* streams; } ;
struct TYPE_24__ {TYPE_14__* dec_ctx; TYPE_4__* st; } ;
struct TYPE_23__ {int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; } ;
struct TYPE_22__ {scalar_t__ codec_id; } ;
struct TYPE_21__ {int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; int /*<<< orphan*/  framerate; int /*<<< orphan*/  pkt_timebase; } ;
typedef  TYPE_2__ InputStream ;
typedef  TYPE_3__ InputFile ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_OPTION_NOT_FOUND ; 
 scalar_t__ AV_CODEC_ID_PROBE ; 
 int /*<<< orphan*/  AV_DICT_DONT_OVERWRITE ; 
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 int /*<<< orphan*/  AV_DICT_MATCH_CASE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 TYPE_6__* av_dict_get (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dump_format (TYPE_5__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ ***) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 TYPE_2__* av_mallocz_array (int,int) ; 
 TYPE_14__* avcodec_alloc_context3 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * avcodec_find_decoder (scalar_t__) ; 
 scalar_t__ avcodec_open2 (TYPE_14__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int avcodec_parameters_to_context (TYPE_14__*,TYPE_15__*) ; 
 TYPE_5__* avformat_alloc_context () ; 
 int avformat_find_stream_info (TYPE_5__*,int /*<<< orphan*/ **) ; 
 int avformat_open_input (TYPE_5__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * codec_opts ; 
 scalar_t__ do_show_log ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int /*<<< orphan*/ * filter_codec_opts (int /*<<< orphan*/ *,scalar_t__,TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ find_stream_info ; 
 int /*<<< orphan*/ * format_opts ; 
 int /*<<< orphan*/  iformat ; 
 int /*<<< orphan*/  print_error (char const*,int) ; 
 int /*<<< orphan*/ ** setup_find_stream_info_opts (TYPE_5__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int open_input_file(InputFile *ifile, const char *filename)
{
    int err, i;
    AVFormatContext *fmt_ctx = NULL;
    AVDictionaryEntry *t;
    int scan_all_pmts_set = 0;

    fmt_ctx = avformat_alloc_context();
    if (!fmt_ctx) {
        print_error(filename, AVERROR(ENOMEM));
        exit_program(1);
    }

    if (!av_dict_get(format_opts, "scan_all_pmts", NULL, AV_DICT_MATCH_CASE)) {
        av_dict_set(&format_opts, "scan_all_pmts", "1", AV_DICT_DONT_OVERWRITE);
        scan_all_pmts_set = 1;
    }
    if ((err = avformat_open_input(&fmt_ctx, filename,
                                   iformat, &format_opts)) < 0) {
        print_error(filename, err);
        return err;
    }
    ifile->fmt_ctx = fmt_ctx;
    if (scan_all_pmts_set)
        av_dict_set(&format_opts, "scan_all_pmts", NULL, AV_DICT_MATCH_CASE);
    if ((t = av_dict_get(format_opts, "", NULL, AV_DICT_IGNORE_SUFFIX))) {
        av_log(NULL, AV_LOG_ERROR, "Option %s not found.\n", t->key);
        return AVERROR_OPTION_NOT_FOUND;
    }

    if (find_stream_info) {
        AVDictionary **opts = setup_find_stream_info_opts(fmt_ctx, codec_opts);
        int orig_nb_streams = fmt_ctx->nb_streams;

        err = avformat_find_stream_info(fmt_ctx, opts);

        for (i = 0; i < orig_nb_streams; i++)
            av_dict_free(&opts[i]);
        av_freep(&opts);

        if (err < 0) {
            print_error(filename, err);
            return err;
        }
    }

    av_dump_format(fmt_ctx, 0, filename, 0);

    ifile->streams = av_mallocz_array(fmt_ctx->nb_streams,
                                      sizeof(*ifile->streams));
    if (!ifile->streams)
        exit(1);
    ifile->nb_streams = fmt_ctx->nb_streams;

    /* bind a decoder to each input stream */
    for (i = 0; i < fmt_ctx->nb_streams; i++) {
        InputStream *ist = &ifile->streams[i];
        AVStream *stream = fmt_ctx->streams[i];
        AVCodec *codec;

        ist->st = stream;

        if (stream->codecpar->codec_id == AV_CODEC_ID_PROBE) {
            av_log(NULL, AV_LOG_WARNING,
                   "Failed to probe codec for input stream %d\n",
                    stream->index);
            continue;
        }

        codec = avcodec_find_decoder(stream->codecpar->codec_id);
        if (!codec) {
            av_log(NULL, AV_LOG_WARNING,
                    "Unsupported codec with id %d for input stream %d\n",
                    stream->codecpar->codec_id, stream->index);
            continue;
        }
        {
            AVDictionary *opts = filter_codec_opts(codec_opts, stream->codecpar->codec_id,
                                                   fmt_ctx, stream, codec);

            ist->dec_ctx = avcodec_alloc_context3(codec);
            if (!ist->dec_ctx)
                exit(1);

            err = avcodec_parameters_to_context(ist->dec_ctx, stream->codecpar);
            if (err < 0)
                exit(1);

            if (do_show_log) {
                // For loging it is needed to disable at least frame threads as otherwise
                // the log information would need to be reordered and matches up to contexts and frames
                // That is in fact possible but not trivial
                av_dict_set(&codec_opts, "threads", "1", 0);
            }

            ist->dec_ctx->pkt_timebase = stream->time_base;
            ist->dec_ctx->framerate = stream->avg_frame_rate;
#if FF_API_LAVF_AVCTX
            ist->dec_ctx->coded_width = stream->codec->coded_width;
            ist->dec_ctx->coded_height = stream->codec->coded_height;
#endif

            if (avcodec_open2(ist->dec_ctx, codec, &opts) < 0) {
                av_log(NULL, AV_LOG_WARNING, "Could not open codec for input stream %d\n",
                       stream->index);
                exit(1);
            }

            if ((t = av_dict_get(opts, "", NULL, AV_DICT_IGNORE_SUFFIX))) {
                av_log(NULL, AV_LOG_ERROR, "Option %s for input stream %d not found\n",
                       t->key, stream->index);
                return AVERROR_OPTION_NOT_FOUND;
            }
        }
    }

    ifile->fmt_ctx = fmt_ctx;
    return 0;
}