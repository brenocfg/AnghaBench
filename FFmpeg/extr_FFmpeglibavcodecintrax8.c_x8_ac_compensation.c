#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int** block; size_t* idct_permutation; void** block_last_index; } ;
typedef  TYPE_1__ IntraX8Context ;

/* Variables and functions */
 void* FFMAX (void*,int) ; 

__attribute__((used)) static void x8_ac_compensation(IntraX8Context *const w, const int direction,
                               const int dc_level)
{
    int t;
#define B(x,y)  w->block[0][w->idct_permutation[(x) + (y) * 8]]
#define T(x)  ((x) * dc_level + 0x8000) >> 16;
    switch (direction) {
    case 0:
        t        = T(3811); // h
        B(1, 0) -= t;
        B(0, 1) -= t;

        t        = T(487); // e
        B(2, 0) -= t;
        B(0, 2) -= t;

        t        = T(506); // f
        B(3, 0) -= t;
        B(0, 3) -= t;

        t        = T(135); // c
        B(4, 0) -= t;
        B(0, 4) -= t;
        B(2, 1) += t;
        B(1, 2) += t;
        B(3, 1) += t;
        B(1, 3) += t;

        t        = T(173); // d
        B(5, 0) -= t;
        B(0, 5) -= t;

        t        = T(61); // b
        B(6, 0) -= t;
        B(0, 6) -= t;
        B(5, 1) += t;
        B(1, 5) += t;

        t        = T(42); // a
        B(7, 0) -= t;
        B(0, 7) -= t;
        B(4, 1) += t;
        B(1, 4) += t;
        B(4, 4) += t;

        t        = T(1084); // g
        B(1, 1) += t;

        w->block_last_index[0] = FFMAX(w->block_last_index[0], 7 * 8);
        break;
    case 1:
        B(0, 1) -= T(6269);
        B(0, 3) -= T(708);
        B(0, 5) -= T(172);
        B(0, 7) -= T(73);

        w->block_last_index[0] = FFMAX(w->block_last_index[0], 7 * 8);
        break;
    case 2:
        B(1, 0) -= T(6269);
        B(3, 0) -= T(708);
        B(5, 0) -= T(172);
        B(7, 0) -= T(73);

        w->block_last_index[0] = FFMAX(w->block_last_index[0], 7);
        break;
    }
#undef B
#undef T
}