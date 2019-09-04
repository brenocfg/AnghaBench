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
struct xvmc_pix_fmt {scalar_t__ filled_mv_blocks_num; } ;
struct TYPE_6__ {TYPE_1__* f; } ;
struct MpegEncContext {TYPE_2__ current_picture; } ;
struct TYPE_7__ {struct MpegEncContext* priv_data; } ;
struct TYPE_5__ {scalar_t__* data; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct xvmc_pix_fmt*) ; 
 int /*<<< orphan*/  ff_mpeg_draw_horiz_band (struct MpegEncContext*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ff_xvmc_field_end(AVCodecContext *avctx)
{
    struct MpegEncContext *s = avctx->priv_data;
    struct xvmc_pix_fmt *render = (struct xvmc_pix_fmt*)s->current_picture.f->data[2];
    assert(render);

    if (render->filled_mv_blocks_num > 0)
        ff_mpeg_draw_horiz_band(s, 0, 0);
    return 0;
}