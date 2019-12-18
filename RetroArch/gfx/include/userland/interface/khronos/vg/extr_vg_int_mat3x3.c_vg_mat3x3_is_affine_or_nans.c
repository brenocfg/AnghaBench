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
struct TYPE_3__ {int /*<<< orphan*/ ** m; } ;
typedef  TYPE_1__ VG_MAT3X3_T ;

/* Variables and functions */
 int /*<<< orphan*/  nan_ne_ (int /*<<< orphan*/ ,float) ; 

bool vg_mat3x3_is_affine_or_nans(const VG_MAT3X3_T *a)
{
   return !nan_ne_(a->m[2][0], 0.0f) && !nan_ne_(a->m[2][1], 0.0f) && !nan_ne_(a->m[2][2], 1.0f);
}