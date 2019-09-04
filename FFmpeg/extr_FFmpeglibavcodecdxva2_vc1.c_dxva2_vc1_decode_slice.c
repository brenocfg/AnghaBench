#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct dxva2_picture_context {scalar_t__ slice_count; int bitstream_size; int /*<<< orphan*/ * slice; int /*<<< orphan*/  const* bitstream; } ;
struct TYPE_8__ {TYPE_3__* current_picture_ptr; } ;
struct TYPE_9__ {TYPE_1__ s; } ;
typedef  TYPE_2__ VC1Context ;
struct TYPE_11__ {scalar_t__ codec_id; TYPE_2__* priv_data; } ;
struct TYPE_10__ {struct dxva2_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_3__ Picture ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_VC1 ; 
 int /*<<< orphan*/  AV_RB32 (int /*<<< orphan*/  const*) ; 
 scalar_t__ IS_MARKER (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_SLICES ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_4__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  fill_slice (TYPE_4__*,int /*<<< orphan*/ *,unsigned int,int) ; 

__attribute__((used)) static int dxva2_vc1_decode_slice(AVCodecContext *avctx,
                                  const uint8_t *buffer,
                                  uint32_t size)
{
    const VC1Context *v = avctx->priv_data;
    const Picture *current_picture = v->s.current_picture_ptr;
    struct dxva2_picture_context *ctx_pic = current_picture->hwaccel_picture_private;
    unsigned position;

    if (ctx_pic->slice_count >= MAX_SLICES) {
        avpriv_request_sample(avctx, "%d slices in dxva2",
                              ctx_pic->slice_count);
        return -1;
    }

    if (avctx->codec_id == AV_CODEC_ID_VC1 &&
        size >= 4 && IS_MARKER(AV_RB32(buffer))) {
        buffer += 4;
        size   -= 4;
    }

    if (!ctx_pic->bitstream)
        ctx_pic->bitstream = buffer;
    ctx_pic->bitstream_size += size;

    position = buffer - ctx_pic->bitstream;
    fill_slice(avctx, &ctx_pic->slice[ctx_pic->slice_count++], position, size);
    return 0;
}