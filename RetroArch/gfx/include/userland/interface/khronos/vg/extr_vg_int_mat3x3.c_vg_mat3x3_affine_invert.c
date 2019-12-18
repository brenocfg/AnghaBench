#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float** m; } ;
typedef  TYPE_1__ VG_MAT3X3_T ;

/* Variables and functions */
 float recip_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vg_mat3x3_affine_det (TYPE_1__*) ; 
 int /*<<< orphan*/  vg_mat3x3_affine_is_invertible (TYPE_1__*) ; 

void vg_mat3x3_affine_invert(VG_MAT3X3_T *a)
{
   float oo_det;
   float m00, m01, m02, m10;

   vcos_assert(vg_mat3x3_affine_is_invertible(a));

   oo_det = recip_(vg_mat3x3_affine_det(a));
   m00 = a->m[0][0];
   m01 = a->m[0][1];
   m02 = a->m[0][2];
   m10 = a->m[1][0];

   a->m[0][0] = a->m[1][1] * oo_det;
   a->m[0][1] = -m01 * oo_det;
   a->m[0][2] = ((a->m[1][2] * m01) - (a->m[1][1] * m02)) * oo_det;

   a->m[1][0] = -m10 * oo_det;
   a->m[1][1] = m00 * oo_det;
   a->m[1][2] = ((m10 * m02) - (a->m[1][2] * m00)) * oo_det;

   a->m[2][0] = 0.0f;
   a->m[2][1] = 0.0f;
   a->m[2][2] = 1.0f;
}