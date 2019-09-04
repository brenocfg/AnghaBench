#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  buffer_id ;
typedef  scalar_t__ VAStatus ;
typedef  scalar_t__ VABufferID ;
struct TYPE_7__ {int surface_width; int surface_height; TYPE_1__* hwctx; int /*<<< orphan*/  va_context; } ;
typedef  TYPE_2__ VAAPIEncodeContext ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  display; } ;
typedef  TYPE_3__ AVCodecContext ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BUFFER_FLAG_READONLY ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  VAEncCodedBufferType ; 
 scalar_t__ VA_STATUS_SUCCESS ; 
 int /*<<< orphan*/ * av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ vaCreateBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  vaDestroyBuffer (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vaErrorStr (scalar_t__) ; 
 int /*<<< orphan*/  vaapi_encode_free_output_buffer ; 

__attribute__((used)) static AVBufferRef *vaapi_encode_alloc_output_buffer(void *opaque,
                                                     int size)
{
    AVCodecContext   *avctx = opaque;
    VAAPIEncodeContext *ctx = avctx->priv_data;
    VABufferID buffer_id;
    VAStatus vas;
    AVBufferRef *ref;

    // The output buffer size is fixed, so it needs to be large enough
    // to hold the largest possible compressed frame.  We assume here
    // that the uncompressed frame plus some header data is an upper
    // bound on that.
    vas = vaCreateBuffer(ctx->hwctx->display, ctx->va_context,
                         VAEncCodedBufferType,
                         3 * ctx->surface_width * ctx->surface_height +
                         (1 << 16), 1, 0, &buffer_id);
    if (vas != VA_STATUS_SUCCESS) {
        av_log(avctx, AV_LOG_ERROR, "Failed to create bitstream "
               "output buffer: %d (%s).\n", vas, vaErrorStr(vas));
        return NULL;
    }

    av_log(avctx, AV_LOG_DEBUG, "Allocated output buffer %#x\n", buffer_id);

    ref = av_buffer_create((uint8_t*)(uintptr_t)buffer_id,
                           sizeof(buffer_id),
                           &vaapi_encode_free_output_buffer,
                           avctx, AV_BUFFER_FLAG_READONLY);
    if (!ref) {
        vaDestroyBuffer(ctx->hwctx->display, buffer_id);
        return NULL;
    }

    return ref;
}