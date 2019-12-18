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
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {float* input_mirror_modifier; scalar_t__ ih_flip; } ;
typedef  TYPE_1__ V360Context ;

/* Variables and functions */
 float const M_PI ; 
 float M_PI_4 ; 
 float asinf (float const) ; 
 float atan2f (float const,float const) ; 
 scalar_t__ av_clip (int,int /*<<< orphan*/ ,int) ; 
 int floorf (float) ; 

__attribute__((used)) static void xyz_to_barrel(const V360Context *s,
                          const float *vec, int width, int height,
                          uint16_t us[4][4], uint16_t vs[4][4], float *du, float *dv)
{
    const float scale = 0.99f;

    const float phi   = atan2f(vec[0], -vec[2]) * s->input_mirror_modifier[0];
    const float theta = asinf(-vec[1]) * s->input_mirror_modifier[1];
    const float theta_range = M_PI_4;

    int ew, eh;
    int u_shift, v_shift;
    float uf, vf;
    int ui, vi;

    if (theta > -theta_range && theta < theta_range) {
        ew = 4 * width / 5;
        eh = height;

        u_shift = s->ih_flip ? width / 5 : 0;
        v_shift = 0;

        uf = (phi   / M_PI        * scale + 1.f) * ew / 2.f;
        vf = (theta / theta_range * scale + 1.f) * eh / 2.f;
    } else {
        ew = width  / 5;
        eh = height / 2;

        u_shift = s->ih_flip ? 0 : 4 * ew;

        if (theta < 0.f) {  // UP
            uf =  vec[0] / vec[1];
            vf = -vec[2] / vec[1];
            v_shift = 0;
        } else {            // DOWN
            uf = -vec[0] / vec[1];
            vf = -vec[2] / vec[1];
            v_shift = eh;
        }

        uf *= s->input_mirror_modifier[0] * s->input_mirror_modifier[1];
        vf *= s->input_mirror_modifier[1];

        uf = 0.5f * ew * (uf * scale + 1.f);
        vf = 0.5f * eh * (vf * scale + 1.f);
    }

    ui = floorf(uf);
    vi = floorf(vf);

    *du = uf - ui;
    *dv = vf - vi;

    for (int i = -1; i < 3; i++) {
        for (int j = -1; j < 3; j++) {
            us[i + 1][j + 1] = u_shift + av_clip(ui + j, 0, ew - 1);
            vs[i + 1][j + 1] = v_shift + av_clip(vi + i, 0, eh - 1);
        }
    }
}