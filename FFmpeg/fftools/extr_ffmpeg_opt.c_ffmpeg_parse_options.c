#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  octx ;
typedef  int /*<<< orphan*/  error ;
struct TYPE_5__ {int /*<<< orphan*/ * groups; int /*<<< orphan*/  global_opts; } ;
typedef  TYPE_1__ OptionParseContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  FF_ARRAY_ELEMS (int /*<<< orphan*/ ) ; 
 size_t GROUP_INFILE ; 
 size_t GROUP_OUTFILE ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strerror (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  check_filter_outputs () ; 
 int /*<<< orphan*/  groups ; 
 int init_complex_filters () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int open_files (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_input_file ; 
 int /*<<< orphan*/  open_output_file ; 
 int /*<<< orphan*/  options ; 
 int parse_optgroup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int split_commandline (TYPE_1__*,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  term_init () ; 
 int /*<<< orphan*/  uninit_parse_context (TYPE_1__*) ; 

int ffmpeg_parse_options(int argc, char **argv)
{
    OptionParseContext octx;
    uint8_t error[128];
    int ret;

    memset(&octx, 0, sizeof(octx));

    /* split the commandline into an internal representation */
    ret = split_commandline(&octx, argc, argv, options, groups,
                            FF_ARRAY_ELEMS(groups));
    if (ret < 0) {
        av_log(NULL, AV_LOG_FATAL, "Error splitting the argument list: ");
        goto fail;
    }

    /* apply global options */
    ret = parse_optgroup(NULL, &octx.global_opts);
    if (ret < 0) {
        av_log(NULL, AV_LOG_FATAL, "Error parsing global options: ");
        goto fail;
    }

    /* configure terminal and setup signal handlers */
    term_init();

    /* open input files */
    ret = open_files(&octx.groups[GROUP_INFILE], "input", open_input_file);
    if (ret < 0) {
        av_log(NULL, AV_LOG_FATAL, "Error opening input files: ");
        goto fail;
    }

    /* create the complex filtergraphs */
    ret = init_complex_filters();
    if (ret < 0) {
        av_log(NULL, AV_LOG_FATAL, "Error initializing complex filters.\n");
        goto fail;
    }

    /* open output files */
    ret = open_files(&octx.groups[GROUP_OUTFILE], "output", open_output_file);
    if (ret < 0) {
        av_log(NULL, AV_LOG_FATAL, "Error opening output files: ");
        goto fail;
    }

    check_filter_outputs();

fail:
    uninit_parse_context(&octx);
    if (ret < 0) {
        av_strerror(ret, error, sizeof(error));
        av_log(NULL, AV_LOG_FATAL, "%s\n", error);
    }
    return ret;
}