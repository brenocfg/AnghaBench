#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_11__ {int /*<<< orphan*/ * priv_data; } ;
struct TYPE_10__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  TSContext ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  truespeech_apply_twopoint_filter (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  truespeech_correlate_filter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truespeech_filters_merge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truespeech_place_pulses (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  truespeech_read_frame (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  truespeech_save_prevvec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truespeech_synth (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  truespeech_update_filters (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int truespeech_decode_frame(AVCodecContext *avctx, void *data,
                                   int *got_frame_ptr, AVPacket *avpkt)
{
    AVFrame *frame     = data;
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    TSContext *c = avctx->priv_data;

    int i, j;
    int16_t *samples;
    int iterations, ret;

    iterations = buf_size / 32;

    if (!iterations) {
        av_log(avctx, AV_LOG_ERROR,
               "Too small input buffer (%d bytes), need at least 32 bytes\n", buf_size);
        return -1;
    }

    /* get output buffer */
    frame->nb_samples = iterations * 240;
    if ((ret = ff_get_buffer(avctx, frame, 0)) < 0)
        return ret;
    samples = (int16_t *)frame->data[0];

    memset(samples, 0, iterations * 240 * sizeof(*samples));

    for(j = 0; j < iterations; j++) {
        truespeech_read_frame(c, buf);
        buf += 32;

        truespeech_correlate_filter(c);
        truespeech_filters_merge(c);

        for(i = 0; i < 4; i++) {
            truespeech_apply_twopoint_filter(c, i);
            truespeech_place_pulses  (c, samples, i);
            truespeech_update_filters(c, samples, i);
            truespeech_synth         (c, samples, i);
            samples += 60;
        }

        truespeech_save_prevvec(c);
    }

    *got_frame_ptr = 1;

    return buf_size;
}