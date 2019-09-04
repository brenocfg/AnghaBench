#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  VideoState ;
struct TYPE_6__ {int /*<<< orphan*/ * data; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_texture_formats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  AV_LOG_SKIP_REPEATED ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ SDL_CreateRenderer (scalar_t__,int,int) ; 
 scalar_t__ SDL_CreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_EventState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_GetRendererInfo (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_HINT_RENDER_SCALE_QUALITY ; 
 int /*<<< orphan*/  SDL_IGNORE ; 
 int SDL_INIT_AUDIO ; 
 int SDL_INIT_TIMER ; 
 int SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int) ; 
 int SDL_RENDERER_ACCELERATED ; 
 int SDL_RENDERER_PRESENTVSYNC ; 
 int /*<<< orphan*/  SDL_SYSWMEVENT ; 
 int /*<<< orphan*/  SDL_SetHint (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SDL_USEREVENT ; 
 int /*<<< orphan*/  SDL_WINDOWPOS_UNDEFINED ; 
 int SDL_WINDOW_BORDERLESS ; 
 int SDL_WINDOW_HIDDEN ; 
 int SDL_WINDOW_RESIZABLE ; 
 int /*<<< orphan*/  SDL_getenv (char*) ; 
 int /*<<< orphan*/  SDL_setenv (char*,char*,int) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ audio_disable ; 
 int /*<<< orphan*/  av_init_packet (TYPE_2__*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_log_set_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avformat_network_init () ; 
 scalar_t__ borderless ; 
 int /*<<< orphan*/  default_height ; 
 int /*<<< orphan*/  default_width ; 
 scalar_t__ display_disable ; 
 int /*<<< orphan*/  do_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_loop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  file_iformat ; 
 TYPE_2__ flush_pkt ; 
 int /*<<< orphan*/  init_dynload () ; 
 int /*<<< orphan*/  init_opts () ; 
 int /*<<< orphan*/  input_filename ; 
 int /*<<< orphan*/  opt_input_file ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  parse_loglevel (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_options (int /*<<< orphan*/ *,int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_name ; 
 scalar_t__ renderer ; 
 TYPE_1__ renderer_info ; 
 int /*<<< orphan*/  show_banner (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_usage () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/ * stream_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int video_disable ; 
 scalar_t__ window ; 

int main(int argc, char **argv)
{
    int flags;
    VideoState *is;

    init_dynload();

    av_log_set_flags(AV_LOG_SKIP_REPEATED);
    parse_loglevel(argc, argv, options);

    /* register all codecs, demux and protocols */
#if CONFIG_AVDEVICE
    avdevice_register_all();
#endif
    avformat_network_init();

    init_opts();

    signal(SIGINT , sigterm_handler); /* Interrupt (ANSI).    */
    signal(SIGTERM, sigterm_handler); /* Termination (ANSI).  */

    show_banner(argc, argv, options);

    parse_options(NULL, argc, argv, options, opt_input_file);

    if (!input_filename) {
        show_usage();
        av_log(NULL, AV_LOG_FATAL, "An input file must be specified\n");
        av_log(NULL, AV_LOG_FATAL,
               "Use -h to get full help or, even better, run 'man %s'\n", program_name);
        exit(1);
    }

    if (display_disable) {
        video_disable = 1;
    }
    flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;
    if (audio_disable)
        flags &= ~SDL_INIT_AUDIO;
    else {
        /* Try to work around an occasional ALSA buffer underflow issue when the
         * period size is NPOT due to ALSA resampling by forcing the buffer size. */
        if (!SDL_getenv("SDL_AUDIO_ALSA_SET_BUFFER_SIZE"))
            SDL_setenv("SDL_AUDIO_ALSA_SET_BUFFER_SIZE","1", 1);
    }
    if (display_disable)
        flags &= ~SDL_INIT_VIDEO;
    if (SDL_Init (flags)) {
        av_log(NULL, AV_LOG_FATAL, "Could not initialize SDL - %s\n", SDL_GetError());
        av_log(NULL, AV_LOG_FATAL, "(Did you set the DISPLAY variable?)\n");
        exit(1);
    }

    SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
    SDL_EventState(SDL_USEREVENT, SDL_IGNORE);

    av_init_packet(&flush_pkt);
    flush_pkt.data = (uint8_t *)&flush_pkt;

    if (!display_disable) {
        int flags = SDL_WINDOW_HIDDEN;
        if (borderless)
            flags |= SDL_WINDOW_BORDERLESS;
        else
            flags |= SDL_WINDOW_RESIZABLE;
        window = SDL_CreateWindow(program_name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, default_width, default_height, flags);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        if (window) {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (!renderer) {
                av_log(NULL, AV_LOG_WARNING, "Failed to initialize a hardware accelerated renderer: %s\n", SDL_GetError());
                renderer = SDL_CreateRenderer(window, -1, 0);
            }
            if (renderer) {
                if (!SDL_GetRendererInfo(renderer, &renderer_info))
                    av_log(NULL, AV_LOG_VERBOSE, "Initialized %s renderer.\n", renderer_info.name);
            }
        }
        if (!window || !renderer || !renderer_info.num_texture_formats) {
            av_log(NULL, AV_LOG_FATAL, "Failed to create window or renderer: %s", SDL_GetError());
            do_exit(NULL);
        }
    }

    is = stream_open(input_filename, file_iformat);
    if (!is) {
        av_log(NULL, AV_LOG_FATAL, "Failed to initialize VideoState!\n");
        do_exit(NULL);
    }

    event_loop(is);

    /* never returns */

    return 0;
}