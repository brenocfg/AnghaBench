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
 scalar_t__ EPS ; 
 scalar_t__ absf_ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vg_mat3x3_affine_det (int /*<<< orphan*/  const*) ; 

bool vg_mat3x3_affine_is_invertible(const VG_MAT3X3_T *a)
{
   return absf_(vg_mat3x3_affine_det(a)) >= EPS;
}