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
typedef  int /*<<< orphan*/  uint32_t ;
struct vp9_dxva2_picture_context {int /*<<< orphan*/  slice; int /*<<< orphan*/  const* bitstream; int /*<<< orphan*/  bitstream_size; } ;
struct TYPE_6__ {TYPE_1__* frames; } ;
typedef  TYPE_2__ VP9SharedContext ;
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_5__ {struct vp9_dxva2_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 size_t CUR_FRAME ; 
 int /*<<< orphan*/  fill_slice_short (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dxva2_vp9_decode_slice(AVCodecContext *avctx,
                                  const uint8_t *buffer,
                                  uint32_t size)
{
    const VP9SharedContext *h = avctx->priv_data;
    struct vp9_dxva2_picture_context *ctx_pic = h->frames[CUR_FRAME].hwaccel_picture_private;
    unsigned position;

    if (!ctx_pic->bitstream)
        ctx_pic->bitstream = buffer;
    ctx_pic->bitstream_size += size;

    position = buffer - ctx_pic->bitstream;
    fill_slice_short(&ctx_pic->slice, position, size);

    return 0;
}