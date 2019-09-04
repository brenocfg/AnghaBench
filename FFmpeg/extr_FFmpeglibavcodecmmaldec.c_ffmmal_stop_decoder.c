#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* priv_data; } ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  ref; struct TYPE_9__* next; } ;
struct TYPE_8__ {scalar_t__ extradata_sent; scalar_t__ packets_sent; scalar_t__ eos_sent; scalar_t__ eos_received; scalar_t__ frames_output; int /*<<< orphan*/  packets_buffered; int /*<<< orphan*/ * waiting_buffers_tail; TYPE_3__* waiting_buffers; int /*<<< orphan*/  queue_decoded_frames; TYPE_1__* decoder; } ;
struct TYPE_7__ {int /*<<< orphan*/  control; int /*<<< orphan*/ * output; int /*<<< orphan*/ * input; } ;
typedef  TYPE_1__ MMAL_COMPONENT_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;
typedef  TYPE_2__ MMALDecodeContext ;
typedef  TYPE_3__ FFBufferEntry ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int MMAL_BUFFER_HEADER_FLAG_FRAME_END ; 
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_3__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmal_port_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_port_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmal_queue_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ffmmal_stop_decoder(AVCodecContext *avctx)
{
    MMALDecodeContext *ctx = avctx->priv_data;
    MMAL_COMPONENT_T *decoder = ctx->decoder;
    MMAL_BUFFER_HEADER_T *buffer;

    mmal_port_disable(decoder->input[0]);
    mmal_port_disable(decoder->output[0]);
    mmal_port_disable(decoder->control);

    mmal_port_flush(decoder->input[0]);
    mmal_port_flush(decoder->output[0]);
    mmal_port_flush(decoder->control);

    while ((buffer = mmal_queue_get(ctx->queue_decoded_frames)))
        mmal_buffer_header_release(buffer);

    while (ctx->waiting_buffers) {
        FFBufferEntry *buffer = ctx->waiting_buffers;

        ctx->waiting_buffers = buffer->next;

        if (buffer->flags & MMAL_BUFFER_HEADER_FLAG_FRAME_END)
            atomic_fetch_add(&ctx->packets_buffered, -1);

        av_buffer_unref(&buffer->ref);
        av_free(buffer);
    }
    ctx->waiting_buffers_tail = NULL;

    av_assert0(atomic_load(&ctx->packets_buffered) == 0);

    ctx->frames_output = ctx->eos_received = ctx->eos_sent = ctx->packets_sent = ctx->extradata_sent = 0;
}