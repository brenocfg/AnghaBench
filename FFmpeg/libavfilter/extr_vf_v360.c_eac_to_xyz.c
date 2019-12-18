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
#define  BOTTOM_LEFT 133 
#define  BOTTOM_MIDDLE 132 
#define  BOTTOM_RIGHT 131 
 float M_PI_2 ; 
#define  TOP_LEFT 130 
#define  TOP_MIDDLE 129 
#define  TOP_RIGHT 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 int floorf (float) ; 
 float fmodf (float,float) ; 
 int /*<<< orphan*/  normalize_vector (float*) ; 
 float tanf (float) ; 

__attribute__((used)) static void eac_to_xyz(const V360Context *s,
                       int i, int j, int width, int height,
                       float *vec)
{
    const float pixel_pad = 2;
    const float u_pad = pixel_pad / width;
    const float v_pad = pixel_pad / height;

    int u_face, v_face, face;

    float l_x, l_y, l_z;

    float uf = (i + 0.5f) / width;
    float vf = (j + 0.5f) / height;

    // EAC has 2-pixel padding on faces except between faces on the same row
    // Padding pixels seems not to be stretched with tangent as regular pixels
    // Formulas below approximate original padding as close as I could get experimentally

    // Horizontal padding
    uf = 3.f * (uf - u_pad) / (1.f - 2.f * u_pad);
    if (uf < 0.f) {
        u_face = 0;
        uf -= 0.5f;
    } else if (uf >= 3.f) {
        u_face = 2;
        uf -= 2.5f;
    } else {
        u_face = floorf(uf);
        uf = fmodf(uf, 1.f) - 0.5f;
    }

    // Vertical padding
    v_face = floorf(vf * 2.f);
    vf = (vf - v_pad - 0.5f * v_face) / (0.5f - 2.f * v_pad) - 0.5f;

    if (uf >= -0.5f && uf < 0.5f) {
        uf = tanf(M_PI_2 * uf);
    } else {
        uf = 2.f * uf;
    }
    if (vf >= -0.5f && vf < 0.5f) {
        vf = tanf(M_PI_2 * vf);
    } else {
        vf = 2.f * vf;
    }

    face = u_face + 3 * v_face;

    switch (face) {
    case TOP_LEFT:
        l_x = -1.f;
        l_y = -vf;
        l_z = -uf;
        break;
    case TOP_MIDDLE:
        l_x =  uf;
        l_y = -vf;
        l_z = -1.f;
        break;
    case TOP_RIGHT:
        l_x =  1.f;
        l_y = -vf;
        l_z =  uf;
        break;
    case BOTTOM_LEFT:
        l_x = -vf;
        l_y = -1.f;
        l_z =  uf;
        break;
    case BOTTOM_MIDDLE:
        l_x = -vf;
        l_y =  uf;
        l_z =  1.f;
        break;
    case BOTTOM_RIGHT:
        l_x = -vf;
        l_y =  1.f;
        l_z = -uf;
        break;
    default:
        av_assert0(0);
    }

    vec[0] = l_x;
    vec[1] = l_y;
    vec[2] = l_z;

    normalize_vector(vec);
}