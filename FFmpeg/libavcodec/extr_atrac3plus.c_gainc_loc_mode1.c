#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  TYPE_1__ VLC ;
struct TYPE_6__ {int num_points; scalar_t__* lev_code; scalar_t__* loc_code; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AtracGainInfo ;
typedef  int /*<<< orphan*/  Atrac3pChanUnitCtx ;

/* Variables and functions */
 TYPE_1__* gain_vlc_tabs ; 
 scalar_t__ get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void gainc_loc_mode1(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                                   AtracGainInfo *dst)
{
    int i;
    VLC *tab;

    if (dst->num_points > 0) {
        /* 1st coefficient is stored directly */
        dst->loc_code[0] = get_bits(gb, 5);

        for (i = 1; i < dst->num_points; i++) {
            /* switch VLC according to the curve direction
             * (ascending/descending) */
            tab              = (dst->lev_code[i] <= dst->lev_code[i - 1])
                               ? &gain_vlc_tabs[7]
                               : &gain_vlc_tabs[9];
            dst->loc_code[i] = dst->loc_code[i - 1] +
                               get_vlc2(gb, tab->table, tab->bits, 1);
        }
    }
}