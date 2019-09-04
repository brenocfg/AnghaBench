#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
struct TYPE_4__ {int quant; int /*<<< orphan*/  gb; TYPE_3__** j_dc_vlc; } ;
typedef  TYPE_1__ IntraX8Context ;

/* Variables and functions */
 int /*<<< orphan*/  DC_VLC_BITS ; 
 int /*<<< orphan*/  DC_VLC_MTD ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 int* dc_index_offset ; 
 int get_bits (int /*<<< orphan*/ ,int) ; 
 int get_vlc2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__** j_dc_vlc ; 

__attribute__((used)) static int x8_get_dc_rlf(IntraX8Context *const w, const int mode,
                         int *const level, int *const final)
{
    int i, e, c;

    av_assert2(mode < 3);
    if (!w->j_dc_vlc[mode]) {
        int table_index = get_bits(w->gb, 3);
        // 4 modes, same table
        w->j_dc_vlc[mode] = &j_dc_vlc[w->quant < 13][table_index];
    }

    i = get_vlc2(w->gb, w->j_dc_vlc[mode]->table, DC_VLC_BITS, DC_VLC_MTD);

    /* (i >= 17) { i -= 17; final =1; } */
    c      = i > 16;
    *final = c;
    i      -= 17 * c;

    if (i <= 0) {
        *level = 0;
        return -i;
    }
    c  = (i + 1) >> 1; // hackish way to calculate dc_extra_sbits[]
    c -= c > 1;

    e = get_bits(w->gb, c); // get the extra bits
    i = dc_index_offset[i] + (e >> 1);

    e      = -(e & 1);     // 0, 0xffffff
    *level =  (i ^ e) - e; // (i ^ 0) - 0, (i ^ 0xff) - (-1)
    return 0;
}