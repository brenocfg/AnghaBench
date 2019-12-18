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

/* Variables and functions */
 float av_clipf (float const,float,float) ; 
 int /*<<< orphan*/  vector_clipf_c_opposite_sign (float*,float const*,float*,float*,int) ; 

__attribute__((used)) static void vector_clipf_c(float *dst, const float *src, int len,
                           float min, float max)
{
    int i;

    if (min < 0 && max > 0) {
        vector_clipf_c_opposite_sign(dst, src, &min, &max, len);
    } else {
        for (i = 0; i < len; i += 8) {
            dst[i]     = av_clipf(src[i], min, max);
            dst[i + 1] = av_clipf(src[i + 1], min, max);
            dst[i + 2] = av_clipf(src[i + 2], min, max);
            dst[i + 3] = av_clipf(src[i + 3], min, max);
            dst[i + 4] = av_clipf(src[i + 4], min, max);
            dst[i + 5] = av_clipf(src[i + 5], min, max);
            dst[i + 6] = av_clipf(src[i + 6], min, max);
            dst[i + 7] = av_clipf(src[i + 7], min, max);
        }
    }
}