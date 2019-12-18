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
typedef  int uint64_t ;
typedef  int uint16_t ;
typedef  int int16_t ;

/* Variables and functions */
 int ROW_SHIFT ; 
 int W1 ; 
 int W2 ; 
 int W3 ; 
 int W4 ; 
 int W5 ; 
 int W6 ; 
 int W7 ; 
 int extwl (int,int) ; 
 int ldq (int*) ; 
 int sextw (int) ; 
 int /*<<< orphan*/  stq (int,int*) ; 

__attribute__((used)) static inline int idct_row(int16_t *row)
{
    int a0, a1, a2, a3, b0, b1, b2, b3, t;
    uint64_t l, r, t2;
    l = ldq(row);
    r = ldq(row + 4);

    if (l == 0 && r == 0)
        return 0;

    a0 = W4 * sextw(l) + (1 << (ROW_SHIFT - 1));

    if (((l & ~0xffffUL) | r) == 0) {
        a0 >>= ROW_SHIFT;
        t2 = (uint16_t) a0;
        t2 |= t2 << 16;
        t2 |= t2 << 32;

        stq(t2, row);
        stq(t2, row + 4);
        return 1;
    }

    a1 = a0;
    a2 = a0;
    a3 = a0;

    t = extwl(l, 4);            /* row[2] */
    if (t != 0) {
        t = sextw(t);
        a0 += W2 * t;
        a1 += W6 * t;
        a2 -= W6 * t;
        a3 -= W2 * t;
    }

    t = extwl(r, 0);            /* row[4] */
    if (t != 0) {
        t = sextw(t);
        a0 += W4 * t;
        a1 -= W4 * t;
        a2 -= W4 * t;
        a3 += W4 * t;
    }

    t = extwl(r, 4);            /* row[6] */
    if (t != 0) {
        t = sextw(t);
        a0 += W6 * t;
        a1 -= W2 * t;
        a2 += W2 * t;
        a3 -= W6 * t;
    }

    t = extwl(l, 2);            /* row[1] */
    if (t != 0) {
        t = sextw(t);
        b0 = W1 * t;
        b1 = W3 * t;
        b2 = W5 * t;
        b3 = W7 * t;
    } else {
        b0 = 0;
        b1 = 0;
        b2 = 0;
        b3 = 0;
    }

    t = extwl(l, 6);            /* row[3] */
    if (t) {
        t = sextw(t);
        b0 += W3 * t;
        b1 -= W7 * t;
        b2 -= W1 * t;
        b3 -= W5 * t;
    }


    t = extwl(r, 2);            /* row[5] */
    if (t) {
        t = sextw(t);
        b0 += W5 * t;
        b1 -= W1 * t;
        b2 += W7 * t;
        b3 += W3 * t;
    }

    t = extwl(r, 6);            /* row[7] */
    if (t) {
        t = sextw(t);
        b0 += W7 * t;
        b1 -= W5 * t;
        b2 += W3 * t;
        b3 -= W1 * t;
    }

    row[0] = (a0 + b0) >> ROW_SHIFT;
    row[1] = (a1 + b1) >> ROW_SHIFT;
    row[2] = (a2 + b2) >> ROW_SHIFT;
    row[3] = (a3 + b3) >> ROW_SHIFT;
    row[4] = (a3 - b3) >> ROW_SHIFT;
    row[5] = (a2 - b2) >> ROW_SHIFT;
    row[6] = (a1 - b1) >> ROW_SHIFT;
    row[7] = (a0 - b0) >> ROW_SHIFT;

    return 2;
}