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
struct TYPE_3__ {int edges; int mb_x; int mb_y; int mb_width; int chroma_orient; int* prediction_table; scalar_t__ raw_orient; } ;
typedef  TYPE_1__ IntraX8Context ;

/* Variables and functions */

__attribute__((used)) static void x8_get_prediction_chroma(IntraX8Context *const w)
{
    w->edges  = 1 * !(w->mb_x >> 1);
    w->edges |= 2 * !(w->mb_y >> 1);
    w->edges |= 4 * (w->mb_x >= (2 * w->mb_width - 1)); // mb_x for chroma would always be odd

    w->raw_orient = 0;
    // lut_co[8] = {inv,4,8,8, inv,4,8,8} <- => {1,1,0,0;1,1,0,0} => 0xCC
    if (w->edges & 3) {
        w->chroma_orient = 4 << ((0xCC >> w->edges) & 1);
        return;
    }
    // block[x - 1][y | 1 - 1)]
    w->chroma_orient = (w->prediction_table[2 * w->mb_x - 2] & 0x03) << 2;
}