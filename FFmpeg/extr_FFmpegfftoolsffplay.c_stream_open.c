#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  serial; } ;
struct TYPE_10__ {int /*<<< orphan*/  serial; } ;
struct TYPE_9__ {int audio_clock_serial; int audio_volume; int /*<<< orphan*/  read_tid; int /*<<< orphan*/  av_sync_type; scalar_t__ muted; TYPE_5__ extclk; TYPE_4__ audioq; TYPE_5__ audclk; TYPE_4__ videoq; TYPE_5__ vidclk; int /*<<< orphan*/  continue_read_thread; TYPE_4__ subtitleq; int /*<<< orphan*/  sampq; int /*<<< orphan*/  subpq; int /*<<< orphan*/  pictq; scalar_t__ xleft; scalar_t__ ytop; int /*<<< orphan*/ * iformat; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ VideoState ;
typedef  int /*<<< orphan*/  AVInputFormat ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_FATAL ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  SAMPLE_QUEUE_SIZE ; 
 int /*<<< orphan*/  SDL_CreateCond () ; 
 int /*<<< orphan*/  SDL_CreateThread (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int SDL_GetError () ; 
 int SDL_MIX_MAXVOLUME ; 
 int /*<<< orphan*/  SUBPICTURE_QUEUE_SIZE ; 
 int /*<<< orphan*/  VIDEO_PICTURE_QUEUE_SIZE ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__* av_mallocz (int) ; 
 int /*<<< orphan*/  av_strdup (char const*) ; 
 int /*<<< orphan*/  av_sync_type ; 
 scalar_t__ frame_queue_init (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_clock (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ packet_queue_init (TYPE_4__*) ; 
 int /*<<< orphan*/  read_thread ; 
 int startup_volume ; 
 int /*<<< orphan*/  stream_close (TYPE_1__*) ; 

__attribute__((used)) static VideoState *stream_open(const char *filename, AVInputFormat *iformat)
{
    VideoState *is;

    is = av_mallocz(sizeof(VideoState));
    if (!is)
        return NULL;
    is->filename = av_strdup(filename);
    if (!is->filename)
        goto fail;
    is->iformat = iformat;
    is->ytop    = 0;
    is->xleft   = 0;

    /* start video display */
    if (frame_queue_init(&is->pictq, &is->videoq, VIDEO_PICTURE_QUEUE_SIZE, 1) < 0)
        goto fail;
    if (frame_queue_init(&is->subpq, &is->subtitleq, SUBPICTURE_QUEUE_SIZE, 0) < 0)
        goto fail;
    if (frame_queue_init(&is->sampq, &is->audioq, SAMPLE_QUEUE_SIZE, 1) < 0)
        goto fail;

    if (packet_queue_init(&is->videoq) < 0 ||
        packet_queue_init(&is->audioq) < 0 ||
        packet_queue_init(&is->subtitleq) < 0)
        goto fail;

    if (!(is->continue_read_thread = SDL_CreateCond())) {
        av_log(NULL, AV_LOG_FATAL, "SDL_CreateCond(): %s\n", SDL_GetError());
        goto fail;
    }

    init_clock(&is->vidclk, &is->videoq.serial);
    init_clock(&is->audclk, &is->audioq.serial);
    init_clock(&is->extclk, &is->extclk.serial);
    is->audio_clock_serial = -1;
    if (startup_volume < 0)
        av_log(NULL, AV_LOG_WARNING, "-volume=%d < 0, setting to 0\n", startup_volume);
    if (startup_volume > 100)
        av_log(NULL, AV_LOG_WARNING, "-volume=%d > 100, setting to 100\n", startup_volume);
    startup_volume = av_clip(startup_volume, 0, 100);
    startup_volume = av_clip(SDL_MIX_MAXVOLUME * startup_volume / 100, 0, SDL_MIX_MAXVOLUME);
    is->audio_volume = startup_volume;
    is->muted = 0;
    is->av_sync_type = av_sync_type;
    is->read_tid     = SDL_CreateThread(read_thread, "read_thread", is);
    if (!is->read_tid) {
        av_log(NULL, AV_LOG_FATAL, "SDL_CreateThread(): %s\n", SDL_GetError());
fail:
        stream_close(is);
        return NULL;
    }
    return is;
}