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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int16_t ;
struct TYPE_7__ {TYPE_1__* f; } ;
struct TYPE_9__ {int y_dc_scale; int c_dc_scale; int* block_wrap; int** dc_val; int* block_index; int msmpeg4_version; int linesize; int mb_y; int mb_x; int uvlinesize; int h263_aic_dir; TYPE_3__* avctx; TYPE_2__ current_picture; scalar_t__ inter_intra_pred; scalar_t__ first_slice_line; } ;
struct TYPE_8__ {int lowres; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** data; } ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 int FASTDIV (int,int) ; 
 scalar_t__ abs (int) ; 
 int get_dc (int /*<<< orphan*/ *,int,int,int) ; 

int ff_msmpeg4_pred_dc(MpegEncContext *s, int n,
                       int16_t **dc_val_ptr, int *dir_ptr)
{
    int a, b, c, wrap, pred, scale;
    int16_t *dc_val;

    /* find prediction */
    if (n < 4) {
        scale = s->y_dc_scale;
    } else {
        scale = s->c_dc_scale;
    }

    wrap = s->block_wrap[n];
    dc_val= s->dc_val[0] + s->block_index[n];

    /* B C
     * A X
     */
    a = dc_val[ - 1];
    b = dc_val[ - 1 - wrap];
    c = dc_val[ - wrap];

    if(s->first_slice_line && (n&2)==0 && s->msmpeg4_version<4){
        b=c=1024;
    }

    /* XXX: the following solution consumes divisions, but it does not
       necessitate to modify mpegvideo.c. The problem comes from the
       fact they decided to store the quantized DC (which would lead
       to problems if Q could vary !) */
#if ARCH_X86 && HAVE_7REGS && HAVE_EBX_AVAILABLE
    __asm__ volatile(
        "movl %3, %%eax         \n\t"
        "shrl $1, %%eax         \n\t"
        "addl %%eax, %2         \n\t"
        "addl %%eax, %1         \n\t"
        "addl %0, %%eax         \n\t"
        "imull %4               \n\t"
        "movl %%edx, %0         \n\t"
        "movl %1, %%eax         \n\t"
        "imull %4               \n\t"
        "movl %%edx, %1         \n\t"
        "movl %2, %%eax         \n\t"
        "imull %4               \n\t"
        "movl %%edx, %2         \n\t"
        : "+b" (a), "+c" (b), "+D" (c)
        : "g" (scale), "S" (ff_inverse[scale])
        : "%eax", "%edx"
    );
#else
    /* Divisions are costly everywhere; optimize the most common case. */
    if (scale == 8) {
        a = (a + (8 >> 1)) / 8;
        b = (b + (8 >> 1)) / 8;
        c = (c + (8 >> 1)) / 8;
    } else {
        a = FASTDIV((a + (scale >> 1)), scale);
        b = FASTDIV((b + (scale >> 1)), scale);
        c = FASTDIV((c + (scale >> 1)), scale);
    }
#endif
    /* XXX: WARNING: they did not choose the same test as MPEG-4. This
       is very important ! */
    if(s->msmpeg4_version>3){
        if(s->inter_intra_pred){
            uint8_t *dest;
            int wrap;

            if(n==1){
                pred=a;
                *dir_ptr = 0;
            }else if(n==2){
                pred=c;
                *dir_ptr = 1;
            }else if(n==3){
                if (abs(a - b) < abs(b - c)) {
                    pred = c;
                    *dir_ptr = 1;
                } else {
                    pred = a;
                    *dir_ptr = 0;
                }
            }else{
                int bs = 8 >> s->avctx->lowres;
                if(n<4){
                    wrap= s->linesize;
                    dest= s->current_picture.f->data[0] + (((n >> 1) + 2*s->mb_y) * bs*  wrap ) + ((n & 1) + 2*s->mb_x) * bs;
                }else{
                    wrap= s->uvlinesize;
                    dest= s->current_picture.f->data[n - 3] + (s->mb_y * bs * wrap) + s->mb_x * bs;
                }
                if(s->mb_x==0) a= (1024 + (scale>>1))/scale;
                else           a= get_dc(dest-bs, wrap, scale*8>>(2*s->avctx->lowres), bs);
                if(s->mb_y==0) c= (1024 + (scale>>1))/scale;
                else           c= get_dc(dest-bs*wrap, wrap, scale*8>>(2*s->avctx->lowres), bs);

                if (s->h263_aic_dir==0) {
                    pred= a;
                    *dir_ptr = 0;
                }else if (s->h263_aic_dir==1) {
                    if(n==0){
                        pred= c;
                        *dir_ptr = 1;
                    }else{
                        pred= a;
                        *dir_ptr = 0;
                    }
                }else if (s->h263_aic_dir==2) {
                    if(n==0){
                        pred= a;
                        *dir_ptr = 0;
                    }else{
                        pred= c;
                        *dir_ptr = 1;
                    }
                } else {
                    pred= c;
                    *dir_ptr = 1;
                }
            }
        }else{
            if (abs(a - b) < abs(b - c)) {
                pred = c;
                *dir_ptr = 1;
            } else {
                pred = a;
                *dir_ptr = 0;
            }
        }
    }else{
        if (abs(a - b) <= abs(b - c)) {
            pred = c;
            *dir_ptr = 1;
        } else {
            pred = a;
            *dir_ptr = 0;
        }
    }

    /* update predictor */
    *dc_val_ptr = &dc_val[0];
    return pred;
}