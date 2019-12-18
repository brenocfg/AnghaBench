#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue_decoded_frames; } ;
struct TYPE_5__ {scalar_t__ userdata; } ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  int /*<<< orphan*/  MMAL_BUFFER_HEADER_T ;
typedef  TYPE_2__ MMALDecodeContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_queue_put (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void output_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
    AVCodecContext *avctx = (AVCodecContext*)port->userdata;
    MMALDecodeContext *ctx = avctx->priv_data;

    mmal_queue_put(ctx->queue_decoded_frames, buffer);
}