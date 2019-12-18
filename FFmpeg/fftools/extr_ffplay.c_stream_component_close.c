#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int audio_stream; int video_stream; int subtitle_stream; int /*<<< orphan*/ * subtitle_st; int /*<<< orphan*/ * video_st; int /*<<< orphan*/ * audio_st; int /*<<< orphan*/  subdec; int /*<<< orphan*/  subpq; int /*<<< orphan*/  viddec; int /*<<< orphan*/  pictq; int /*<<< orphan*/  rdft_bits; int /*<<< orphan*/ * rdft; int /*<<< orphan*/  rdft_data; int /*<<< orphan*/ * audio_buf; int /*<<< orphan*/  audio_buf1_size; int /*<<< orphan*/  audio_buf1; int /*<<< orphan*/  swr_ctx; int /*<<< orphan*/  auddec; int /*<<< orphan*/  sampq; TYPE_3__* ic; } ;
typedef  TYPE_2__ VideoState ;
struct TYPE_9__ {int codec_type; } ;
struct TYPE_8__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_6__ {int /*<<< orphan*/  discard; TYPE_4__* codecpar; } ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;

/* Variables and functions */
 int /*<<< orphan*/  AVDISCARD_ALL ; 
#define  AVMEDIA_TYPE_AUDIO 130 
#define  AVMEDIA_TYPE_SUBTITLE 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  SDL_CloseAudioDevice (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_dev ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_rdft_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decoder_abort (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  decoder_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swr_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stream_component_close(VideoState *is, int stream_index)
{
    AVFormatContext *ic = is->ic;
    AVCodecParameters *codecpar;

    if (stream_index < 0 || stream_index >= ic->nb_streams)
        return;
    codecpar = ic->streams[stream_index]->codecpar;

    switch (codecpar->codec_type) {
    case AVMEDIA_TYPE_AUDIO:
        decoder_abort(&is->auddec, &is->sampq);
        SDL_CloseAudioDevice(audio_dev);
        decoder_destroy(&is->auddec);
        swr_free(&is->swr_ctx);
        av_freep(&is->audio_buf1);
        is->audio_buf1_size = 0;
        is->audio_buf = NULL;

        if (is->rdft) {
            av_rdft_end(is->rdft);
            av_freep(&is->rdft_data);
            is->rdft = NULL;
            is->rdft_bits = 0;
        }
        break;
    case AVMEDIA_TYPE_VIDEO:
        decoder_abort(&is->viddec, &is->pictq);
        decoder_destroy(&is->viddec);
        break;
    case AVMEDIA_TYPE_SUBTITLE:
        decoder_abort(&is->subdec, &is->subpq);
        decoder_destroy(&is->subdec);
        break;
    default:
        break;
    }

    ic->streams[stream_index]->discard = AVDISCARD_ALL;
    switch (codecpar->codec_type) {
    case AVMEDIA_TYPE_AUDIO:
        is->audio_st = NULL;
        is->audio_stream = -1;
        break;
    case AVMEDIA_TYPE_VIDEO:
        is->video_st = NULL;
        is->video_stream = -1;
        break;
    case AVMEDIA_TYPE_SUBTITLE:
        is->subtitle_st = NULL;
        is->subtitle_stream = -1;
        break;
    default:
        break;
    }
}