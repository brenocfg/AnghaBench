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
struct TYPE_5__ {int abort_request; scalar_t__ audio_stream; scalar_t__ video_stream; scalar_t__ subtitle_stream; scalar_t__ sub_texture; scalar_t__ vid_texture; scalar_t__ vis_texture; struct TYPE_5__* filename; int /*<<< orphan*/  sub_convert_ctx; int /*<<< orphan*/  img_convert_ctx; int /*<<< orphan*/  continue_read_thread; int /*<<< orphan*/  subpq; int /*<<< orphan*/  sampq; int /*<<< orphan*/  pictq; int /*<<< orphan*/  subtitleq; int /*<<< orphan*/  audioq; int /*<<< orphan*/  videoq; int /*<<< orphan*/  ic; int /*<<< orphan*/  read_tid; } ;
typedef  TYPE_1__ VideoState ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_DestroyCond (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_DestroyTexture (scalar_t__) ; 
 int /*<<< orphan*/  SDL_WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int /*<<< orphan*/  avformat_close_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  frame_queue_destory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  packet_queue_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_component_close (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  sws_freeContext (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stream_close(VideoState *is)
{
    /* XXX: use a special url_shutdown call to abort parse cleanly */
    is->abort_request = 1;
    SDL_WaitThread(is->read_tid, NULL);

    /* close each stream */
    if (is->audio_stream >= 0)
        stream_component_close(is, is->audio_stream);
    if (is->video_stream >= 0)
        stream_component_close(is, is->video_stream);
    if (is->subtitle_stream >= 0)
        stream_component_close(is, is->subtitle_stream);

    avformat_close_input(&is->ic);

    packet_queue_destroy(&is->videoq);
    packet_queue_destroy(&is->audioq);
    packet_queue_destroy(&is->subtitleq);

    /* free all pictures */
    frame_queue_destory(&is->pictq);
    frame_queue_destory(&is->sampq);
    frame_queue_destory(&is->subpq);
    SDL_DestroyCond(is->continue_read_thread);
    sws_freeContext(is->img_convert_ctx);
    sws_freeContext(is->sub_convert_ctx);
    av_free(is->filename);
    if (is->vis_texture)
        SDL_DestroyTexture(is->vis_texture);
    if (is->vid_texture)
        SDL_DestroyTexture(is->vid_texture);
    if (is->sub_texture)
        SDL_DestroyTexture(is->sub_texture);
    av_free(is);
}