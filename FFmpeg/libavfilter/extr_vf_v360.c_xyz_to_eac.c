#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int* in_cubemap_face_order; } ;
typedef  TYPE_1__ V360Context ;

/* Variables and functions */
 float M_2_PI ; 
 float atanf (float) ; 
 int /*<<< orphan*/  av_clip (int,int /*<<< orphan*/ ,int) ; 
 int floorf (float) ; 
 int /*<<< orphan*/  xyz_to_cube (TYPE_1__ const*,float const*,float*,float*,int*) ; 

__attribute__((used)) static void xyz_to_eac(const V360Context *s,
                       const float *vec, int width, int height,
                       uint16_t us[4][4], uint16_t vs[4][4], float *du, float *dv)
{
    const float pixel_pad = 2;
    const float u_pad = pixel_pad / width;
    const float v_pad = pixel_pad / height;

    float uf, vf;
    int ui, vi;
    int direction, face;
    int u_face, v_face;

    xyz_to_cube(s, vec, &uf, &vf, &direction);

    face = s->in_cubemap_face_order[direction];
    u_face = face % 3;
    v_face = face / 3;

    uf = M_2_PI * atanf(uf) + 0.5f;
    vf = M_2_PI * atanf(vf) + 0.5f;

    // These formulas are inversed from eac_to_xyz ones
    uf = (uf + u_face) * (1.f - 2.f * u_pad) / 3.f + u_pad;
    vf = vf * (0.5f - 2.f * v_pad) + v_pad + 0.5f * v_face;

    uf *= width;
    vf *= height;

    uf -= 0.5f;
    vf -= 0.5f;

    ui = floorf(uf);
    vi = floorf(vf);

    *du = uf - ui;
    *dv = vf - vi;

    for (int i = -1; i < 3; i++) {
        for (int j = -1; j < 3; j++) {
            us[i + 1][j + 1] = av_clip(ui + j, 0, width  - 1);
            vs[i + 1][j + 1] = av_clip(vi + i, 0, height - 1);
        }
    }
}