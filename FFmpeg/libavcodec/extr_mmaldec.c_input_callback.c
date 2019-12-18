#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* priv_data; } ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  ref; } ;
struct TYPE_12__ {int /*<<< orphan*/  packets_buffered; } ;
struct TYPE_11__ {TYPE_4__* user_data; int /*<<< orphan*/  cmd; } ;
struct TYPE_10__ {scalar_t__ userdata; } ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;
typedef  TYPE_3__ MMALDecodeContext ;
typedef  TYPE_4__ FFBufferEntry ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int MMAL_BUFFER_HEADER_FLAG_FRAME_END ; 
 int /*<<< orphan*/  atomic_fetch_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (TYPE_4__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_2__*) ; 

__attribute__((used)) static void input_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
    AVCodecContext *avctx = (AVCodecContext*)port->userdata;
    MMALDecodeContext *ctx = avctx->priv_data;

    if (!buffer->cmd) {
        FFBufferEntry *entry = buffer->user_data;
        av_buffer_unref(&entry->ref);
        if (entry->flags & MMAL_BUFFER_HEADER_FLAG_FRAME_END)
            atomic_fetch_add(&ctx->packets_buffered, -1);
        av_free(entry);
    }
    mmal_buffer_header_release(buffer);
}