#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* vertex; char* fragment; } ;
struct TYPE_9__ {unsigned int path; TYPE_2__ string; } ;
struct video_shader_pass {TYPE_3__ source; } ;
struct shader_program_info {char const* vertex; char const* fragment; int is_file; } ;
struct shader_program_glsl_data {int dummy; } ;
struct TYPE_10__ {TYPE_1__* shader; } ;
typedef  TYPE_4__ glsl_shader_data_t ;
struct TYPE_7__ {unsigned int passes; int /*<<< orphan*/ * pass; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  gl_glsl_compile_program (TYPE_4__*,unsigned int,struct shader_program_glsl_data*,struct shader_program_info*) ; 
 int /*<<< orphan*/  gl_glsl_load_source_path (struct video_shader_pass*,unsigned int) ; 
 int /*<<< orphan*/  string_is_empty (unsigned int) ; 

__attribute__((used)) static bool gl_glsl_compile_programs(
      glsl_shader_data_t *glsl, struct shader_program_glsl_data *program)
{
   unsigned i;

   for (i = 0; i < glsl->shader->passes; i++)
   {
      struct shader_program_info shader_prog_info;
      const char *vertex           = NULL;
      const char *fragment         = NULL;
      struct video_shader_pass *pass = (struct video_shader_pass*)
         &glsl->shader->pass[i];

      if (!pass)
         continue;

      /* If we load from GLSLP (preset),
       * load the file here.
       */
      if (     !string_is_empty(pass->source.path)
            && !gl_glsl_load_source_path(pass, pass->source.path))
      {
         RARCH_ERR("Failed to load GLSL shader: %s.\n",
               pass->source.path);
         return false;
      }

      vertex                    = pass->source.string.vertex;
      fragment                  = pass->source.string.fragment;

      shader_prog_info.vertex   = vertex;
      shader_prog_info.fragment = fragment;
      shader_prog_info.is_file  = false;

      if (!gl_glsl_compile_program(glsl, i,
            &program[i],
            &shader_prog_info))
      {
         RARCH_ERR("Failed to create GL program #%u.\n", i);
         return false;
      }
   }

   return true;
}