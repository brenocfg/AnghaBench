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
typedef  int int16_t ;

/* Variables and functions */
 int COL_SHIFT ; 
 int W1 ; 
 int W2 ; 
 int W3 ; 
 int W4 ; 
 int W5 ; 
 int W6 ; 
 int W7 ; 

__attribute__((used)) static inline void idct_col(int16_t *col)
{
    int a0, a1, a2, a3, b0, b1, b2, b3;

    col[0] += (1 << (COL_SHIFT - 1)) / W4;

    a0 = W4 * col[8 * 0];
    a1 = W4 * col[8 * 0];
    a2 = W4 * col[8 * 0];
    a3 = W4 * col[8 * 0];

    if (col[8 * 2]) {
        a0 += W2 * col[8 * 2];
        a1 += W6 * col[8 * 2];
        a2 -= W6 * col[8 * 2];
        a3 -= W2 * col[8 * 2];
    }

    if (col[8 * 4]) {
        a0 += W4 * col[8 * 4];
        a1 -= W4 * col[8 * 4];
        a2 -= W4 * col[8 * 4];
        a3 += W4 * col[8 * 4];
    }

    if (col[8 * 6]) {
        a0 += W6 * col[8 * 6];
        a1 -= W2 * col[8 * 6];
        a2 += W2 * col[8 * 6];
        a3 -= W6 * col[8 * 6];
    }

    if (col[8 * 1]) {
        b0 = W1 * col[8 * 1];
        b1 = W3 * col[8 * 1];
        b2 = W5 * col[8 * 1];
        b3 = W7 * col[8 * 1];
    } else {
        b0 = 0;
        b1 = 0;
        b2 = 0;
        b3 = 0;
    }

    if (col[8 * 3]) {
        b0 += W3 * col[8 * 3];
        b1 -= W7 * col[8 * 3];
        b2 -= W1 * col[8 * 3];
        b3 -= W5 * col[8 * 3];
    }

    if (col[8 * 5]) {
        b0 += W5 * col[8 * 5];
        b1 -= W1 * col[8 * 5];
        b2 += W7 * col[8 * 5];
        b3 += W3 * col[8 * 5];
    }

    if (col[8 * 7]) {
        b0 += W7 * col[8 * 7];
        b1 -= W5 * col[8 * 7];
        b2 += W3 * col[8 * 7];
        b3 -= W1 * col[8 * 7];
    }

    col[8 * 0] = (a0 + b0) >> COL_SHIFT;
    col[8 * 7] = (a0 - b0) >> COL_SHIFT;
    col[8 * 1] = (a1 + b1) >> COL_SHIFT;
    col[8 * 6] = (a1 - b1) >> COL_SHIFT;
    col[8 * 2] = (a2 + b2) >> COL_SHIFT;
    col[8 * 5] = (a2 - b2) >> COL_SHIFT;
    col[8 * 3] = (a3 + b3) >> COL_SHIFT;
    col[8 * 4] = (a3 - b3) >> COL_SHIFT;
}