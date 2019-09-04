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
struct TYPE_7__ {TYPE_2__** cbp; TYPE_1__* cbppattern; } ;
struct TYPE_6__ {int bits; int /*<<< orphan*/  table; } ;
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_3__ RV34VLC ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 size_t get_bits1 (int /*<<< orphan*/ *) ; 
 int const get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int* modulo_three_table ; 
 int* rv34_count_ones ; 

__attribute__((used)) static int rv34_decode_cbp(GetBitContext *gb, RV34VLC *vlc, int table)
{
    int pattern, code, cbp=0;
    int ones;
    static const int cbp_masks[3] = {0x100000, 0x010000, 0x110000};
    static const int shifts[4] = { 0, 2, 8, 10 };
    const int *curshift = shifts;
    int i, t, mask;

    code = get_vlc2(gb, vlc->cbppattern[table].table, 9, 2);
    pattern = code & 0xF;
    code >>= 4;

    ones = rv34_count_ones[pattern];

    for(mask = 8; mask; mask >>= 1, curshift++){
        if(pattern & mask)
            cbp |= get_vlc2(gb, vlc->cbp[table][ones].table, vlc->cbp[table][ones].bits, 1) << curshift[0];
    }

    for(i = 0; i < 4; i++){
        t = (modulo_three_table[code] >> (6 - 2*i)) & 3;
        if(t == 1)
            cbp |= cbp_masks[get_bits1(gb)] << i;
        if(t == 2)
            cbp |= cbp_masks[2] << i;
    }
    return cbp;
}