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
struct TYPE_3__ {float h_fov; float v_fov; int /*<<< orphan*/  d_fov; } ;
typedef  TYPE_1__ V360Context ;

/* Variables and functions */
 double FFMIN (int /*<<< orphan*/ ,float) ; 
 double M_PI ; 
 float atan2f (float const,float const) ; 
 float hypotf (float,float) ; 
 float tanf (double) ; 

__attribute__((used)) static void fov_from_dfov(V360Context *s, float w, float h)
{
    const float da = tanf(0.5 * FFMIN(s->d_fov, 359.f) * M_PI / 180.f);
    const float d = hypotf(w, h);

    s->h_fov = atan2f(da * w, d) * 360.f / M_PI;
    s->v_fov = atan2f(da * h, d) * 360.f / M_PI;

    if (s->h_fov < 0.f)
        s->h_fov += 360.f;
    if (s->v_fov < 0.f)
        s->v_fov += 360.f;
}