#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int member_0; int member_1; int member_2; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADIANS (float) ; 
 int /*<<< orphan*/  mat_apply (float*,float*,int,int,int) ; 
 int /*<<< orphan*/  mat_identity (float*) ; 
 int /*<<< orphan*/  mat_multiply (float*,float*,float*) ; 
 int /*<<< orphan*/  mat_rotate (float*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mat_translate (float*,float,float,float) ; 
 int* plants ; 

void make_plant(
    float *data, float ao, float light,
    float px, float py, float pz, float n, int w, float rotation)
{
    static const float positions[4][4][3] = {
        {{ 0, -1, -1}, { 0, -1, +1}, { 0, +1, -1}, { 0, +1, +1}},
        {{ 0, -1, -1}, { 0, -1, +1}, { 0, +1, -1}, { 0, +1, +1}},
        {{-1, -1,  0}, {-1, +1,  0}, {+1, -1,  0}, {+1, +1,  0}},
        {{-1, -1,  0}, {-1, +1,  0}, {+1, -1,  0}, {+1, +1,  0}}
    };
    static const float normals[4][3] = {
        {-1, 0, 0},
        {+1, 0, 0},
        {0, 0, -1},
        {0, 0, +1}
    };
    static const float uvs[4][4][2] = {
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
        {{1, 0}, {0, 0}, {1, 1}, {0, 1}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{1, 0}, {1, 1}, {0, 0}, {0, 1}}
    };
    static const float indices[4][6] = {
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3},
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3}
    };
    float *d = data;
    float s = 0.0625;
    float a = 0;
    float b = s;
    float du = (plants[w] % 16) * s;
    float dv = (plants[w] / 16) * s;
    for (int i = 0; i < 4; i++) {
        for (int v = 0; v < 6; v++) {
            int j = indices[i][v];
            *(d++) = n * positions[i][j][0];
            *(d++) = n * positions[i][j][1];
            *(d++) = n * positions[i][j][2];
            *(d++) = normals[i][0];
            *(d++) = normals[i][1];
            *(d++) = normals[i][2];
            *(d++) = du + (uvs[i][j][0] ? b : a);
            *(d++) = dv + (uvs[i][j][1] ? b : a);
            *(d++) = ao;
            *(d++) = light;
        }
    }
    float ma[16];
    float mb[16];
    mat_identity(ma);
    mat_rotate(mb, 0, 1, 0, RADIANS(rotation));
    mat_multiply(ma, mb, ma);
    mat_apply(data, ma, 24, 3, 10);
    mat_translate(mb, px, py, pz);
    mat_multiply(ma, mb, ma);
    mat_apply(data, ma, 24, 0, 10);
}