#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int member_0; int member_1; int member_2; } ;
struct TYPE_5__ {int member_0; int member_1; int member_2; } ;
struct TYPE_4__ {int member_0; int member_1; int member_2; } ;

/* Variables and functions */

void make_character_3d(
    float *data, float x, float y, float z, float n, int face, char c)
{
    static const float positions[8][6][3] = {
        {{0, -2, -1}, {0, +2, +1}, {0, +2, -1},
         {0, -2, -1}, {0, -2, +1}, {0, +2, +1}},
        {{0, -2, -1}, {0, +2, +1}, {0, -2, +1},
         {0, -2, -1}, {0, +2, -1}, {0, +2, +1}},
        {{-1, -2, 0}, {+1, +2, 0}, {+1, -2, 0},
         {-1, -2, 0}, {-1, +2, 0}, {+1, +2, 0}},
        {{-1, -2, 0}, {+1, -2, 0}, {+1, +2, 0},
         {-1, -2, 0}, {+1, +2, 0}, {-1, +2, 0}},
        {{-1, 0, +2}, {+1, 0, +2}, {+1, 0, -2},
         {-1, 0, +2}, {+1, 0, -2}, {-1, 0, -2}},
        {{-2, 0, +1}, {+2, 0, -1}, {-2, 0, -1},
         {-2, 0, +1}, {+2, 0, +1}, {+2, 0, -1}},
        {{+1, 0, +2}, {-1, 0, -2}, {-1, 0, +2},
         {+1, 0, +2}, {+1, 0, -2}, {-1, 0, -2}},
        {{+2, 0, -1}, {-2, 0, +1}, {+2, 0, +1},
         {+2, 0, -1}, {-2, 0, -1}, {-2, 0, +1}}
    };
    static const float uvs[8][6][2] = {
        {{0, 0}, {1, 1}, {0, 1}, {0, 0}, {1, 0}, {1, 1}},
        {{1, 0}, {0, 1}, {0, 0}, {1, 0}, {1, 1}, {0, 1}},
        {{1, 0}, {0, 1}, {0, 0}, {1, 0}, {1, 1}, {0, 1}},
        {{0, 0}, {1, 0}, {1, 1}, {0, 0}, {1, 1}, {0, 1}},
        {{0, 0}, {1, 0}, {1, 1}, {0, 0}, {1, 1}, {0, 1}},
        {{0, 1}, {1, 0}, {1, 1}, {0, 1}, {0, 0}, {1, 0}},
        {{0, 1}, {1, 0}, {1, 1}, {0, 1}, {0, 0}, {1, 0}},
        {{0, 1}, {1, 0}, {1, 1}, {0, 1}, {0, 0}, {1, 0}}
    };
    static const float offsets[8][3] = {
        {-1, 0, 0}, {+1, 0, 0}, {0, 0, -1}, {0, 0, +1},
        {0, +1, 0}, {0, +1, 0}, {0, +1, 0}, {0, +1, 0},
    };
    float *d = data;
    float s = 0.0625;
    float pu = s / 5;
    float pv = s / 2.5;
    float u1 = pu;
    float v1 = pv;
    float u2 = s - pu;
    float v2 = s * 2 - pv;
    float p = 0.5;
    int w = c - 32;
    float du = (w % 16) * s;
    float dv = 1 - (w / 16 + 1) * s * 2;
    x += p * offsets[face][0];
    y += p * offsets[face][1];
    z += p * offsets[face][2];
    for (int i = 0; i < 6; i++) {
        *(d++) = x + n * positions[face][i][0];
        *(d++) = y + n * positions[face][i][1];
        *(d++) = z + n * positions[face][i][2];
        *(d++) = du + (uvs[face][i][0] ? u2 : u1);
        *(d++) = dv + (uvs[face][i][1] ? v2 : v1);
    }
}