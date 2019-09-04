#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VAStatus ;
struct TYPE_11__ {int nb_param_buffers; int nb_slices; int /*<<< orphan*/ * slice_buffers; int /*<<< orphan*/ * param_buffers; } ;
typedef  TYPE_3__ VAAPIDecodePicture ;
struct TYPE_12__ {TYPE_2__* hwctx; } ;
typedef  TYPE_4__ VAAPIDecodeContext ;
struct TYPE_13__ {TYPE_1__* internal; } ;
struct TYPE_10__ {int /*<<< orphan*/  display; } ;
struct TYPE_9__ {TYPE_4__* hwaccel_priv_data; } ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ VA_STATUS_SUCCESS ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ vaDestroyBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaErrorStr (scalar_t__) ; 

__attribute__((used)) static void ff_vaapi_decode_destroy_buffers(AVCodecContext *avctx,
                                            VAAPIDecodePicture *pic)
{
    VAAPIDecodeContext *ctx = avctx->internal->hwaccel_priv_data;
    VAStatus vas;
    int i;

    for (i = 0; i < pic->nb_param_buffers; i++) {
        vas = vaDestroyBuffer(ctx->hwctx->display,
                              pic->param_buffers[i]);
        if (vas != VA_STATUS_SUCCESS) {
            av_log(avctx, AV_LOG_ERROR, "Failed to destroy "
                   "parameter buffer %#x: %d (%s).\n",
                   pic->param_buffers[i], vas, vaErrorStr(vas));
        }
    }

    for (i = 0; i < 2 * pic->nb_slices; i++) {
        vas = vaDestroyBuffer(ctx->hwctx->display,
                              pic->slice_buffers[i]);
        if (vas != VA_STATUS_SUCCESS) {
            av_log(avctx, AV_LOG_ERROR, "Failed to destroy slice "
                   "slice buffer %#x: %d (%s).\n",
                   pic->slice_buffers[i], vas, vaErrorStr(vas));
        }
    }
}