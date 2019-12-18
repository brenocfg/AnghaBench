#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int swf_frame_number; int /*<<< orphan*/  video_par; int /*<<< orphan*/  sound_samples; int /*<<< orphan*/  audio_fifo; } ;
typedef  TYPE_1__ SWFContext ;
typedef  TYPE_2__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVCodecParameters ;

/* Variables and functions */
 scalar_t__ AUDIO_FIFO_SIZE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_fifo_generic_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ av_fifo_size (int /*<<< orphan*/ ) ; 
 scalar_t__ av_get_audio_frame_duration2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  swf_write_video (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int swf_write_audio(AVFormatContext *s,
                           AVCodecParameters *par, uint8_t *buf, int size)
{
    SWFContext *swf = s->priv_data;

    /* Flash Player limit */
    if (swf->swf_frame_number == 16000)
        av_log(s, AV_LOG_INFO, "warning: Flash Player limit of 16000 frames reached\n");

    if (av_fifo_size(swf->audio_fifo) + size > AUDIO_FIFO_SIZE) {
        av_log(s, AV_LOG_ERROR, "audio fifo too small to mux audio essence\n");
        return -1;
    }

    av_fifo_generic_write(swf->audio_fifo, buf, size, NULL);
    swf->sound_samples += av_get_audio_frame_duration2(par, size);

    /* if audio only stream make sure we add swf frames */
    if (!swf->video_par)
        swf_write_video(s, par, 0, 0);

    return 0;
}