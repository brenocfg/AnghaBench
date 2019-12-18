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
struct TYPE_3__ {int edges; int mb_x; int mb_y; int mb_width; int est_run; int* prediction_table; int orient; int quant; } ;
typedef  TYPE_1__ IntraX8Context ;

/* Variables and functions */
 void* FFMIN (int,int) ; 

__attribute__((used)) static void x8_get_prediction(IntraX8Context *const w)
{
    int a, b, c, i;

    w->edges  = 1 * !w->mb_x;
    w->edges |= 2 * !w->mb_y;
    w->edges |= 4 * (w->mb_x >= (2 * w->mb_width - 1));

    switch (w->edges & 3) {
    case 0:
        break;
    case 1:
        // take the one from the above block[0][y - 1]
        w->est_run = w->prediction_table[!(w->mb_y & 1)] >> 2;
        w->orient  = 1;
        return;
    case 2:
        // take the one from the previous block[x - 1][0]
        w->est_run = w->prediction_table[2 * w->mb_x - 2] >> 2;
        w->orient  = 2;
        return;
    case 3:
        w->est_run = 16;
        w->orient  = 0;
        return;
    }
    // no edge cases
    b = w->prediction_table[2 * w->mb_x     + !(w->mb_y & 1)]; // block[x    ][y - 1]
    a = w->prediction_table[2 * w->mb_x - 2 +  (w->mb_y & 1)]; // block[x - 1][y    ]
    c = w->prediction_table[2 * w->mb_x - 2 + !(w->mb_y & 1)]; // block[x - 1][y - 1]

    w->est_run = FFMIN(b, a);
    /* This condition has nothing to do with w->edges, even if it looks
     * similar it would trigger if e.g. x = 3; y = 2;
     * I guess somebody wrote something wrong and it became standard. */
    if ((w->mb_x & w->mb_y) != 0)
        w->est_run = FFMIN(c, w->est_run);
    w->est_run >>= 2;

    a &= 3;
    b &= 3;
    c &= 3;

    i = (0xFFEAF4C4 >> (2 * b + 8 * a)) & 3;
    if (i != 3)
        w->orient = i;
    else
        w->orient = (0xFFEAD8 >> (2 * c + 8 * (w->quant > 12))) & 3;
/*
 * lut1[b][a] = {
 * ->{ 0, 1, 0, pad },
 *   { 0, 1, X, pad },
 *   { 2, 2, 2, pad }
 * }
 * pad 2  2  2;
 * pad X  1  0;
 * pad 0  1  0 <-
 * -> 11 10 '10 10 '11 11'01 00 '11 00'01 00 => 0xEAF4C4
 *
 * lut2[q>12][c] = {
 * ->{ 0, 2, 1, pad},
 *   { 2, 2, 2, pad}
 * }
 * pad 2  2  2;
 * pad 1  2  0 <-
 * -> 11 10'10 10 '11 01'10 00 => 0xEAD8
 */
}