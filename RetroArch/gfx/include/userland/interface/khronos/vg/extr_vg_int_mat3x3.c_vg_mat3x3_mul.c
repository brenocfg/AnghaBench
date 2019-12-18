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
typedef  int uint32_t ;
struct TYPE_5__ {int** m; } ;
typedef  TYPE_1__ VG_MAT3X3_T ;

/* Variables and functions */

void vg_mat3x3_mul(VG_MAT3X3_T *a, const VG_MAT3X3_T *b, const VG_MAT3X3_T *c)
{
   uint32_t j, i;
   for (j = 0; j != 3; ++j) {
      for (i = 0; i != 3; ++i) {
         a->m[j][i] =
            (b->m[j][0] * c->m[0][i]) +
            (b->m[j][1] * c->m[1][i]) +
            (b->m[j][2] * c->m[2][i]);
      }
   }
}