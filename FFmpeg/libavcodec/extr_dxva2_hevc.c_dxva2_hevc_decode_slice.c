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
struct hevc_dxva2_picture_context {size_t slice_count; int /*<<< orphan*/ * slice_short; int /*<<< orphan*/  const* bitstream; int /*<<< orphan*/  bitstream_size; } ;
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {TYPE_1__* ref; } ;
struct TYPE_5__ {struct hevc_dxva2_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_1__ HEVCFrame ;
typedef  TYPE_2__ HEVCContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 size_t MAX_SLICES ; 
 int /*<<< orphan*/  fill_slice_short (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dxva2_hevc_decode_slice(AVCodecContext *avctx,
                                   const uint8_t *buffer,
                                   uint32_t size)
{
    const HEVCContext *h = avctx->priv_data;
    const HEVCFrame *current_picture = h->ref;
    struct hevc_dxva2_picture_context *ctx_pic = current_picture->hwaccel_picture_private;
    unsigned position;

    if (ctx_pic->slice_count >= MAX_SLICES)
        return -1;

    if (!ctx_pic->bitstream)
        ctx_pic->bitstream = buffer;
    ctx_pic->bitstream_size += size;

    position = buffer - ctx_pic->bitstream;
    fill_slice_short(&ctx_pic->slice_short[ctx_pic->slice_count], position, size);
    ctx_pic->slice_count++;

    return 0;
}