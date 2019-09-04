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
struct TYPE_3__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ MpegEncContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int** ff_mpeg12_mbMotionVectorTable ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int,int) ; 
 int sign_extend (int,int) ; 

__attribute__((used)) static void mpeg1_encode_motion(MpegEncContext *s, int val, int f_or_b_code)
{
    if (val == 0) {
        /* zero vector */
        put_bits(&s->pb,
                 ff_mpeg12_mbMotionVectorTable[0][1],
                 ff_mpeg12_mbMotionVectorTable[0][0]);
    } else {
        int code, sign, bits;
        int bit_size = f_or_b_code - 1;
        int range    = 1 << bit_size;
        /* modulo encoding */
        val = sign_extend(val, 5 + bit_size);

        if (val >= 0) {
            val--;
            code = (val >> bit_size) + 1;
            bits = val & (range - 1);
            sign = 0;
        } else {
            val = -val;
            val--;
            code = (val >> bit_size) + 1;
            bits = val & (range - 1);
            sign = 1;
        }

        av_assert2(code > 0 && code <= 16);

        put_bits(&s->pb,
                 ff_mpeg12_mbMotionVectorTable[code][1],
                 ff_mpeg12_mbMotionVectorTable[code][0]);

        put_bits(&s->pb, 1, sign);
        if (bit_size > 0)
            put_bits(&s->pb, bit_size, bits);
    }
}