#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct shader_program_info {int is_file; void* combined; } ;
struct TYPE_4__ {int /*<<< orphan*/ * prg; } ;
typedef  TYPE_1__ cg_shader_data_t ;

/* Variables and functions */
 size_t VIDEO_SHADER_MENU ; 
 size_t VIDEO_SHADER_MENU_2 ; 
 size_t VIDEO_SHADER_MENU_3 ; 
 int /*<<< orphan*/  gl_cg_compile_program (TYPE_1__*,size_t,int /*<<< orphan*/ *,struct shader_program_info*) ; 
 int /*<<< orphan*/  gl_cg_set_program_base_attrib (TYPE_1__*,size_t) ; 
 void* stock_xmb_ribbon_simple ; 
 void* stock_xmb_snow ; 

__attribute__((used)) static void gl_cg_init_menu_shaders(void *data)
{
   struct shader_program_info shader_prog_info;
   cg_shader_data_t *cg = (cg_shader_data_t*)data;

   if (!cg)
      return;

#ifdef HAVE_SHADERPIPELINE
   shader_prog_info.combined = stock_xmb_ribbon_simple;
   shader_prog_info.is_file  = false;

   gl_cg_compile_program(
         cg,
         VIDEO_SHADER_MENU,
         &cg->prg[VIDEO_SHADER_MENU],
         &shader_prog_info);
   gl_cg_set_program_base_attrib(cg, VIDEO_SHADER_MENU);

   shader_prog_info.combined = stock_xmb_ribbon_simple;
   shader_prog_info.is_file  = false;

   gl_cg_compile_program(
         cg,
         VIDEO_SHADER_MENU_2,
         &cg->prg[VIDEO_SHADER_MENU_2],
         &shader_prog_info);
   gl_cg_set_program_base_attrib(cg, VIDEO_SHADER_MENU_2);

   shader_prog_info.combined = stock_xmb_snow;
   shader_prog_info.is_file  = false;

   gl_cg_compile_program(
         cg,
         VIDEO_SHADER_MENU_3,
         &cg->prg[VIDEO_SHADER_MENU_3],
         &shader_prog_info);
   gl_cg_set_program_base_attrib(cg, VIDEO_SHADER_MENU_3);
#endif
}