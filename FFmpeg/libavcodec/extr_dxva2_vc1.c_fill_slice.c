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
struct TYPE_9__ {int mb_y; scalar_t__ pict_type; int mb_width; scalar_t__ mb_x; int /*<<< orphan*/  gb; } ;
struct TYPE_8__ {int field_mode; int /*<<< orphan*/  pq; scalar_t__ p_frame_skipped; scalar_t__ bfraction_lut_index; int /*<<< orphan*/  bi_type; TYPE_2__ s; } ;
typedef  TYPE_1__ VC1Context ;
struct TYPE_11__ {scalar_t__ codec_id; TYPE_1__* priv_data; } ;
struct TYPE_10__ {int wVerticalPosition; int dwSliceBitsInBuffer; unsigned int dwSliceDataLocation; int wMBbitOffset; scalar_t__ wBadSliceChopping; int /*<<< orphan*/  wQuantizerScaleCode; scalar_t__ wNumberMBsInSlice; scalar_t__ bReservedBits; scalar_t__ bStartCodeBitOffset; scalar_t__ wHorizontalPosition; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ DXVA_SliceInfo ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_VC1 ; 
 scalar_t__ AV_PICTURE_TYPE_B ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_slice(AVCodecContext *avctx, DXVA_SliceInfo *slice,
                       unsigned position, unsigned size)
{
    const VC1Context *v = avctx->priv_data;
    const MpegEncContext *s = &v->s;

    memset(slice, 0, sizeof(*slice));
    slice->wHorizontalPosition = 0;
    slice->wVerticalPosition   = s->mb_y;
    slice->dwSliceBitsInBuffer = 8 * size;
    slice->dwSliceDataLocation = position;
    slice->bStartCodeBitOffset = 0;
    slice->bReservedBits       = (s->pict_type == AV_PICTURE_TYPE_B && !v->bi_type) ? v->bfraction_lut_index + 9 : 0;
    slice->wMBbitOffset        = v->p_frame_skipped ? 0xffff : get_bits_count(&s->gb) + (avctx->codec_id == AV_CODEC_ID_VC1 ? 32 : 0);
    /* XXX We store the index of the first MB and it will be fixed later */
    slice->wNumberMBsInSlice   = (s->mb_y >> v->field_mode) * s->mb_width + s->mb_x;
    slice->wQuantizerScaleCode = v->pq;
    slice->wBadSliceChopping   = 0;
}