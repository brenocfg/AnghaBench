#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int mid_pred (int,int,int) ; 

__attribute__((used)) static inline void rv34_pred_b_vector(int A[2], int B[2], int C[2],
                                      int A_avail, int B_avail, int C_avail,
                                      int *mx, int *my)
{
    if(A_avail + B_avail + C_avail != 3){
        *mx = A[0] + B[0] + C[0];
        *my = A[1] + B[1] + C[1];
        if(A_avail + B_avail + C_avail == 2){
            *mx /= 2;
            *my /= 2;
        }
    }else{
        *mx = mid_pred(A[0], B[0], C[0]);
        *my = mid_pred(A[1], B[1], C[1]);
    }
}