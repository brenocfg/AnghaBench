#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_16__ {scalar_t__* color; int /*<<< orphan*/  type; } ;
struct TYPE_15__ {int width; int height; } ;
struct TYPE_12__ {scalar_t__ obmc_scratchpad; } ;
struct TYPE_13__ {TYPE_3__ sc; } ;
struct TYPE_14__ {int block_max_depth; int const chroma_h_shift; int const chroma_v_shift; int b_width; TYPE_7__* block; TYPE_4__ m; TYPE_2__* input_picture; TYPE_1__* current_picture; TYPE_6__* plane; } ;
struct TYPE_11__ {int** data; } ;
struct TYPE_10__ {int* linesize; } ;
typedef  TYPE_5__ SnowContext ;
typedef  TYPE_6__ Plane ;
typedef  int IDWTELEM ;
typedef  TYPE_7__ BlockNode ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_INTRA ; 
 int FFMAX (int,int /*<<< orphan*/ ) ; 
 int FFMIN (int const,int) ; 
 int FRAC_BITS ; 
 int LOG2_OBMC_MAX ; 
 int MB_SIZE ; 
 int /*<<< orphan*/  ROUNDED_DIV (int,int) ; 
 int /*<<< orphan*/  add_yblock (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int const*,int,int,int const,int const,int const,int const,int const,int const,int const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int av_clip_uint8 (int /*<<< orphan*/ ) ; 
 int** ff_obmc_tab ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int const) ; 

__attribute__((used)) static int get_dc(SnowContext *s, int mb_x, int mb_y, int plane_index){
    int i, x2, y2;
    Plane *p= &s->plane[plane_index];
    const int block_size = MB_SIZE >> s->block_max_depth;
    const int block_w    = plane_index ? block_size>>s->chroma_h_shift : block_size;
    const int block_h    = plane_index ? block_size>>s->chroma_v_shift : block_size;
    const uint8_t *obmc  = plane_index ? ff_obmc_tab[s->block_max_depth+s->chroma_h_shift] : ff_obmc_tab[s->block_max_depth];
    const int obmc_stride= plane_index ? (2*block_size)>>s->chroma_h_shift : 2*block_size;
    const int ref_stride= s->current_picture->linesize[plane_index];
    uint8_t *src= s-> input_picture->data[plane_index];
    IDWTELEM *dst= (IDWTELEM*)s->m.sc.obmc_scratchpad + plane_index*block_size*block_size*4; //FIXME change to unsigned
    const int b_stride = s->b_width << s->block_max_depth;
    const int w= p->width;
    const int h= p->height;
    int index= mb_x + mb_y*b_stride;
    BlockNode *b= &s->block[index];
    BlockNode backup= *b;
    int ab=0;
    int aa=0;

    av_assert2(s->chroma_h_shift == s->chroma_v_shift); //obmc stuff above

    b->type|= BLOCK_INTRA;
    b->color[plane_index]= 0;
    memset(dst, 0, obmc_stride*obmc_stride*sizeof(IDWTELEM));

    for(i=0; i<4; i++){
        int mb_x2= mb_x + (i &1) - 1;
        int mb_y2= mb_y + (i>>1) - 1;
        int x= block_w*mb_x2 + block_w/2;
        int y= block_h*mb_y2 + block_h/2;

        add_yblock(s, 0, NULL, dst + (i&1)*block_w + (i>>1)*obmc_stride*block_h, NULL, obmc,
                    x, y, block_w, block_h, w, h, obmc_stride, ref_stride, obmc_stride, mb_x2, mb_y2, 0, 0, plane_index);

        for(y2= FFMAX(y, 0); y2<FFMIN(h, y+block_h); y2++){
            for(x2= FFMAX(x, 0); x2<FFMIN(w, x+block_w); x2++){
                int index= x2-(block_w*mb_x - block_w/2) + (y2-(block_h*mb_y - block_h/2))*obmc_stride;
                int obmc_v= obmc[index];
                int d;
                if(y<0) obmc_v += obmc[index + block_h*obmc_stride];
                if(x<0) obmc_v += obmc[index + block_w];
                if(y+block_h>h) obmc_v += obmc[index - block_h*obmc_stride];
                if(x+block_w>w) obmc_v += obmc[index - block_w];
                //FIXME precalculate this or simplify it somehow else

                d = -dst[index] + (1<<(FRAC_BITS-1));
                dst[index] = d;
                ab += (src[x2 + y2*ref_stride] - (d>>FRAC_BITS)) * obmc_v;
                aa += obmc_v * obmc_v; //FIXME precalculate this
            }
        }
    }
    *b= backup;

    return av_clip_uint8( ROUNDED_DIV(ab<<LOG2_OBMC_MAX, aa) ); //FIXME we should not need clipping
}