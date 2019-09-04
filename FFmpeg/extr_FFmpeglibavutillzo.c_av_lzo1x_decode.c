#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_6__ {int error; int /*<<< orphan*/ * out; int /*<<< orphan*/ * out_end; int /*<<< orphan*/  const* in_end; int /*<<< orphan*/  const* in; int /*<<< orphan*/ * out_start; } ;
typedef  TYPE_1__ LZOContext ;

/* Variables and functions */
 int AV_LZO_ERROR ; 
 int AV_LZO_INPUT_DEPLETED ; 
 int AV_LZO_OUTPUT_FULL ; 
 int GETB (TYPE_1__) ; 
 int /*<<< orphan*/  copy (TYPE_1__*,int) ; 
 int /*<<< orphan*/  copy_backptr (TYPE_1__*,int,int) ; 
 int get_len (TYPE_1__*,int,int) ; 

int av_lzo1x_decode(void *out, int *outlen, const void *in, int *inlen)
{
    int state = 0;
    int x;
    LZOContext c;
    if (*outlen <= 0 || *inlen <= 0) {
        int res = 0;
        if (*outlen <= 0)
            res |= AV_LZO_OUTPUT_FULL;
        if (*inlen <= 0)
            res |= AV_LZO_INPUT_DEPLETED;
        return res;
    }
    c.in      = in;
    c.in_end  = (const uint8_t *)in + *inlen;
    c.out     = c.out_start = out;
    c.out_end = (uint8_t *)out + *outlen;
    c.error   = 0;
    x         = GETB(c);
    if (x > 17) {
        copy(&c, x - 17);
        x = GETB(c);
        if (x < 16)
            c.error |= AV_LZO_ERROR;
    }
    if (c.in > c.in_end)
        c.error |= AV_LZO_INPUT_DEPLETED;
    while (!c.error) {
        int cnt, back;
        if (x > 15) {
            if (x > 63) {
                cnt  = (x >> 5) - 1;
                back = (GETB(c) << 3) + ((x >> 2) & 7) + 1;
            } else if (x > 31) {
                cnt  = get_len(&c, x, 31);
                x    = GETB(c);
                back = (GETB(c) << 6) + (x >> 2) + 1;
            } else {
                cnt   = get_len(&c, x, 7);
                back  = (1 << 14) + ((x & 8) << 11);
                x     = GETB(c);
                back += (GETB(c) << 6) + (x >> 2);
                if (back == (1 << 14)) {
                    if (cnt != 1)
                        c.error |= AV_LZO_ERROR;
                    break;
                }
            }
        } else if (!state) {
            cnt = get_len(&c, x, 15);
            copy(&c, cnt + 3);
            x = GETB(c);
            if (x > 15)
                continue;
            cnt  = 1;
            back = (1 << 11) + (GETB(c) << 2) + (x >> 2) + 1;
        } else {
            cnt  = 0;
            back = (GETB(c) << 2) + (x >> 2) + 1;
        }
        copy_backptr(&c, back, cnt + 2);
        state =
        cnt   = x & 3;
        copy(&c, cnt);
        x = GETB(c);
    }
    *inlen = c.in_end - c.in;
    if (c.in > c.in_end)
        *inlen = 0;
    *outlen = c.out_end - c.out;
    return c.error;
}