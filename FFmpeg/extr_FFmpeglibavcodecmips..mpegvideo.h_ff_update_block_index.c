#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* dest; int chroma_x_shift; scalar_t__* block_index; TYPE_1__* avctx; } ;
struct TYPE_4__ {int bits_per_raw_sample; int lowres; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */

__attribute__((used)) static inline void ff_update_block_index(MpegEncContext *s){
    const int bytes_per_pixel = 1 + (s->avctx->bits_per_raw_sample > 8);
    const int block_size= (8*bytes_per_pixel) >> s->avctx->lowres;

    s->block_index[0]+=2;
    s->block_index[1]+=2;
    s->block_index[2]+=2;
    s->block_index[3]+=2;
    s->block_index[4]++;
    s->block_index[5]++;
    s->dest[0]+= 2*block_size;
    s->dest[1]+= (2 >> s->chroma_x_shift) * block_size;
    s->dest[2]+= (2 >> s->chroma_x_shift) * block_size;
}