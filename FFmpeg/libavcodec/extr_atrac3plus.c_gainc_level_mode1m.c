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
struct TYPE_5__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_4__ {int num_points; int* lev_code; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AtracGainInfo ;
typedef  int /*<<< orphan*/  Atrac3pChanUnitCtx ;

/* Variables and functions */
 TYPE_3__* gain_vlc_tabs ; 
 void* get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void gainc_level_mode1m(GetBitContext *gb,
                                      Atrac3pChanUnitCtx *ctx,
                                      AtracGainInfo *dst)
{
    int i, delta;

    if (dst->num_points > 0)
        dst->lev_code[0] = get_vlc2(gb, gain_vlc_tabs[2].table,
                                    gain_vlc_tabs[2].bits, 1);

    for (i = 1; i < dst->num_points; i++) {
        delta = get_vlc2(gb, gain_vlc_tabs[3].table,
                         gain_vlc_tabs[3].bits, 1);
        dst->lev_code[i] = (dst->lev_code[i - 1] + delta) & 0xF;
    }
}