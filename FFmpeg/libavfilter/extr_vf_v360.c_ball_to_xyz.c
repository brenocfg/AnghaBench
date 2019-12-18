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
typedef  int /*<<< orphan*/  V360Context ;

/* Variables and functions */
 float hypotf (float const,float const) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void ball_to_xyz(const V360Context *s,
                        int i, int j, int width, int height,
                        float *vec)
{
    const float x = (2.f * i) / width  - 1.f;
    const float y = (2.f * j) / height - 1.f;
    const float l = hypotf(x, y);

    if (l <= 1.f) {
        const float z = 2.f * l * sqrtf(1.f - l * l);

        vec[0] =  z * x / (l > 0.f ? l : 1.f);
        vec[1] = -z * y / (l > 0.f ? l : 1.f);
        vec[2] = -1.f + 2.f * l * l;
    } else {
        vec[0] =  0.f;
        vec[1] = -1.f;
        vec[2] =  0.f;
    }
}