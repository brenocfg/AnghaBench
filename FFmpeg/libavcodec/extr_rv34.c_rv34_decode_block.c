#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_9__ {int /*<<< orphan*/  coefficient; TYPE_3__* third_pattern; TYPE_2__* second_pattern; TYPE_1__* first_pattern; } ;
struct TYPE_8__ {int /*<<< orphan*/  table; } ;
struct TYPE_7__ {int /*<<< orphan*/  table; } ;
struct TYPE_6__ {int /*<<< orphan*/  table; } ;
typedef  TYPE_4__ RV34VLC ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  decode_subblock (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_subblock1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  decode_subblock3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int* modulo_three_table ; 

__attribute__((used)) static int rv34_decode_block(int16_t *dst, GetBitContext *gb, RV34VLC *rvlc, int fc, int sc, int q_dc, int q_ac1, int q_ac2)
{
    int code, pattern, has_ac = 1;

    code = get_vlc2(gb, rvlc->first_pattern[fc].table, 9, 2);

    pattern = code & 0x7;

    code >>= 3;

    if (modulo_three_table[code] & 0x3F) {
        decode_subblock3(dst, code, gb, &rvlc->coefficient, q_dc, q_ac1, q_ac2);
    } else {
        decode_subblock1(dst, code, gb, &rvlc->coefficient, q_dc);
        if (!pattern)
            return 0;
        has_ac = 0;
    }

    if(pattern & 4){
        code = get_vlc2(gb, rvlc->second_pattern[sc].table, 9, 2);
        decode_subblock(dst + 4*0+2, code, 0, gb, &rvlc->coefficient, q_ac2);
    }
    if(pattern & 2){ // Looks like coefficients 1 and 2 are swapped for this block
        code = get_vlc2(gb, rvlc->second_pattern[sc].table, 9, 2);
        decode_subblock(dst + 4*2+0, code, 1, gb, &rvlc->coefficient, q_ac2);
    }
    if(pattern & 1){
        code = get_vlc2(gb, rvlc->third_pattern[sc].table, 9, 2);
        decode_subblock(dst + 4*2+2, code, 0, gb, &rvlc->coefficient, q_ac2);
    }
    return has_ac | pattern;
}