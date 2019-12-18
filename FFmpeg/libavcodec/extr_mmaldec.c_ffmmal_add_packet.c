#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_21__ {int size; int /*<<< orphan*/ * data; } ;
struct TYPE_20__ {TYPE_3__* priv_data; } ;
struct TYPE_19__ {int size; scalar_t__ pts; scalar_t__ dts; int /*<<< orphan*/ * data; TYPE_7__* buf; } ;
struct TYPE_18__ {struct TYPE_18__* next; void* ref; int /*<<< orphan*/  flags; scalar_t__ length; void* dts; void* pts; int /*<<< orphan*/ * data; } ;
struct TYPE_17__ {int eos_sent; int eos_received; TYPE_4__* waiting_buffers_tail; TYPE_4__* waiting_buffers; int /*<<< orphan*/  packets_buffered; TYPE_2__* decoder; int /*<<< orphan*/  packets_sent; } ;
struct TYPE_16__ {TYPE_1__** input; } ;
struct TYPE_15__ {int /*<<< orphan*/  buffer_size; } ;
typedef  TYPE_3__ MMALDecodeContext ;
typedef  TYPE_4__ FFBufferEntry ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVCodecContext ;
typedef  TYPE_7__ AVBufferRef ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FFMIN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_CONFIG ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_EOS ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_FRAME_END ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_FRAME_START ; 
 void* MMAL_TIME_UNKNOWN ; 
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 TYPE_7__* av_buffer_alloc (int) ; 
 void* av_buffer_ref (TYPE_7__*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_7__**) ; 
 int /*<<< orphan*/  av_free (TYPE_4__*) ; 
 TYPE_4__* av_mallocz (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ffmmal_add_packet(AVCodecContext *avctx, AVPacket *avpkt,
                             int is_extradata)
{
    MMALDecodeContext *ctx = avctx->priv_data;
    AVBufferRef *buf = NULL;
    int size = 0;
    uint8_t *data = (uint8_t *)"";
    uint8_t *start;
    int ret = 0;

    if (avpkt->size) {
        if (avpkt->buf) {
            buf = av_buffer_ref(avpkt->buf);
            size = avpkt->size;
            data = avpkt->data;
        } else {
            buf = av_buffer_alloc(avpkt->size);
            if (buf) {
                memcpy(buf->data, avpkt->data, avpkt->size);
                size = buf->size;
                data = buf->data;
            }
        }
        if (!buf) {
            ret = AVERROR(ENOMEM);
            goto done;
        }
        if (!is_extradata)
            ctx->packets_sent++;
    } else {
        if (ctx->eos_sent)
            goto done;
        if (!ctx->packets_sent) {
            // Short-cut the flush logic to avoid upsetting MMAL.
            ctx->eos_sent = 1;
            ctx->eos_received = 1;
            goto done;
        }
    }

    start = data;

    do {
        FFBufferEntry *buffer = av_mallocz(sizeof(*buffer));
        if (!buffer) {
            ret = AVERROR(ENOMEM);
            goto done;
        }

        buffer->data = data;
        buffer->length = FFMIN(size, ctx->decoder->input[0]->buffer_size);

        if (is_extradata)
            buffer->flags |= MMAL_BUFFER_HEADER_FLAG_CONFIG;

        if (data == start)
            buffer->flags |= MMAL_BUFFER_HEADER_FLAG_FRAME_START;

        data += buffer->length;
        size -= buffer->length;

        buffer->pts = avpkt->pts == AV_NOPTS_VALUE ? MMAL_TIME_UNKNOWN : avpkt->pts;
        buffer->dts = avpkt->dts == AV_NOPTS_VALUE ? MMAL_TIME_UNKNOWN : avpkt->dts;

        if (!size) {
            buffer->flags |= MMAL_BUFFER_HEADER_FLAG_FRAME_END;
            atomic_fetch_add(&ctx->packets_buffered, 1);
        }

        if (!buffer->length) {
            buffer->flags |= MMAL_BUFFER_HEADER_FLAG_EOS;
            ctx->eos_sent = 1;
        }

        if (buf) {
            buffer->ref = av_buffer_ref(buf);
            if (!buffer->ref) {
                av_free(buffer);
                ret = AVERROR(ENOMEM);
                goto done;
            }
        }

        // Insert at end of the list
        if (!ctx->waiting_buffers)
            ctx->waiting_buffers = buffer;
        if (ctx->waiting_buffers_tail)
            ctx->waiting_buffers_tail->next = buffer;
        ctx->waiting_buffers_tail = buffer;
    } while (size);

done:
    av_buffer_unref(&buf);
    return ret;
}