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
struct TYPE_3__ {float* flat_range; } ;
typedef  TYPE_1__ V360Context ;

/* Variables and functions */
 int /*<<< orphan*/  normalize_vector (float*) ; 

__attribute__((used)) static void flat_to_xyz(const V360Context *s,
                        int i, int j, int width, int height,
                        float *vec)
{
    const float l_x =  s->flat_range[0] * (2.f * i / width  - 1.f);
    const float l_y = -s->flat_range[1] * (2.f * j / height - 1.f);

    vec[0] =  l_x;
    vec[1] =  l_y;
    vec[2] = -1.f;

    normalize_vector(vec);
}