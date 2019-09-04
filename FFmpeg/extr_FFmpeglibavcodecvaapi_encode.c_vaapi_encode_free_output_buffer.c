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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ VABufferID ;
struct TYPE_6__ {TYPE_1__* hwctx; } ;
typedef  TYPE_2__ VAAPIEncodeContext ;
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  vaDestroyBuffer (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void vaapi_encode_free_output_buffer(void *opaque,
                                            uint8_t *data)
{
    AVCodecContext   *avctx = opaque;
    VAAPIEncodeContext *ctx = avctx->priv_data;
    VABufferID buffer_id;

    buffer_id = (VABufferID)(uintptr_t)data;

    vaDestroyBuffer(ctx->hwctx->display, buffer_id);

    av_log(avctx, AV_LOG_DEBUG, "Freed output buffer %#x\n", buffer_id);
}