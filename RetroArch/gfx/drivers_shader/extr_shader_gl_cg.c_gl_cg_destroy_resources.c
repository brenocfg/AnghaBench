#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* shader; int /*<<< orphan*/  lut_textures; } ;
typedef  TYPE_1__ cg_shader_data_t ;
struct TYPE_4__ {scalar_t__ luts; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  glDeleteTextures (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_cg_deinit_progs (void*) ; 
 int /*<<< orphan*/  gl_cg_reset_attrib (void*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gl_cg_destroy_resources(void *data)
{
   cg_shader_data_t *cg = (cg_shader_data_t*)data;
   if (!cg)
      return;

   gl_cg_reset_attrib(data);

   gl_cg_deinit_progs(data);

   if (cg->shader && cg->shader->luts)
   {
      glDeleteTextures(cg->shader->luts, cg->lut_textures);
      memset(cg->lut_textures, 0, sizeof(cg->lut_textures));
   }

   free(cg->shader);
   cg->shader = NULL;
}