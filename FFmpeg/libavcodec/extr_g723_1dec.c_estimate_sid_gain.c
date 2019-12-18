#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int64_t ;
typedef  int int32_t ;
struct TYPE_3__ {int cur_gain; int sid_gain; } ;
typedef  TYPE_1__ G723_1_ChannelContext ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int INT32_MAX ; 
 int INT32_MIN ; 
 int av_clipl_int32 (int) ; 
 int* cng_bseg ; 
 scalar_t__* cng_filt ; 

__attribute__((used)) static int estimate_sid_gain(G723_1_ChannelContext *p)
{
    int i, shift, seg, seg2, t, val, val_add, x, y;

    shift = 16 - p->cur_gain * 2;
    if (shift > 0) {
        if (p->sid_gain == 0) {
            t = 0;
        } else if (shift >= 31 || (int32_t)((uint32_t)p->sid_gain << shift) >> shift != p->sid_gain) {
            if (p->sid_gain < 0) t = INT32_MIN;
            else                 t = INT32_MAX;
        } else
            t = p->sid_gain * (1 << shift);
    } else if(shift < -31) {
        t = (p->sid_gain < 0) ? -1 : 0;
    }else
        t = p->sid_gain >> -shift;
    x = av_clipl_int32(t * (int64_t)cng_filt[0] >> 16);

    if (x >= cng_bseg[2])
        return 0x3F;

    if (x >= cng_bseg[1]) {
        shift = 4;
        seg   = 3;
    } else {
        shift = 3;
        seg   = (x >= cng_bseg[0]);
    }
    seg2 = FFMIN(seg, 3);

    val     = 1 << shift;
    val_add = val >> 1;
    for (i = 0; i < shift; i++) {
        t = seg * 32 + (val << seg2);
        t *= t;
        if (x >= t)
            val += val_add;
        else
            val -= val_add;
        val_add >>= 1;
    }

    t = seg * 32 + (val << seg2);
    y = t * t - x;
    if (y <= 0) {
        t = seg * 32 + (val + 1 << seg2);
        t = t * t - x;
        val = (seg2 - 1) * 16 + val;
        if (t >= y)
            val++;
    } else {
        t = seg * 32 + (val - 1 << seg2);
        t = t * t - x;
        val = (seg2 - 1) * 16 + val;
        if (t >= y)
            val--;
    }

    return val;
}