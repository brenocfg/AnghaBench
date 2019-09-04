#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  table; } ;
struct TYPE_4__ {int /*<<< orphan*/  h263_long_vectors; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  MV_VLC_BITS ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_2__ mv_vlc ; 
 int sign_extend (int,int) ; 

int ff_h263_decode_motion(MpegEncContext * s, int pred, int f_code)
{
    int code, val, sign, shift;
    code = get_vlc2(&s->gb, mv_vlc.table, MV_VLC_BITS, 2);

    if (code == 0)
        return pred;
    if (code < 0)
        return 0xffff;

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

    /* modulo decoding */
    if (!s->h263_long_vectors) {
        val = sign_extend(val, 5 + f_code);
    } else {
        /* horrible H.263 long vector mode */
        if (pred < -31 && val < -63)
            val += 64;
        if (pred > 32 && val > 63)
            val -= 64;

    }
    return val;
}