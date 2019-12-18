#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_17__ {scalar_t__ format; int /*<<< orphan*/ ** data; int /*<<< orphan*/ * linesize; int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_16__ {scalar_t__ pBits; int /*<<< orphan*/  Pitch; } ;
struct TYPE_15__ {int /*<<< orphan*/  Height; } ;
struct TYPE_14__ {scalar_t__ palette_dummy; } ;
typedef  int /*<<< orphan*/  IDirect3DSurface9 ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DXVA2Mapping ;
typedef  TYPE_2__ D3DSURFACE_DESC ;
typedef  TYPE_3__ D3DLOCKED_RECT ;
typedef  int /*<<< orphan*/  AVHWFramesContext ;
typedef  TYPE_4__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int AV_HWFRAME_MAP_OVERWRITE ; 
 int AV_HWFRAME_MAP_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 int D3DLOCK_DISCARD ; 
 int D3DLOCK_READONLY ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirect3DSurface9_GetDesc (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  IDirect3DSurface9_LockRect (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IDirect3DSurface9_UnlockRect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 int /*<<< orphan*/  av_image_fill_pointers (int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* av_mallocz (int) ; 
 int av_pix_fmt_count_planes (scalar_t__) ; 
 int /*<<< orphan*/  dxva2_unmap_frame ; 
 int ff_hwframe_map_create (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__ const*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int dxva2_map_frame(AVHWFramesContext *ctx, AVFrame *dst, const AVFrame *src,
                           int flags)
{
    IDirect3DSurface9 *surface = (IDirect3DSurface9*)src->data[3];
    DXVA2Mapping      *map;
    D3DSURFACE_DESC    surfaceDesc;
    D3DLOCKED_RECT     LockedRect;
    HRESULT            hr;
    int i, err, nb_planes;
    int lock_flags = 0;

    nb_planes = av_pix_fmt_count_planes(dst->format);

    hr = IDirect3DSurface9_GetDesc(surface, &surfaceDesc);
    if (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Error getting a surface description\n");
        return AVERROR_UNKNOWN;
    }

    if (!(flags & AV_HWFRAME_MAP_WRITE))
        lock_flags |= D3DLOCK_READONLY;
    if (flags & AV_HWFRAME_MAP_OVERWRITE)
        lock_flags |= D3DLOCK_DISCARD;

    hr = IDirect3DSurface9_LockRect(surface, &LockedRect, NULL, lock_flags);
    if (FAILED(hr)) {
        av_log(ctx, AV_LOG_ERROR, "Unable to lock DXVA2 surface\n");
        return AVERROR_UNKNOWN;
    }

    map = av_mallocz(sizeof(*map));
    if (!map) {
        err = AVERROR(ENOMEM);
        goto fail;
    }

    err = ff_hwframe_map_create(src->hw_frames_ctx, dst, src,
                                dxva2_unmap_frame, map);
    if (err < 0) {
        av_freep(&map);
        goto fail;
    }

    for (i = 0; i < nb_planes; i++)
        dst->linesize[i] = LockedRect.Pitch;

    av_image_fill_pointers(dst->data, dst->format, surfaceDesc.Height,
                           (uint8_t*)LockedRect.pBits, dst->linesize);

    if (dst->format == AV_PIX_FMT_PAL8)
        dst->data[1] = (uint8_t*)map->palette_dummy;

    return 0;
fail:
    IDirect3DSurface9_UnlockRect(surface);
    return err;
}