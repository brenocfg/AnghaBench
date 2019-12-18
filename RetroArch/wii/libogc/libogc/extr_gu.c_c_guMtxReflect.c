#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float x; float y; float z; } ;
typedef  TYPE_1__ guVector ;
typedef  float f32 ;
typedef  float** Mtx ;

/* Variables and functions */
 float c_guVecDotProduct (TYPE_1__*,TYPE_1__*) ; 

void c_guMtxReflect(Mtx m,guVector *p,guVector *n)
{
    f32 vxy, vxz, vyz, pdotn;

    vxy   = -2.0f * n->x * n->y;
    vxz   = -2.0f * n->x * n->z;
    vyz   = -2.0f * n->y * n->z;
    pdotn = 2.0f * c_guVecDotProduct(p,n);

    m[0][0] = 1.0f - 2.0f * n->x * n->x;
    m[0][1] = vxy;
    m[0][2] = vxz;
    m[0][3] = pdotn * n->x;

    m[1][0] = vxy;
    m[1][1] = 1.0f - 2.0f * n->y * n->y;
    m[1][2] = vyz;
    m[1][3] = pdotn * n->y;

    m[2][0] = vxz;
    m[2][1] = vyz;
    m[2][2] = 1.0f - 2.0f * n->z * n->z;
    m[2][3] = pdotn * n->z;
}