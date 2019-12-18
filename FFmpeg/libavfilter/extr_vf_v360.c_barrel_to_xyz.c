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
 float M_PI_4 ; 
 float cosf (float const) ; 
 int /*<<< orphan*/  normalize_vector (float*) ; 
 float sinf (float const) ; 

__attribute__((used)) static void barrel_to_xyz(const V360Context *s,
                          int i, int j, int width, int height,
                          float *vec)
{
    const float scale = 0.99f;
    float l_x, l_y, l_z;

    if (i < 4 * width / 5) {
        const float theta_range = M_PI_4;

        const int ew = 4 * width / 5;
        const int eh = height;

        const float phi   = ((2.f * i) / ew - 1.f) * M_PI        / scale;
        const float theta = ((2.f * j) / eh - 1.f) * theta_range / scale;

        const float sin_phi   = sinf(phi);
        const float cos_phi   = cosf(phi);
        const float sin_theta = sinf(theta);
        const float cos_theta = cosf(theta);

        l_x =  cos_theta * sin_phi;
        l_y = -sin_theta;
        l_z = -cos_theta * cos_phi;
    } else {
        const int ew = width  / 5;
        const int eh = height / 2;

        float uf, vf;

        if (j < eh) {   // UP
            uf = 2.f * (i - 4 * ew) / ew  - 1.f;
            vf = 2.f * (j         ) / eh - 1.f;

            uf /= scale;
            vf /= scale;

            l_x =  uf;
            l_y =  1.f;
            l_z = -vf;
        } else {            // DOWN
            uf = 2.f * (i - 4 * ew) / ew - 1.f;
            vf = 2.f * (j -     eh) / eh - 1.f;

            uf /= scale;
            vf /= scale;

            l_x =  uf;
            l_y = -1.f;
            l_z =  vf;
        }
    }

    vec[0] = l_x;
    vec[1] = l_y;
    vec[2] = l_z;

    normalize_vector(vec);
}