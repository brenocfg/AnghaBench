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
struct TYPE_4__ {int /*<<< orphan*/  pb; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
typedef  TYPE_1__ MpegEncContext ;
typedef  TYPE_2__ H261Context ;

/* Variables and functions */
 int** ff_h261_mv_tab ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void h261_encode_motion(H261Context *h, int val)
{
    MpegEncContext *const s = &h->s;
    int sign, code;
    if (val == 0) {
        code = 0;
        put_bits(&s->pb, ff_h261_mv_tab[code][1], ff_h261_mv_tab[code][0]);
    } else {
        if (val > 15)
            val -= 32;
        if (val < -16)
            val += 32;
        sign = val < 0;
        code = sign ? -val : val;
        put_bits(&s->pb, ff_h261_mv_tab[code][1], ff_h261_mv_tab[code][0]);
        put_bits(&s->pb, 1, sign);
    }
}