#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  surface_id ;
typedef  scalar_t__ VASurfaceID ;
typedef  scalar_t__ VAStatus ;
struct TYPE_11__ {int /*<<< orphan*/  nb_attributes; int /*<<< orphan*/  attributes; int /*<<< orphan*/  rt_format; } ;
typedef  TYPE_3__ VAAPIFramesContext ;
struct TYPE_14__ {scalar_t__ initial_pool_size; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_4__* hwctx; TYPE_2__* device_ctx; TYPE_1__* internal; } ;
struct TYPE_13__ {int /*<<< orphan*/  display; } ;
struct TYPE_12__ {scalar_t__ nb_surfaces; scalar_t__* surface_ids; } ;
struct TYPE_10__ {TYPE_5__* hwctx; } ;
struct TYPE_9__ {TYPE_3__* priv; } ;
typedef  TYPE_4__ AVVAAPIFramesContext ;
typedef  TYPE_5__ AVVAAPIDeviceContext ;
typedef  TYPE_6__ AVHWFramesContext ;
typedef  int /*<<< orphan*/  AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  AV_BUFFER_FLAG_READONLY ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ VA_STATUS_SUCCESS ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/ * av_buffer_create (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 scalar_t__ vaCreateSurfaces (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vaDestroySurfaces (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  vaErrorStr (scalar_t__) ; 
 int /*<<< orphan*/  vaapi_buffer_free ; 

__attribute__((used)) static AVBufferRef *vaapi_pool_alloc(void *opaque, int size)
{
    AVHWFramesContext     *hwfc = opaque;
    VAAPIFramesContext     *ctx = hwfc->internal->priv;
    AVVAAPIDeviceContext *hwctx = hwfc->device_ctx->hwctx;
    AVVAAPIFramesContext  *avfc = hwfc->hwctx;
    VASurfaceID surface_id;
    VAStatus vas;
    AVBufferRef *ref;

    if (hwfc->initial_pool_size > 0 &&
        avfc->nb_surfaces >= hwfc->initial_pool_size)
        return NULL;

    vas = vaCreateSurfaces(hwctx->display, ctx->rt_format,
                           hwfc->width, hwfc->height,
                           &surface_id, 1,
                           ctx->attributes, ctx->nb_attributes);
    if (vas != VA_STATUS_SUCCESS) {
        av_log(hwfc, AV_LOG_ERROR, "Failed to create surface: "
               "%d (%s).\n", vas, vaErrorStr(vas));
        return NULL;
    }
    av_log(hwfc, AV_LOG_DEBUG, "Created surface %#x.\n", surface_id);

    ref = av_buffer_create((uint8_t*)(uintptr_t)surface_id,
                           sizeof(surface_id), &vaapi_buffer_free,
                           hwfc, AV_BUFFER_FLAG_READONLY);
    if (!ref) {
        vaDestroySurfaces(hwctx->display, &surface_id, 1);
        return NULL;
    }

    if (hwfc->initial_pool_size > 0) {
        // This is a fixed-size pool, so we must still be in the initial
        // allocation sequence.
        av_assert0(avfc->nb_surfaces < hwfc->initial_pool_size);
        avfc->surface_ids[avfc->nb_surfaces] = surface_id;
        ++avfc->nb_surfaces;
    }

    return ref;
}