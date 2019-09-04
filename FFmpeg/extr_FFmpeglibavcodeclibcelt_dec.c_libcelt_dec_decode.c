#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct libcelt_context {int discard; int /*<<< orphan*/  dec; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_10__ {int frame_size; int channels; struct libcelt_context* priv_data; } ;
struct TYPE_9__ {int nb_samples; scalar_t__* data; } ;
struct TYPE_8__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ AVPacket ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int celt_decode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int ff_celt_error_to_averror (int) ; 
 int ff_get_buffer (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int libcelt_dec_decode(AVCodecContext *c, void *data,
                              int *got_frame_ptr, AVPacket *pkt)
{
    struct libcelt_context *celt = c->priv_data;
    AVFrame *frame = data;
    int err;
    int16_t *pcm;

    frame->nb_samples = c->frame_size;
    if ((err = ff_get_buffer(c, frame, 0)) < 0)
        return err;
    pcm = (int16_t *)frame->data[0];
    err = celt_decode(celt->dec, pkt->data, pkt->size, pcm, c->frame_size);
    if (err < 0)
        return ff_celt_error_to_averror(err);
    if (celt->discard) {
        frame->nb_samples -= celt->discard;
        memmove(pcm, pcm + celt->discard * c->channels,
                frame->nb_samples * c->channels * sizeof(int16_t));
        celt->discard = 0;
    }
    *got_frame_ptr = 1;
    return pkt->size;
}