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
 float const M_SQRT2 ; 
 int /*<<< orphan*/  normalize_vector (float*) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void hammer_to_xyz(const V360Context *s,
                          int i, int j, int width, int height,
                          float *vec)
{
    const float x = ((2.f * i) / width  - 1.f);
    const float y = ((2.f * j) / height - 1.f);

    const float xx = x * x;
    const float yy = y * y;

    const float z = sqrtf(1.f - xx * 0.5f - yy * 0.5f);

    const float a = M_SQRT2 * x * z;
    const float b = 2.f * z * z - 1.f;

    const float aa = a * a;
    const float bb = b * b;

    const float w = sqrtf(1.f - 2.f * yy * z * z);

    vec[0] =  w * 2.f * a * b / (aa + bb);
    vec[1] = -M_SQRT2 * y * z;
    vec[2] = -w * (bb  - aa) / (aa + bb);

    normalize_vector(vec);
}