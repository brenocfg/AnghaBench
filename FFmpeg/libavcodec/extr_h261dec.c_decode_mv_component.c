#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  table; } ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  H261_MV_VLC_BITS ; 
 int /*<<< orphan*/  get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ h261_mv_vlc ; 
 int* mvmap ; 

__attribute__((used)) static int decode_mv_component(GetBitContext *gb, int v)
{
    int mv_diff = get_vlc2(gb, h261_mv_vlc.table, H261_MV_VLC_BITS, 2);

    /* check if mv_diff is valid */
    if (mv_diff < 0)
        return v;

    mv_diff = mvmap[mv_diff];

    if (mv_diff && !get_bits1(gb))
        mv_diff = -mv_diff;

    v += mv_diff;
    if (v <= -16)
        v += 32;
    else if (v >= 16)
        v -= 32;

    return v;
}