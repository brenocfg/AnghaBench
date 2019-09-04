#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* priv_data; } ;
struct TYPE_8__ {TYPE_1__* decoder; } ;
struct TYPE_7__ {int /*<<< orphan*/ * output; int /*<<< orphan*/ * input; int /*<<< orphan*/  control; } ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_COMPONENT_T ;
typedef  TYPE_2__ MMALDecodeContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  control_port_cb ; 
 int /*<<< orphan*/  ffmmal_stop_decoder (TYPE_3__*) ; 
 int /*<<< orphan*/  input_callback ; 
 scalar_t__ mmal_port_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_callback ; 

__attribute__((used)) static void ffmmal_flush(AVCodecContext *avctx)
{
    MMALDecodeContext *ctx = avctx->priv_data;
    MMAL_COMPONENT_T *decoder = ctx->decoder;
    MMAL_STATUS_T status;

    ffmmal_stop_decoder(avctx);

    if ((status = mmal_port_enable(decoder->control, control_port_cb)))
        goto fail;
    if ((status = mmal_port_enable(decoder->input[0], input_callback)))
        goto fail;
    if ((status = mmal_port_enable(decoder->output[0], output_callback)))
        goto fail;

    return;

fail:
    av_log(avctx, AV_LOG_ERROR, "MMAL flush error: %i\n", (int)status);
}