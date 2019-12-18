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
struct TYPE_7__ {int mb_x; int mb_y; int b8_stride; TYPE_1__* current_picture_ptr; } ;
struct TYPE_6__ {int* avail_cache; scalar_t__** dmv; scalar_t__ rv30; TYPE_3__ s; } ;
struct TYPE_5__ {int*** motion_val; } ;
typedef  TYPE_2__ RV34DecContext ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int* avail_indexes ; 
 int mid_pred (int,int,int) ; 
 int* part_sizes_h ; 
 int* part_sizes_w ; 

__attribute__((used)) static void rv34_pred_mv(RV34DecContext *r, int block_type, int subblock_no, int dmv_no)
{
    MpegEncContext *s = &r->s;
    int mv_pos = s->mb_x * 2 + s->mb_y * 2 * s->b8_stride;
    int A[2] = {0}, B[2], C[2];
    int i, j;
    int mx, my;
    int* avail = r->avail_cache + avail_indexes[subblock_no];
    int c_off = part_sizes_w[block_type];

    mv_pos += (subblock_no & 1) + (subblock_no >> 1)*s->b8_stride;
    if(subblock_no == 3)
        c_off = -1;

    if(avail[-1]){
        A[0] = s->current_picture_ptr->motion_val[0][mv_pos-1][0];
        A[1] = s->current_picture_ptr->motion_val[0][mv_pos-1][1];
    }
    if(avail[-4]){
        B[0] = s->current_picture_ptr->motion_val[0][mv_pos-s->b8_stride][0];
        B[1] = s->current_picture_ptr->motion_val[0][mv_pos-s->b8_stride][1];
    }else{
        B[0] = A[0];
        B[1] = A[1];
    }
    if(!avail[c_off-4]){
        if(avail[-4] && (avail[-1] || r->rv30)){
            C[0] = s->current_picture_ptr->motion_val[0][mv_pos-s->b8_stride-1][0];
            C[1] = s->current_picture_ptr->motion_val[0][mv_pos-s->b8_stride-1][1];
        }else{
            C[0] = A[0];
            C[1] = A[1];
        }
    }else{
        C[0] = s->current_picture_ptr->motion_val[0][mv_pos-s->b8_stride+c_off][0];
        C[1] = s->current_picture_ptr->motion_val[0][mv_pos-s->b8_stride+c_off][1];
    }
    mx = mid_pred(A[0], B[0], C[0]);
    my = mid_pred(A[1], B[1], C[1]);
    mx += r->dmv[dmv_no][0];
    my += r->dmv[dmv_no][1];
    for(j = 0; j < part_sizes_h[block_type]; j++){
        for(i = 0; i < part_sizes_w[block_type]; i++){
            s->current_picture_ptr->motion_val[0][mv_pos + i + j*s->b8_stride][0] = mx;
            s->current_picture_ptr->motion_val[0][mv_pos + i + j*s->b8_stride][1] = my;
        }
    }
}