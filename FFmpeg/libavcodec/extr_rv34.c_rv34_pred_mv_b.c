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
struct TYPE_7__ {int mb_x; int mb_y; int mb_stride; int b8_stride; int mb_width; TYPE_2__* current_picture_ptr; } ;
struct TYPE_6__ {int* mb_type; int*** motion_val; } ;
struct TYPE_5__ {int* avail_cache; scalar_t__** dmv; TYPE_3__ s; } ;
typedef  TYPE_1__ RV34DecContext ;
typedef  TYPE_2__ Picture ;
typedef  TYPE_3__ MpegEncContext ;

/* Variables and functions */
 int MB_TYPE_L0 ; 
 int MB_TYPE_L1 ; 
 int RV34_MB_B_BACKWARD ; 
 int RV34_MB_B_FORWARD ; 
 int /*<<< orphan*/  ZERO8x2 (int*,int) ; 
 int /*<<< orphan*/  rv34_pred_b_vector (int*,int*,int*,int,int,int,int*,int*) ; 

__attribute__((used)) static void rv34_pred_mv_b(RV34DecContext *r, int block_type, int dir)
{
    MpegEncContext *s = &r->s;
    int mb_pos = s->mb_x + s->mb_y * s->mb_stride;
    int mv_pos = s->mb_x * 2 + s->mb_y * 2 * s->b8_stride;
    int A[2] = { 0 }, B[2] = { 0 }, C[2] = { 0 };
    int has_A = 0, has_B = 0, has_C = 0;
    int mx, my;
    int i, j;
    Picture *cur_pic = s->current_picture_ptr;
    const int mask = dir ? MB_TYPE_L1 : MB_TYPE_L0;
    int type = cur_pic->mb_type[mb_pos];

    if((r->avail_cache[6-1] & type) & mask){
        A[0] = cur_pic->motion_val[dir][mv_pos - 1][0];
        A[1] = cur_pic->motion_val[dir][mv_pos - 1][1];
        has_A = 1;
    }
    if((r->avail_cache[6-4] & type) & mask){
        B[0] = cur_pic->motion_val[dir][mv_pos - s->b8_stride][0];
        B[1] = cur_pic->motion_val[dir][mv_pos - s->b8_stride][1];
        has_B = 1;
    }
    if(r->avail_cache[6-4] && (r->avail_cache[6-2] & type) & mask){
        C[0] = cur_pic->motion_val[dir][mv_pos - s->b8_stride + 2][0];
        C[1] = cur_pic->motion_val[dir][mv_pos - s->b8_stride + 2][1];
        has_C = 1;
    }else if((s->mb_x+1) == s->mb_width && (r->avail_cache[6-5] & type) & mask){
        C[0] = cur_pic->motion_val[dir][mv_pos - s->b8_stride - 1][0];
        C[1] = cur_pic->motion_val[dir][mv_pos - s->b8_stride - 1][1];
        has_C = 1;
    }

    rv34_pred_b_vector(A, B, C, has_A, has_B, has_C, &mx, &my);

    mx += r->dmv[dir][0];
    my += r->dmv[dir][1];

    for(j = 0; j < 2; j++){
        for(i = 0; i < 2; i++){
            cur_pic->motion_val[dir][mv_pos + i + j*s->b8_stride][0] = mx;
            cur_pic->motion_val[dir][mv_pos + i + j*s->b8_stride][1] = my;
        }
    }
    if(block_type == RV34_MB_B_BACKWARD || block_type == RV34_MB_B_FORWARD){
        ZERO8x2(cur_pic->motion_val[!dir][mv_pos], s->b8_stride);
    }
}