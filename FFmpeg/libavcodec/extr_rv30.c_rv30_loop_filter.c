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
struct TYPE_9__ {int mb_stride; int mb_width; int linesize; int uvlinesize; TYPE_2__* current_picture_ptr; } ;
struct TYPE_8__ {int* deblock_coefs; int* cbp_chroma; TYPE_4__ s; } ;
struct TYPE_7__ {int* mb_type; size_t* qscale_table; TYPE_1__* f; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** data; } ;
typedef  TYPE_3__ RV34DecContext ;
typedef  TYPE_4__ MpegEncContext ;

/* Variables and functions */
 scalar_t__ IS_INTRA (int) ; 
 scalar_t__ IS_SEPARATE_DC (int) ; 
 int* rv30_loop_filt_lim ; 
 int /*<<< orphan*/  rv30_weak_loop_filter (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void rv30_loop_filter(RV34DecContext *r, int row)
{
    MpegEncContext *s = &r->s;
    int mb_pos, mb_x;
    int i, j, k;
    uint8_t *Y, *C;
    int loc_lim, cur_lim, left_lim = 0, top_lim = 0;

    mb_pos = row * s->mb_stride;
    for(mb_x = 0; mb_x < s->mb_width; mb_x++, mb_pos++){
        int mbtype = s->current_picture_ptr->mb_type[mb_pos];
        if(IS_INTRA(mbtype) || IS_SEPARATE_DC(mbtype))
            r->deblock_coefs[mb_pos] = 0xFFFF;
        if(IS_INTRA(mbtype))
            r->cbp_chroma[mb_pos] = 0xFF;
    }

    /* all vertical edges are filtered first
     * and horizontal edges are filtered on the next iteration
     */
    mb_pos = row * s->mb_stride;
    for(mb_x = 0; mb_x < s->mb_width; mb_x++, mb_pos++){
        cur_lim = rv30_loop_filt_lim[s->current_picture_ptr->qscale_table[mb_pos]];
        if(mb_x)
            left_lim = rv30_loop_filt_lim[s->current_picture_ptr->qscale_table[mb_pos - 1]];
        for(j = 0; j < 16; j += 4){
            Y = s->current_picture_ptr->f->data[0] + mb_x*16 + (row*16 + j) * s->linesize + 4 * !mb_x;
            for(i = !mb_x; i < 4; i++, Y += 4){
                int ij = i + j;
                loc_lim = 0;
                if(r->deblock_coefs[mb_pos] & (1 << ij))
                    loc_lim = cur_lim;
                else if(!i && r->deblock_coefs[mb_pos - 1] & (1 << (ij + 3)))
                    loc_lim = left_lim;
                else if( i && r->deblock_coefs[mb_pos]     & (1 << (ij - 1)))
                    loc_lim = cur_lim;
                if(loc_lim)
                    rv30_weak_loop_filter(Y, 1, s->linesize, loc_lim);
            }
        }
        for(k = 0; k < 2; k++){
            int cur_cbp, left_cbp = 0;
            cur_cbp = (r->cbp_chroma[mb_pos] >> (k*4)) & 0xF;
            if(mb_x)
                left_cbp = (r->cbp_chroma[mb_pos - 1] >> (k*4)) & 0xF;
            for(j = 0; j < 8; j += 4){
                C = s->current_picture_ptr->f->data[k + 1] + mb_x*8 + (row*8 + j) * s->uvlinesize + 4 * !mb_x;
                for(i = !mb_x; i < 2; i++, C += 4){
                    int ij = i + (j >> 1);
                    loc_lim = 0;
                    if (cur_cbp & (1 << ij))
                        loc_lim = cur_lim;
                    else if(!i && left_cbp & (1 << (ij + 1)))
                        loc_lim = left_lim;
                    else if( i && cur_cbp  & (1 << (ij - 1)))
                        loc_lim = cur_lim;
                    if(loc_lim)
                        rv30_weak_loop_filter(C, 1, s->uvlinesize, loc_lim);
                }
            }
        }
    }
    mb_pos = row * s->mb_stride;
    for(mb_x = 0; mb_x < s->mb_width; mb_x++, mb_pos++){
        cur_lim = rv30_loop_filt_lim[s->current_picture_ptr->qscale_table[mb_pos]];
        if(row)
            top_lim = rv30_loop_filt_lim[s->current_picture_ptr->qscale_table[mb_pos - s->mb_stride]];
        for(j = 4*!row; j < 16; j += 4){
            Y = s->current_picture_ptr->f->data[0] + mb_x*16 + (row*16 + j) * s->linesize;
            for(i = 0; i < 4; i++, Y += 4){
                int ij = i + j;
                loc_lim = 0;
                if(r->deblock_coefs[mb_pos] & (1 << ij))
                    loc_lim = cur_lim;
                else if(!j && r->deblock_coefs[mb_pos - s->mb_stride] & (1 << (ij + 12)))
                    loc_lim = top_lim;
                else if( j && r->deblock_coefs[mb_pos]                & (1 << (ij - 4)))
                    loc_lim = cur_lim;
                if(loc_lim)
                    rv30_weak_loop_filter(Y, s->linesize, 1, loc_lim);
            }
        }
        for(k = 0; k < 2; k++){
            int cur_cbp, top_cbp = 0;
            cur_cbp = (r->cbp_chroma[mb_pos] >> (k*4)) & 0xF;
            if(row)
                top_cbp = (r->cbp_chroma[mb_pos - s->mb_stride] >> (k*4)) & 0xF;
            for(j = 4*!row; j < 8; j += 4){
                C = s->current_picture_ptr->f->data[k+1] + mb_x*8 + (row*8 + j) * s->uvlinesize;
                for(i = 0; i < 2; i++, C += 4){
                    int ij = i + (j >> 1);
                    loc_lim = 0;
                    if (r->cbp_chroma[mb_pos] & (1 << ij))
                        loc_lim = cur_lim;
                    else if(!j && top_cbp & (1 << (ij + 2)))
                        loc_lim = top_lim;
                    else if( j && cur_cbp & (1 << (ij - 2)))
                        loc_lim = cur_lim;
                    if(loc_lim)
                        rv30_weak_loop_filter(C, s->uvlinesize, 1, loc_lim);
                }
            }
        }
    }
}