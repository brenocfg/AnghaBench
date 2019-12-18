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

/* Variables and functions */

void make_cube_wireframe(float *data, float x, float y, float z, float n) {
    static const float positions[8][3] = {
        {-1, -1, -1},
        {-1, -1, +1},
        {-1, +1, -1},
        {-1, +1, +1},
        {+1, -1, -1},
        {+1, -1, +1},
        {+1, +1, -1},
        {+1, +1, +1}
    };
    static const int indices[24] = {
        0, 1, 0, 2, 0, 4, 1, 3,
        1, 5, 2, 3, 2, 6, 3, 7,
        4, 5, 4, 6, 5, 7, 6, 7
    };
    float *d = data;
    for (int i = 0; i < 24; i++) {
        int j = indices[i];
        *(d++) = x + n * positions[j][0];
        *(d++) = y + n * positions[j][1];
        *(d++) = z + n * positions[j][2];
    }
}