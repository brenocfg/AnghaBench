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
typedef  int uint32_t ;
struct TYPE_6__ {int code; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** pixel_model3; TYPE_2__ rc; } ;
typedef  TYPE_1__ SCPRContext ;
typedef  TYPE_2__ RangeCoder ;

/* Variables and functions */
 int decode_unit3 (TYPE_1__*,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int decode_units3(SCPRContext * s, uint32_t *red,
                         uint32_t *green, uint32_t *blue,
                         int *cx, int *cx1)
{
    RangeCoder *rc = &s->rc;
    int ret;

    ret = decode_unit3(s, &s->pixel_model3[0][*cx + *cx1], rc->code & 0xFFF, red);
    if (ret < 0)
        return ret;

    *cx1 = (*cx << 6) & 0xFC0;
    *cx = *red >> 2;

    ret = decode_unit3(s, &s->pixel_model3[1][*cx + *cx1], rc->code & 0xFFF, green);
    if (ret < 0)
        return ret;

    *cx1 = (*cx << 6) & 0xFC0;
    *cx = *green >> 2;

    ret = decode_unit3(s, &s->pixel_model3[2][*cx + *cx1], rc->code & 0xFFF, blue);
    if (ret < 0)
        return ret;

    *cx1 = (*cx << 6) & 0xFC0;
    *cx = *blue >> 2;

    return 0;
}