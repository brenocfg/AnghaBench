#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct shader_program_info {int is_file; void* fragment; void* vertex; } ;
struct TYPE_5__ {int /*<<< orphan*/ * uniforms; TYPE_4__* prg; } ;
typedef  TYPE_1__ glsl_shader_data_t ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 size_t VIDEO_SHADER_MENU ; 
 size_t VIDEO_SHADER_MENU_2 ; 
 size_t VIDEO_SHADER_MENU_3 ; 
 size_t VIDEO_SHADER_MENU_4 ; 
 size_t VIDEO_SHADER_MENU_5 ; 
 size_t VIDEO_SHADER_MENU_6 ; 
 void* core_stock_fragment_xmb ; 
 int /*<<< orphan*/  gl_glsl_compile_program (TYPE_1__*,size_t,TYPE_4__*,struct shader_program_info*) ; 
 int /*<<< orphan*/  gl_glsl_find_uniforms (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gl_query_extension (char*) ; 
 scalar_t__ glsl_core ; 
 void* stock_fragment_xmb ; 
 void* stock_fragment_xmb_bokeh ; 
 void* stock_fragment_xmb_bokeh_core ; 
 void* stock_fragment_xmb_ribbon_simple ; 
 void* stock_fragment_xmb_ribbon_simple_core ; 
 void* stock_fragment_xmb_simple_snow ; 
 void* stock_fragment_xmb_simple_snow_core ; 
 void* stock_fragment_xmb_snow ; 
 void* stock_fragment_xmb_snow_core ; 
 void* stock_fragment_xmb_snowflake ; 
 void* stock_fragment_xmb_snowflake_core ; 
 void* stock_vertex_xmb_ribbon_legacy ; 
 void* stock_vertex_xmb_ribbon_modern ; 
 void* stock_vertex_xmb_ribbon_simple_legacy ; 
 void* stock_vertex_xmb_simple_modern ; 
 void* stock_vertex_xmb_snow ; 
 void* stock_vertex_xmb_snow_core ; 
 void* stock_vertex_xmb_snow_legacy ; 

__attribute__((used)) static void gl_glsl_init_menu_shaders(void *data)
{
#ifdef HAVE_SHADERPIPELINE
   struct shader_program_info shader_prog_info;
   glsl_shader_data_t *glsl = (glsl_shader_data_t*)data;

   if (!glsl)
      return;

#ifdef HAVE_OPENGLES
   if (gl_query_extension("GL_OES_standard_derivatives"))
   {
      shader_prog_info.vertex = glsl_core ? stock_vertex_xmb_ribbon_modern : stock_vertex_xmb_ribbon_legacy;
      shader_prog_info.fragment = glsl_core ? core_stock_fragment_xmb : stock_fragment_xmb;
   }
   else
   {
      shader_prog_info.vertex = stock_vertex_xmb_ribbon_simple_legacy;
      shader_prog_info.fragment = stock_fragment_xmb_ribbon_simple;
   }
#else
   shader_prog_info.vertex = glsl_core ? stock_vertex_xmb_ribbon_modern : stock_vertex_xmb_ribbon_legacy;
   shader_prog_info.fragment = glsl_core ? core_stock_fragment_xmb : stock_fragment_xmb;
#endif
   shader_prog_info.is_file = false;

   RARCH_LOG("[GLSL]: Compiling ribbon shader..\n");
   gl_glsl_compile_program(
         glsl,
         VIDEO_SHADER_MENU,
         &glsl->prg[VIDEO_SHADER_MENU],
         &shader_prog_info);
   gl_glsl_find_uniforms(glsl, 0, glsl->prg[VIDEO_SHADER_MENU].id,
         &glsl->uniforms[VIDEO_SHADER_MENU]);

   shader_prog_info.vertex = glsl_core ? stock_vertex_xmb_simple_modern : stock_vertex_xmb_ribbon_simple_legacy;
   shader_prog_info.fragment = glsl_core ? stock_fragment_xmb_ribbon_simple_core : stock_fragment_xmb_ribbon_simple;

   RARCH_LOG("[GLSL]: Compiling simple ribbon shader..\n");
   gl_glsl_compile_program(
         glsl,
         VIDEO_SHADER_MENU_2,
         &glsl->prg[VIDEO_SHADER_MENU_2],
         &shader_prog_info);
   gl_glsl_find_uniforms(glsl, 0, glsl->prg[VIDEO_SHADER_MENU_2].id,
         &glsl->uniforms[VIDEO_SHADER_MENU_2]);

#if defined(HAVE_OPENGLES)
   shader_prog_info.vertex   = stock_vertex_xmb_snow;
   shader_prog_info.fragment = stock_fragment_xmb_simple_snow;
#else
   shader_prog_info.vertex   = glsl_core ? stock_vertex_xmb_snow_core : stock_vertex_xmb_snow_legacy;
   shader_prog_info.fragment = glsl_core ? stock_fragment_xmb_simple_snow_core : stock_fragment_xmb_simple_snow;
#endif

   RARCH_LOG("[GLSL]: Compiling snow shader..\n");
   gl_glsl_compile_program(
         glsl,
         VIDEO_SHADER_MENU_3,
         &glsl->prg[VIDEO_SHADER_MENU_3],
         &shader_prog_info);
   gl_glsl_find_uniforms(glsl, 0, glsl->prg[VIDEO_SHADER_MENU_3].id,
         &glsl->uniforms[VIDEO_SHADER_MENU_3]);

#if defined(HAVE_OPENGLES)
   shader_prog_info.vertex   = stock_vertex_xmb_snow;
   shader_prog_info.fragment = stock_fragment_xmb_snow;
#else
   shader_prog_info.vertex   = glsl_core ? stock_vertex_xmb_snow_core : stock_vertex_xmb_snow_legacy;
   shader_prog_info.fragment = glsl_core ? stock_fragment_xmb_snow_core : stock_fragment_xmb_snow;
#endif

   RARCH_LOG("[GLSL]: Compiling modern snow shader..\n");
   gl_glsl_compile_program(
         glsl,
         VIDEO_SHADER_MENU_4,
         &glsl->prg[VIDEO_SHADER_MENU_4],
         &shader_prog_info);
   gl_glsl_find_uniforms(glsl, 0, glsl->prg[VIDEO_SHADER_MENU_4].id,
         &glsl->uniforms[VIDEO_SHADER_MENU_4]);

#if defined(HAVE_OPENGLES)
   shader_prog_info.vertex   = stock_vertex_xmb_snow;
   shader_prog_info.fragment = stock_fragment_xmb_bokeh;
#else
   shader_prog_info.vertex   = glsl_core ? stock_vertex_xmb_snow_core  : stock_vertex_xmb_snow_legacy;
   shader_prog_info.fragment = glsl_core ? stock_fragment_xmb_bokeh_core : stock_fragment_xmb_bokeh;
#endif

   RARCH_LOG("[GLSL]: Compiling bokeh shader..\n");
   gl_glsl_compile_program(
         glsl,
         VIDEO_SHADER_MENU_5,
         &glsl->prg[VIDEO_SHADER_MENU_5],
         &shader_prog_info);
   gl_glsl_find_uniforms(glsl, 0, glsl->prg[VIDEO_SHADER_MENU_5].id,
         &glsl->uniforms[VIDEO_SHADER_MENU_5]);

#if defined(HAVE_OPENGLES)
   shader_prog_info.vertex   = stock_vertex_xmb_snow;
   shader_prog_info.fragment = stock_fragment_xmb_snowflake;
#else
   shader_prog_info.vertex   = glsl_core ? stock_vertex_xmb_snow_core : stock_vertex_xmb_snow_legacy;
   shader_prog_info.fragment = glsl_core ? stock_fragment_xmb_snowflake_core : stock_fragment_xmb_snowflake;
#endif

   RARCH_LOG("[GLSL]: Compiling snowflake shader..\n");
   gl_glsl_compile_program(
         glsl,
         VIDEO_SHADER_MENU_6,
         &glsl->prg[VIDEO_SHADER_MENU_6],
         &shader_prog_info);
   gl_glsl_find_uniforms(glsl, 0, glsl->prg[VIDEO_SHADER_MENU_6].id,
         &glsl->uniforms[VIDEO_SHADER_MENU_6]);
#endif
}