#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int current_input_buffer; int /*<<< orphan*/  hw_buffer_count; int /*<<< orphan*/  serial; scalar_t__ eos; scalar_t__ flushing; scalar_t__ draining; scalar_t__ output_buffer_count; int /*<<< orphan*/ * codec; } ;
typedef  TYPE_1__ MediaCodecDecContext ;
typedef  int /*<<< orphan*/  FFAMediaCodec ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int ff_AMediaCodec_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mediacodec_dec_flush_codec(AVCodecContext *avctx, MediaCodecDecContext *s)
{
    FFAMediaCodec *codec = s->codec;
    int status;

    s->output_buffer_count = 0;

    s->draining = 0;
    s->flushing = 0;
    s->eos = 0;
    atomic_fetch_add(&s->serial, 1);
    atomic_init(&s->hw_buffer_count, 0);
    s->current_input_buffer = -1;

    status = ff_AMediaCodec_flush(codec);
    if (status < 0) {
        av_log(avctx, AV_LOG_ERROR, "Failed to flush codec\n");
        return AVERROR_EXTERNAL;
    }

    return 0;
}