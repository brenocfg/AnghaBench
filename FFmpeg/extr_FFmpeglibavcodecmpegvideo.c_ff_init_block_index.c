#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* f; } ;
struct TYPE_9__ {int* block_index; int b8_stride; int mb_y; int mb_x; int mb_stride; int mb_height; int const chroma_x_shift; scalar_t__ pict_type; scalar_t__ picture_structure; int const chroma_y_shift; scalar_t__* dest; TYPE_3__* avctx; TYPE_2__ current_picture; } ;
struct TYPE_8__ {int bits_per_raw_sample; int lowres; scalar_t__ draw_horiz_band; } ;
struct TYPE_6__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ AV_PICTURE_TYPE_B ; 
 scalar_t__ PICT_BOTTOM_FIELD ; 
 scalar_t__ PICT_FRAME ; 
 int /*<<< orphan*/  av_assert1 (int) ; 

void ff_init_block_index(MpegEncContext *s){ //FIXME maybe rename
    const int linesize   = s->current_picture.f->linesize[0]; //not s->linesize as this would be wrong for field pics
    const int uvlinesize = s->current_picture.f->linesize[1];
    const int width_of_mb = (4 + (s->avctx->bits_per_raw_sample > 8)) - s->avctx->lowres;
    const int height_of_mb = 4 - s->avctx->lowres;

    s->block_index[0]= s->b8_stride*(s->mb_y*2    ) - 2 + s->mb_x*2;
    s->block_index[1]= s->b8_stride*(s->mb_y*2    ) - 1 + s->mb_x*2;
    s->block_index[2]= s->b8_stride*(s->mb_y*2 + 1) - 2 + s->mb_x*2;
    s->block_index[3]= s->b8_stride*(s->mb_y*2 + 1) - 1 + s->mb_x*2;
    s->block_index[4]= s->mb_stride*(s->mb_y + 1)                + s->b8_stride*s->mb_height*2 + s->mb_x - 1;
    s->block_index[5]= s->mb_stride*(s->mb_y + s->mb_height + 2) + s->b8_stride*s->mb_height*2 + s->mb_x - 1;
    //block_index is not used by mpeg2, so it is not affected by chroma_format

    s->dest[0] = s->current_picture.f->data[0] + (int)((s->mb_x - 1U) <<  width_of_mb);
    s->dest[1] = s->current_picture.f->data[1] + (int)((s->mb_x - 1U) << (width_of_mb - s->chroma_x_shift));
    s->dest[2] = s->current_picture.f->data[2] + (int)((s->mb_x - 1U) << (width_of_mb - s->chroma_x_shift));

    if(!(s->pict_type==AV_PICTURE_TYPE_B && s->avctx->draw_horiz_band && s->picture_structure==PICT_FRAME))
    {
        if(s->picture_structure==PICT_FRAME){
        s->dest[0] += s->mb_y *   linesize << height_of_mb;
        s->dest[1] += s->mb_y * uvlinesize << (height_of_mb - s->chroma_y_shift);
        s->dest[2] += s->mb_y * uvlinesize << (height_of_mb - s->chroma_y_shift);
        }else{
            s->dest[0] += (s->mb_y>>1) *   linesize << height_of_mb;
            s->dest[1] += (s->mb_y>>1) * uvlinesize << (height_of_mb - s->chroma_y_shift);
            s->dest[2] += (s->mb_y>>1) * uvlinesize << (height_of_mb - s->chroma_y_shift);
            av_assert1((s->mb_y&1) == (s->picture_structure == PICT_BOTTOM_FIELD));
        }
    }
}