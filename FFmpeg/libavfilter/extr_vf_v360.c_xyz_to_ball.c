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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {float const* input_mirror_modifier; } ;
typedef  TYPE_1__ V360Context ;

/* Variables and functions */
 float M_SQRT2 ; 
 int /*<<< orphan*/  av_clip (int,int /*<<< orphan*/ ,int) ; 
 int floorf (float) ; 
 float hypotf (float const,float const) ; 
 float sqrtf (float) ; 

__attribute__((used)) static void xyz_to_ball(const V360Context *s,
                        const float *vec, int width, int height,
                        uint16_t us[4][4], uint16_t vs[4][4], float *du, float *dv)
{
    const float l = hypotf(vec[0], vec[1]);
    const float r = sqrtf(1.f + vec[2]) / M_SQRT2;
    float uf, vf;
    int ui, vi;

    uf = (1.f + r * vec[0] * s->input_mirror_modifier[0] / (l > 0.f ? l : 1.f)) * width  * 0.5f;
    vf = (1.f - r * vec[1] * s->input_mirror_modifier[1] / (l > 0.f ? l : 1.f)) * height * 0.5f;

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