#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_16__ {int /*<<< orphan*/  eof_reached; } ;
struct TYPE_15__ {int /*<<< orphan*/  header_written; TYPE_4__* ctx; } ;
struct TYPE_14__ {int /*<<< orphan*/  url; } ;
struct TYPE_13__ {size_t file_index; int /*<<< orphan*/  dec_ctx; int /*<<< orphan*/  (* hwaccel_uninit ) (int /*<<< orphan*/ ) ;scalar_t__ decoding_needed; } ;
struct TYPE_12__ {int /*<<< orphan*/  resample_opts; int /*<<< orphan*/  swr_opts; int /*<<< orphan*/  sws_dict; int /*<<< orphan*/  encoder_opts; int /*<<< orphan*/  disposition; int /*<<< orphan*/  apad; int /*<<< orphan*/  forced_kf_pts; int /*<<< orphan*/ * logfile; scalar_t__ packets_written; TYPE_1__* enc_ctx; scalar_t__ encoding_needed; } ;
struct TYPE_11__ {int /*<<< orphan*/  stats_in; } ;
typedef  TYPE_2__ OutputStream ;
typedef  TYPE_3__ InputStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int ABORT_ON_FLAG_EMPTY_OUTPUT ; 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int abort_on_flags ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 scalar_t__ av_gettime_relative () ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int av_write_trailer (TYPE_4__*) ; 
 int /*<<< orphan*/  avcodec_close (int /*<<< orphan*/ ) ; 
 scalar_t__ check_keyboard_interaction (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ exit_on_error ; 
 int /*<<< orphan*/  exit_program (int) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_encoders () ; 
 int /*<<< orphan*/  free_input_threads () ; 
 int /*<<< orphan*/  hw_device_ctx ; 
 int /*<<< orphan*/  hw_device_free_all () ; 
 int init_input_threads () ; 
 TYPE_9__** input_files ; 
 TYPE_3__** input_streams ; 
 int nb_input_streams ; 
 int nb_output_files ; 
 int nb_output_streams ; 
 int /*<<< orphan*/  need_output () ; 
 TYPE_7__** output_files ; 
 TYPE_2__** output_streams ; 
 int /*<<< orphan*/  print_report (int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  process_input_packet (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  received_sigterm ; 
 scalar_t__ stdin_interaction ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  term_exit () ; 
 int transcode_init () ; 
 int transcode_step () ; 

__attribute__((used)) static int transcode(void)
{
    int ret, i;
    AVFormatContext *os;
    OutputStream *ost;
    InputStream *ist;
    int64_t timer_start;
    int64_t total_packets_written = 0;

    ret = transcode_init();
    if (ret < 0)
        goto fail;

    if (stdin_interaction) {
        av_log(NULL, AV_LOG_INFO, "Press [q] to stop, [?] for help\n");
    }

    timer_start = av_gettime_relative();

#if HAVE_THREADS
    if ((ret = init_input_threads()) < 0)
        goto fail;
#endif

    while (!received_sigterm) {
        int64_t cur_time= av_gettime_relative();

        /* if 'q' pressed, exits */
        if (stdin_interaction)
            if (check_keyboard_interaction(cur_time) < 0)
                break;

        /* check if there's any stream where output is still needed */
        if (!need_output()) {
            av_log(NULL, AV_LOG_VERBOSE, "No more output streams to write to, finishing.\n");
            break;
        }

        ret = transcode_step();
        if (ret < 0 && ret != AVERROR_EOF) {
            av_log(NULL, AV_LOG_ERROR, "Error while filtering: %s\n", av_err2str(ret));
            break;
        }

        /* dump report by using the output first video and audio streams */
        print_report(0, timer_start, cur_time);
    }
#if HAVE_THREADS
    free_input_threads();
#endif

    /* at the end of stream, we must flush the decoder buffers */
    for (i = 0; i < nb_input_streams; i++) {
        ist = input_streams[i];
        if (!input_files[ist->file_index]->eof_reached) {
            process_input_packet(ist, NULL, 0);
        }
    }
    flush_encoders();

    term_exit();

    /* write the trailer if needed and close file */
    for (i = 0; i < nb_output_files; i++) {
        os = output_files[i]->ctx;
        if (!output_files[i]->header_written) {
            av_log(NULL, AV_LOG_ERROR,
                   "Nothing was written into output file %d (%s), because "
                   "at least one of its streams received no packets.\n",
                   i, os->url);
            continue;
        }
        if ((ret = av_write_trailer(os)) < 0) {
            av_log(NULL, AV_LOG_ERROR, "Error writing trailer of %s: %s\n", os->url, av_err2str(ret));
            if (exit_on_error)
                exit_program(1);
        }
    }

    /* dump report by using the first video and audio streams */
    print_report(1, timer_start, av_gettime_relative());

    /* close each encoder */
    for (i = 0; i < nb_output_streams; i++) {
        ost = output_streams[i];
        if (ost->encoding_needed) {
            av_freep(&ost->enc_ctx->stats_in);
        }
        total_packets_written += ost->packets_written;
    }

    if (!total_packets_written && (abort_on_flags & ABORT_ON_FLAG_EMPTY_OUTPUT)) {
        av_log(NULL, AV_LOG_FATAL, "Empty output\n");
        exit_program(1);
    }

    /* close each decoder */
    for (i = 0; i < nb_input_streams; i++) {
        ist = input_streams[i];
        if (ist->decoding_needed) {
            avcodec_close(ist->dec_ctx);
            if (ist->hwaccel_uninit)
                ist->hwaccel_uninit(ist->dec_ctx);
        }
    }

    av_buffer_unref(&hw_device_ctx);
    hw_device_free_all();

    /* finished ! */
    ret = 0;

 fail:
#if HAVE_THREADS
    free_input_threads();
#endif

    if (output_streams) {
        for (i = 0; i < nb_output_streams; i++) {
            ost = output_streams[i];
            if (ost) {
                if (ost->logfile) {
                    if (fclose(ost->logfile))
                        av_log(NULL, AV_LOG_ERROR,
                               "Error closing logfile, loss of information possible: %s\n",
                               av_err2str(AVERROR(errno)));
                    ost->logfile = NULL;
                }
                av_freep(&ost->forced_kf_pts);
                av_freep(&ost->apad);
                av_freep(&ost->disposition);
                av_dict_free(&ost->encoder_opts);
                av_dict_free(&ost->sws_dict);
                av_dict_free(&ost->swr_opts);
                av_dict_free(&ost->resample_opts);
            }
        }
    }
    return ret;
}