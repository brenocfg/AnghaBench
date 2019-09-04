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
typedef  int int16_t ;
struct TYPE_4__ {int*** motion_val; } ;
struct TYPE_5__ {int b8_stride; int* block_index; scalar_t__ mb_x; scalar_t__ resync_mb_x; scalar_t__ h263_pred; scalar_t__ first_slice_line; TYPE_1__ current_picture; } ;
typedef  TYPE_2__ MpegEncContext ;

/* Variables and functions */
 int mid_pred (int,int,int) ; 

int16_t *ff_h263_pred_motion(MpegEncContext * s, int block, int dir,
                             int *px, int *py)
{
    int wrap;
    int16_t *A, *B, *C, (*mot_val)[2];
    static const int off[4]= {2, 1, 1, -1};

    wrap = s->b8_stride;
    mot_val = s->current_picture.motion_val[dir] + s->block_index[block];

    A = mot_val[ - 1];
    /* special case for first (slice) line */
    if (s->first_slice_line && block<3) {
        // we can't just change some MVs to simulate that as we need them for the B-frames (and ME)
        // and if we ever support non rectangular objects than we need to do a few ifs here anyway :(
        if(block==0){ //most common case
            if(s->mb_x  == s->resync_mb_x){ //rare
                *px= *py = 0;
            }else if(s->mb_x + 1 == s->resync_mb_x && s->h263_pred){ //rare
                C = mot_val[off[block] - wrap];
                if(s->mb_x==0){
                    *px = C[0];
                    *py = C[1];
                }else{
                    *px = mid_pred(A[0], 0, C[0]);
                    *py = mid_pred(A[1], 0, C[1]);
                }
            }else{
                *px = A[0];
                *py = A[1];
            }
        }else if(block==1){
            if(s->mb_x + 1 == s->resync_mb_x && s->h263_pred){ //rare
                C = mot_val[off[block] - wrap];
                *px = mid_pred(A[0], 0, C[0]);
                *py = mid_pred(A[1], 0, C[1]);
            }else{
                *px = A[0];
                *py = A[1];
            }
        }else{ /* block==2*/
            B = mot_val[ - wrap];
            C = mot_val[off[block] - wrap];
            if(s->mb_x == s->resync_mb_x) //rare
                A[0]=A[1]=0;

            *px = mid_pred(A[0], B[0], C[0]);
            *py = mid_pred(A[1], B[1], C[1]);
        }
    } else {
        B = mot_val[ - wrap];
        C = mot_val[off[block] - wrap];
        *px = mid_pred(A[0], B[0], C[0]);
        *py = mid_pred(A[1], B[1], C[1]);
    }
    return *mot_val;
}