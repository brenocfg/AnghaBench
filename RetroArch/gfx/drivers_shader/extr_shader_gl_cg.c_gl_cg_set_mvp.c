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
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ math_matrix_4x4 ;
struct TYPE_6__ {size_t active_idx; TYPE_1__* prg; } ;
typedef  TYPE_3__ cg_shader_data_t ;
struct TYPE_4__ {scalar_t__ mvp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgGLSetMatrixParameterfc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gl_cg_set_mvp(void *shader_data,
      const void *mat_data)
{
   cg_shader_data_t *cg = (cg_shader_data_t*)shader_data;
   if (cg && cg->prg[cg->active_idx].mvp)
   {
      const math_matrix_4x4 *mat = (const math_matrix_4x4*)mat_data;
      cgGLSetMatrixParameterfc(cg->prg[cg->active_idx].mvp, mat->data);
      return true;
   }

   return false;
}