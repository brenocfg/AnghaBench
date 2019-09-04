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

void make_cube_faces(
    float *data, float ao[6][4], float light[6][4],
    int left, int right, int top, int bottom, int front, int back,
    int wleft, int wright, int wtop, int wbottom, int wfront, int wback,
    float x, float y, float z, float n)
{
    static const float positions[6][4][3] = {
        {{-1, -1, -1}, {-1, -1, +1}, {-1, +1, -1}, {-1, +1, +1}},
        {{+1, -1, -1}, {+1, -1, +1}, {+1, +1, -1}, {+1, +1, +1}},
        {{-1, +1, -1}, {-1, +1, +1}, {+1, +1, -1}, {+1, +1, +1}},
        {{-1, -1, -1}, {-1, -1, +1}, {+1, -1, -1}, {+1, -1, +1}},
        {{-1, -1, -1}, {-1, +1, -1}, {+1, -1, -1}, {+1, +1, -1}},
        {{-1, -1, +1}, {-1, +1, +1}, {+1, -1, +1}, {+1, +1, +1}}
    };
    static const float normals[6][3] = {
        {-1, 0, 0},
        {+1, 0, 0},
        {0, +1, 0},
        {0, -1, 0},
        {0, 0, -1},
        {0, 0, +1}
    };
    static const float uvs[6][4][2] = {
        {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
        {{1, 0}, {0, 0}, {1, 1}, {0, 1}},
        {{0, 1}, {0, 0}, {1, 1}, {1, 0}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
        {{1, 0}, {1, 1}, {0, 0}, {0, 1}}
    };
    static const float indices[6][6] = {
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3},
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3},
        {0, 3, 2, 0, 1, 3},
        {0, 3, 1, 0, 2, 3}
    };
    static const float flipped[6][6] = {
        {0, 1, 2, 1, 3, 2},
        {0, 2, 1, 2, 3, 1},
        {0, 1, 2, 1, 3, 2},
        {0, 2, 1, 2, 3, 1},
        {0, 1, 2, 1, 3, 2},
        {0, 2, 1, 2, 3, 1}
    };
    float *d = data;
    float s = 0.0625;
    float a = 0 + 1 / 2048.0;
    float b = s - 1 / 2048.0;
    int faces[6] = {left, right, top, bottom, front, back};
    int tiles[6] = {wleft, wright, wtop, wbottom, wfront, wback};
    for (int i = 0; i < 6; i++) {
        if (faces[i] == 0) {
            continue;
        }
        float du = (tiles[i] % 16) * s;
        float dv = (tiles[i] / 16) * s;
        int flip = ao[i][0] + ao[i][3] > ao[i][1] + ao[i][2];
        for (int v = 0; v < 6; v++) {
            int j = flip ? flipped[i][v] : indices[i][v];
            *(d++) = x + n * positions[i][j][0];
            *(d++) = y + n * positions[i][j][1];
            *(d++) = z + n * positions[i][j][2];
            *(d++) = normals[i][0];
            *(d++) = normals[i][1];
            *(d++) = normals[i][2];
            *(d++) = du + (uvs[i][j][0] ? b : a);
            *(d++) = dv + (uvs[i][j][1] ? b : a);
            *(d++) = ao[i][j];
            *(d++) = light[i][j];
        }
    }
}