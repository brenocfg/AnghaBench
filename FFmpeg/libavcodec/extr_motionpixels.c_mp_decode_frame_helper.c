#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {void* u; void* v; int /*<<< orphan*/  y; } ;
typedef  TYPE_2__ YuvPixel ;
struct TYPE_14__ {scalar_t__* changes_map; TYPE_1__* avctx; TYPE_2__* vpt; int /*<<< orphan*/  gradient_scale; } ;
struct TYPE_12__ {int height; int width; } ;
typedef  TYPE_3__ MotionPixelsContext ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert1 (scalar_t__) ; 
 void* av_clip_intp2 (void*,int) ; 
 int /*<<< orphan*/  av_clip_uintp2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mp_decode_line (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mp_get_vlc (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__ mp_get_yuv_from_rgb (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mp_gradient (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_set_rgb_from_yuv (TYPE_3__*,int /*<<< orphan*/ ,int,TYPE_2__*) ; 

__attribute__((used)) static void mp_decode_frame_helper(MotionPixelsContext *mp, GetBitContext *gb)
{
    YuvPixel p;
    int y, y0;

    av_assert1(mp->changes_map[0]);

    for (y = 0; y < mp->avctx->height; ++y) {
        if (mp->changes_map[y * mp->avctx->width] != 0) {
            memset(mp->gradient_scale, 1, sizeof(mp->gradient_scale));
            p = mp_get_yuv_from_rgb(mp, 0, y);
        } else {
            p.y += mp_gradient(mp, 0, mp_get_vlc(mp, gb));
            p.y = av_clip_uintp2(p.y, 5);
            if ((y & 3) == 0) {
                p.v += mp_gradient(mp, 1, mp_get_vlc(mp, gb));
                p.v = av_clip_intp2(p.v, 5);
                p.u += mp_gradient(mp, 2, mp_get_vlc(mp, gb));
                p.u = av_clip_intp2(p.u, 5);
            }
            mp->vpt[y] = p;
            mp_set_rgb_from_yuv(mp, 0, y, &p);
        }
    }
    for (y0 = 0; y0 < 2; ++y0)
        for (y = y0; y < mp->avctx->height; y += 2)
            mp_decode_line(mp, gb, y);
}