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
struct TYPE_4__ {float fout_pad; float out_width; float out_pad; float out_height; } ;
typedef  TYPE_1__ V360Context ;

/* Variables and functions */
 int const ceilf (float const) ; 
 int /*<<< orphan*/  cube_to_xyz (TYPE_1__ const*,float const,float const,int const,float*,float const,float const) ; 
 int floorf (int) ; 

__attribute__((used)) static void cube3x2_to_xyz(const V360Context *s,
                           int i, int j, int width, int height,
                           float *vec)
{
    const float scalew = s->fout_pad > 0 ? 1.f - s->fout_pad / (s->out_width  / 3.f) : 1.f - s->out_pad;
    const float scaleh = s->fout_pad > 0 ? 1.f - s->fout_pad / (s->out_height / 2.f) : 1.f - s->out_pad;

    const float ew = width  / 3.f;
    const float eh = height / 2.f;

    const int u_face = floorf(i / ew);
    const int v_face = floorf(j / eh);
    const int face = u_face + 3 * v_face;

    const int u_shift = ceilf(ew * u_face);
    const int v_shift = ceilf(eh * v_face);
    const int ewi = ceilf(ew * (u_face + 1)) - u_shift;
    const int ehi = ceilf(eh * (v_face + 1)) - v_shift;

    const float uf = 2.f * (i - u_shift + 0.5f) / ewi - 1.f;
    const float vf = 2.f * (j - v_shift + 0.5f) / ehi - 1.f;

    cube_to_xyz(s, uf, vf, face, vec, scalew, scaleh);
}