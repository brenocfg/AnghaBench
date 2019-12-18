#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct video_coords {int /*<<< orphan*/  color; int /*<<< orphan*/  lut_tex_coord; int /*<<< orphan*/  tex_coord; int /*<<< orphan*/  vertex; } ;
struct TYPE_5__ {size_t active_idx; TYPE_1__* prg; } ;
typedef  TYPE_2__ cg_shader_data_t ;
struct TYPE_4__ {scalar_t__ color; scalar_t__ lut_tex; scalar_t__ tex; scalar_t__ vertex; } ;

/* Variables and functions */
 int /*<<< orphan*/  gl_cg_set_coord_array (scalar_t__,TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool gl_cg_set_coords(void *shader_data,
      const struct video_coords *coords)
{
   cg_shader_data_t *cg = (cg_shader_data_t*)shader_data;

   if (!cg || !coords)
   {
      if (coords)
         return false;
      return true;
   }

   if (cg->prg[cg->active_idx].vertex)
      gl_cg_set_coord_array(cg->prg[cg->active_idx].vertex, cg, coords->vertex, 2);

   if (cg->prg[cg->active_idx].tex)
      gl_cg_set_coord_array(cg->prg[cg->active_idx].tex, cg, coords->tex_coord, 2);

   if (cg->prg[cg->active_idx].lut_tex)
      gl_cg_set_coord_array(cg->prg[cg->active_idx].lut_tex, cg, coords->lut_tex_coord, 2);

   if (cg->prg[cg->active_idx].color)
      gl_cg_set_coord_array(cg->prg[cg->active_idx].color, cg, coords->color, 4);

   return true;
}