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
#define  ROT_0 131 
#define  ROT_180 130 
#define  ROT_270 129 
#define  ROT_90 128 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rotate_cube_face_inverse(float *uf, float *vf, int rotation)
{
    float tmp;

    switch (rotation) {
    case ROT_0:
        break;
    case ROT_90:
        tmp = -*uf;
        *uf =  *vf;
        *vf =  tmp;
        break;
    case ROT_180:
        *uf = -*uf;
        *vf = -*vf;
        break;
    case ROT_270:
        tmp =  *uf;
        *uf = -*vf;
        *vf =  tmp;
        break;
    default:
        av_assert0(0);
    }
}