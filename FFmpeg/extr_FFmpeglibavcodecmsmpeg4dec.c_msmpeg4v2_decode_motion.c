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
struct TYPE_6__ {int /*<<< orphan*/  table; } ;
struct TYPE_5__ {int /*<<< orphan*/  gb; int /*<<< orphan*/  mb_y; int /*<<< orphan*/  mb_x; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  V2_MV_VLC_BITS ; 
 int /*<<< orphan*/  ff_dlog (TYPE_1__*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ v2_mv_vlc ; 

__attribute__((used)) static int msmpeg4v2_decode_motion(MpegEncContext * s, int pred, int f_code)
{
    int code, val, sign, shift;

    code = get_vlc2(&s->gb, v2_mv_vlc.table, V2_MV_VLC_BITS, 2);
    ff_dlog(s, "MV code %d at %d %d pred: %d\n", code, s->mb_x,s->mb_y, pred);
    if (code < 0)
        return 0xffff;

    if (code == 0)
        return pred;
    sign = get_bits1(&s->gb);
    shift = f_code - 1;
    val = code;
    if (shift) {
        val = (val - 1) << shift;
        val |= get_bits(&s->gb, shift);
        val++;
    }
    if (sign)
        val = -val;

    val += pred;
    if (val <= -64)
        val += 64;
    else if (val >= 64)
        val -= 64;

    return val;
}