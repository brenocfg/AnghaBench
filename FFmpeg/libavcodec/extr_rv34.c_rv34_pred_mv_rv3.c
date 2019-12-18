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
struct TYPE_6__ {int* avail_cache; scalar_t__** dmv; TYPE_3__ s; } ;
struct TYPE_5__ {int*** motion_val; } ;
typedef  TYPE_2__ RV34DecContext ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int* avail_indexes ; 
 int mid_pred (int,int,int) ; 

__attribute__((used)) static void rv34_pred_mv_rv3(RV34DecContext *r, int block_type, int dir)
{
    MpegEncContext *s = &r->s;
    int mv_pos = s->mb_x * 2 + s->mb_y * 2 * s->b8_stride;
    int A[2] = {0}, B[2], C[2];
    int i, j, k;
    int mx, my;
    int* avail = r->avail_cache + avail_indexes[0];

    if(avail[-1]){
        A[0] = s->current_picture_ptr->motion_val[0][mv_pos - 1][0];
        A[1] = s->current_picture_ptr->motion_val[0][mv_pos - 1][1];
    }
    if(avail[-4]){
        B[0] = s->current_picture_ptr->motion_val[0][mv_pos - s->b8_stride][0];
        B[1] = s->current_picture_ptr->motion_val[0][mv_pos - s->b8_stride][1];
    }else{
        B[0] = A[0];
        B[1] = A[1];
    }
    if(!avail[-4 + 2]){
        if(avail[-4] && (avail[-1])){
            C[0] = s->current_picture_ptr->motion_val[0][mv_pos - s->b8_stride - 1][0];
            C[1] = s->current_picture_ptr->motion_val[0][mv_pos - s->b8_stride - 1][1];
        }else{
            C[0] = A[0];
            C[1] = A[1];
        }
    }else{
        C[0] = s->current_picture_ptr->motion_val[0][mv_pos - s->b8_stride + 2][0];
        C[1] = s->current_picture_ptr->motion_val[0][mv_pos - s->b8_stride + 2][1];
    }
    mx = mid_pred(A[0], B[0], C[0]);
    my = mid_pred(A[1], B[1], C[1]);
    mx += r->dmv[0][0];
    my += r->dmv[0][1];
    for(j = 0; j < 2; j++){
        for(i = 0; i < 2; i++){
            for(k = 0; k < 2; k++){
                s->current_picture_ptr->motion_val[k][mv_pos + i + j*s->b8_stride][0] = mx;
                s->current_picture_ptr->motion_val[k][mv_pos + i + j*s->b8_stride][1] = my;
            }
        }
    }
}