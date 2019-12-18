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
 float sinf (float const) ; 

__attribute__((used)) static void equirect_to_xyz(const V360Context *s,
                            int i, int j, int width, int height,
                            float *vec)
{
    const float phi   = ((2.f * i) / width  - 1.f) * M_PI;
    const float theta = ((2.f * j) / height - 1.f) * M_PI_2;

    const float sin_phi   = sinf(phi);
    const float cos_phi   = cosf(phi);
    const float sin_theta = sinf(theta);
    const float cos_theta = cosf(theta);

    vec[0] =  cos_theta * sin_phi;
    vec[1] = -sin_theta;
    vec[2] = -cos_theta * cos_phi;
}