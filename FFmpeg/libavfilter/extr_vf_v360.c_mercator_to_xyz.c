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
 float M_PI ; 
 float M_PI_2 ; 
 float cosf (float const) ; 
 float expf (float const) ; 
 float sinf (float const) ; 

__attribute__((used)) static void mercator_to_xyz(const V360Context *s,
                            int i, int j, int width, int height,
                            float *vec)
{
    const float phi = ((2.f * i) / width - 1.f) * M_PI + M_PI_2;
    const float y   = ((2.f * j) / height - 1.f) * M_PI;
    const float div = expf(2.f * y) + 1.f;

    const float sin_phi   = sinf(phi);
    const float cos_phi   = cosf(phi);
    const float sin_theta = -2.f * expf(y) / div;
    const float cos_theta = -(expf(2.f * y) - 1.f) / div;

    vec[0] = sin_theta * cos_phi;
    vec[1] = cos_theta;
    vec[2] = sin_theta * sin_phi;
}