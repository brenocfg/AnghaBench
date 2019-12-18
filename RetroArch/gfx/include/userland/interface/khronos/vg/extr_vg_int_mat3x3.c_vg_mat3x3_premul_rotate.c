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
typedef  int /*<<< orphan*/  VG_MAT3X3_T ;

/* Variables and functions */
 int /*<<< orphan*/  sin_cos_ (float*,float*,float) ; 
 int /*<<< orphan*/  vg_mat3x3_premul_rotate_sc (int /*<<< orphan*/ *,float,float) ; 

void vg_mat3x3_premul_rotate(VG_MAT3X3_T *a, float angle)
{
   float s, c;
   sin_cos_(&s, &c, angle);
   vg_mat3x3_premul_rotate_sc(a, s, c);
}