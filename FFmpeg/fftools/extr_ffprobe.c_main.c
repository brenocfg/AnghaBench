#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  string_validation_utf8_flags; } ;
typedef  TYPE_1__ WriterContext ;
typedef  int /*<<< orphan*/  Writer ;
struct TYPE_15__ {int /*<<< orphan*/  entries_to_show; } ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_SKIP_REPEATED ; 
 int /*<<< orphan*/  AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES ; 
 int /*<<< orphan*/  CHAPTERS ; 
 int /*<<< orphan*/  CHAPTER_TAGS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ERROR ; 
 int FF_ARRAY_ELEMS (TYPE_5__*) ; 
 int /*<<< orphan*/  FORMAT ; 
 int /*<<< orphan*/  FORMAT_TAGS ; 
 int /*<<< orphan*/  FRAMES ; 
 int /*<<< orphan*/  FRAME_TAGS ; 
 int /*<<< orphan*/  LIBRARY_VERSIONS ; 
 int /*<<< orphan*/  PACKETS ; 
 int /*<<< orphan*/  PACKET_TAGS ; 
 int /*<<< orphan*/  PIXEL_FORMATS ; 
 int /*<<< orphan*/  PIXEL_FORMAT_COMPONENTS ; 
 int /*<<< orphan*/  PIXEL_FORMAT_FLAGS ; 
 int /*<<< orphan*/  PROGRAMS ; 
 int /*<<< orphan*/  PROGRAM_STREAM_DISPOSITION ; 
 int /*<<< orphan*/  PROGRAM_STREAM_TAGS ; 
 int /*<<< orphan*/  PROGRAM_TAGS ; 
 int /*<<< orphan*/  PROGRAM_VERSION ; 
 int /*<<< orphan*/  SECTION_ID_ROOT ; 
 int /*<<< orphan*/  SET_DO_SHOW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STREAMS ; 
 int /*<<< orphan*/  STREAM_DISPOSITION ; 
 int /*<<< orphan*/  STREAM_TAGS ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (scalar_t__*) ; 
 int av_hash_alloc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  av_hash_freep (int /*<<< orphan*/ *) ; 
 char* av_hash_names (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_log_set_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log_set_flags (int /*<<< orphan*/ ) ; 
 scalar_t__ av_strdup (char*) ; 
 char* av_strtok (scalar_t__,char*,char**) ; 
 int /*<<< orphan*/  avdevice_register_all () ; 
 int /*<<< orphan*/  avformat_network_deinit () ; 
 int /*<<< orphan*/  avformat_network_init () ; 
 int /*<<< orphan*/  chapter_tags ; 
 int /*<<< orphan*/  chapters ; 
 scalar_t__ do_bitexact ; 
 scalar_t__ do_show_chapters ; 
 scalar_t__ do_show_error ; 
 scalar_t__ do_show_format ; 
 scalar_t__ do_show_library_versions ; 
 scalar_t__ do_show_log ; 
 scalar_t__ do_show_packets ; 
 scalar_t__ do_show_pixel_formats ; 
 scalar_t__ do_show_program_version ; 
 scalar_t__ do_show_programs ; 
 scalar_t__ do_show_streams ; 
 int /*<<< orphan*/  error ; 
 int /*<<< orphan*/  ffprobe_cleanup ; 
 int /*<<< orphan*/  ffprobe_show_library_versions (TYPE_1__*) ; 
 int /*<<< orphan*/  ffprobe_show_pixel_formats (TYPE_1__*) ; 
 int /*<<< orphan*/  ffprobe_show_program_version (TYPE_1__*) ; 
 int /*<<< orphan*/  format ; 
 int /*<<< orphan*/  format_tags ; 
 int /*<<< orphan*/  frame_tags ; 
 int /*<<< orphan*/  frames ; 
 int /*<<< orphan*/  hash ; 
 int /*<<< orphan*/  init_dynload () ; 
 int /*<<< orphan*/  init_opts () ; 
 scalar_t__ input_filename ; 
 int /*<<< orphan*/  library_versions ; 
 int /*<<< orphan*/  log_callback ; 
 int /*<<< orphan*/  log_mutex ; 
 int /*<<< orphan*/  opt_input_file ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  packet_tags ; 
 int /*<<< orphan*/  packets ; 
 int /*<<< orphan*/  parse_loglevel (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_options (int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pixel_format_components ; 
 int /*<<< orphan*/  pixel_format_flags ; 
 int /*<<< orphan*/  pixel_formats ; 
 scalar_t__ print_format ; 
 int probe_file (TYPE_1__*,scalar_t__) ; 
 char* program_name ; 
 int /*<<< orphan*/  program_tags ; 
 int /*<<< orphan*/  program_version ; 
 int /*<<< orphan*/  programs ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ read_intervals ; 
 int /*<<< orphan*/  real_options ; 
 int /*<<< orphan*/  register_exit (int /*<<< orphan*/ ) ; 
 TYPE_5__* sections ; 
 int /*<<< orphan*/  show_banner (int,char**,int /*<<< orphan*/ ) ; 
 char* show_data_hash ; 
 int /*<<< orphan*/  show_error (TYPE_1__*,int) ; 
 int /*<<< orphan*/  show_usage () ; 
 int /*<<< orphan*/  stream_disposition ; 
 int /*<<< orphan*/  stream_tags ; 
 int /*<<< orphan*/  streams ; 
 int /*<<< orphan*/  uninit_opts () ; 
 int /*<<< orphan*/  writer_close (TYPE_1__**) ; 
 int /*<<< orphan*/ * writer_get_by_name (char*) ; 
 int writer_open (TYPE_1__**,int /*<<< orphan*/  const*,char*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  writer_print_section_footer (TYPE_1__*) ; 
 int /*<<< orphan*/  writer_print_section_header (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writer_register_all () ; 
 int /*<<< orphan*/  const xml_writer ; 

int main(int argc, char **argv)
{
    const Writer *w;
    WriterContext *wctx;
    char *buf;
    char *w_name = NULL, *w_args = NULL;
    int ret, i;

    init_dynload();

#if HAVE_THREADS
    ret = pthread_mutex_init(&log_mutex, NULL);
    if (ret != 0) {
        goto end;
    }
#endif
    av_log_set_flags(AV_LOG_SKIP_REPEATED);
    register_exit(ffprobe_cleanup);

    options = real_options;
    parse_loglevel(argc, argv, options);
    avformat_network_init();
    init_opts();
#if CONFIG_AVDEVICE
    avdevice_register_all();
#endif

    show_banner(argc, argv, options);
    parse_options(NULL, argc, argv, options, opt_input_file);

    if (do_show_log)
        av_log_set_callback(log_callback);

    /* mark things to show, based on -show_entries */
    SET_DO_SHOW(CHAPTERS, chapters);
    SET_DO_SHOW(ERROR, error);
    SET_DO_SHOW(FORMAT, format);
    SET_DO_SHOW(FRAMES, frames);
    SET_DO_SHOW(LIBRARY_VERSIONS, library_versions);
    SET_DO_SHOW(PACKETS, packets);
    SET_DO_SHOW(PIXEL_FORMATS, pixel_formats);
    SET_DO_SHOW(PIXEL_FORMAT_FLAGS, pixel_format_flags);
    SET_DO_SHOW(PIXEL_FORMAT_COMPONENTS, pixel_format_components);
    SET_DO_SHOW(PROGRAM_VERSION, program_version);
    SET_DO_SHOW(PROGRAMS, programs);
    SET_DO_SHOW(STREAMS, streams);
    SET_DO_SHOW(STREAM_DISPOSITION, stream_disposition);
    SET_DO_SHOW(PROGRAM_STREAM_DISPOSITION, stream_disposition);

    SET_DO_SHOW(CHAPTER_TAGS, chapter_tags);
    SET_DO_SHOW(FORMAT_TAGS, format_tags);
    SET_DO_SHOW(FRAME_TAGS, frame_tags);
    SET_DO_SHOW(PROGRAM_TAGS, program_tags);
    SET_DO_SHOW(STREAM_TAGS, stream_tags);
    SET_DO_SHOW(PROGRAM_STREAM_TAGS, stream_tags);
    SET_DO_SHOW(PACKET_TAGS, packet_tags);

    if (do_bitexact && (do_show_program_version || do_show_library_versions)) {
        av_log(NULL, AV_LOG_ERROR,
               "-bitexact and -show_program_version or -show_library_versions "
               "options are incompatible\n");
        ret = AVERROR(EINVAL);
        goto end;
    }

    writer_register_all();

    if (!print_format)
        print_format = av_strdup("default");
    if (!print_format) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    w_name = av_strtok(print_format, "=", &buf);
    if (!w_name) {
        av_log(NULL, AV_LOG_ERROR,
               "No name specified for the output format\n");
        ret = AVERROR(EINVAL);
        goto end;
    }
    w_args = buf;

    if (show_data_hash) {
        if ((ret = av_hash_alloc(&hash, show_data_hash)) < 0) {
            if (ret == AVERROR(EINVAL)) {
                const char *n;
                av_log(NULL, AV_LOG_ERROR,
                       "Unknown hash algorithm '%s'\nKnown algorithms:",
                       show_data_hash);
                for (i = 0; (n = av_hash_names(i)); i++)
                    av_log(NULL, AV_LOG_ERROR, " %s", n);
                av_log(NULL, AV_LOG_ERROR, "\n");
            }
            goto end;
        }
    }

    w = writer_get_by_name(w_name);
    if (!w) {
        av_log(NULL, AV_LOG_ERROR, "Unknown output format with name '%s'\n", w_name);
        ret = AVERROR(EINVAL);
        goto end;
    }

    if ((ret = writer_open(&wctx, w, w_args,
                           sections, FF_ARRAY_ELEMS(sections))) >= 0) {
        if (w == &xml_writer)
            wctx->string_validation_utf8_flags |= AV_UTF8_FLAG_EXCLUDE_XML_INVALID_CONTROL_CODES;

        writer_print_section_header(wctx, SECTION_ID_ROOT);

        if (do_show_program_version)
            ffprobe_show_program_version(wctx);
        if (do_show_library_versions)
            ffprobe_show_library_versions(wctx);
        if (do_show_pixel_formats)
            ffprobe_show_pixel_formats(wctx);

        if (!input_filename &&
            ((do_show_format || do_show_programs || do_show_streams || do_show_chapters || do_show_packets || do_show_error) ||
             (!do_show_program_version && !do_show_library_versions && !do_show_pixel_formats))) {
            show_usage();
            av_log(NULL, AV_LOG_ERROR, "You have to specify one input file.\n");
            av_log(NULL, AV_LOG_ERROR, "Use -h to get full help or, even better, run 'man %s'.\n", program_name);
            ret = AVERROR(EINVAL);
        } else if (input_filename) {
            ret = probe_file(wctx, input_filename);
            if (ret < 0 && do_show_error)
                show_error(wctx, ret);
        }

        writer_print_section_footer(wctx);
        writer_close(&wctx);
    }

end:
    av_freep(&print_format);
    av_freep(&read_intervals);
    av_hash_freep(&hash);

    uninit_opts();
    for (i = 0; i < FF_ARRAY_ELEMS(sections); i++)
        av_dict_free(&(sections[i].entries_to_show));

    avformat_network_deinit();

    return ret < 0;
}