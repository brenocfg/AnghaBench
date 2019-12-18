#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  enum CeltSpread { ____Placeholder_CeltSpread } CeltSpread ;

/* Variables and functions */
 int CELT_SPREAD_NONE ; 
 float M_PI ; 
 int /*<<< orphan*/  celt_exp_rotation_impl (float*,int,int,float,float) ; 
 float cosf (float) ; 
 float sinf (float) ; 

__attribute__((used)) static inline void celt_exp_rotation(float *X, uint32_t len,
                                     uint32_t stride, uint32_t K,
                                     enum CeltSpread spread, const int encode)
{
    uint32_t stride2 = 0;
    float c, s;
    float gain, theta;
    int i;

    if (2*K >= len || spread == CELT_SPREAD_NONE)
        return;

    gain = (float)len / (len + (20 - 5*spread) * K);
    theta = M_PI * gain * gain / 4;

    c = cosf(theta);
    s = sinf(theta);

    if (len >= stride << 3) {
        stride2 = 1;
        /* This is just a simple (equivalent) way of computing sqrt(len/stride) with rounding.
        It's basically incrementing long as (stride2+0.5)^2 < len/stride. */
        while ((stride2 * stride2 + stride2) * stride + (stride >> 2) < len)
            stride2++;
    }

    len /= stride;
    for (i = 0; i < stride; i++) {
        if (encode) {
            celt_exp_rotation_impl(X + i * len, len, 1, c, -s);
            if (stride2)
                celt_exp_rotation_impl(X + i * len, len, stride2, s, -c);
        } else {
            if (stride2)
                celt_exp_rotation_impl(X + i * len, len, stride2, s, c);
            celt_exp_rotation_impl(X + i * len, len, 1, c, s);
        }
    }
}