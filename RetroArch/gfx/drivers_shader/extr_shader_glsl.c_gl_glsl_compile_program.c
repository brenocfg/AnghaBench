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
struct shader_program_info {int /*<<< orphan*/  fragment; int /*<<< orphan*/  vertex; } ;
struct shader_program_glsl_data {scalar_t__ id; void* fprg; void* vprg; } ;
struct TYPE_4__ {struct shader_program_glsl_data* prg; } ;
typedef  TYPE_1__ glsl_shader_data_t ;
typedef  scalar_t__ GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  RARCH_ERR (char*,unsigned int) ; 
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int /*<<< orphan*/  glAttachShader (scalar_t__,void*) ; 
 scalar_t__ glCreateProgram () ; 
 void* glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteShader (void*) ; 
 int /*<<< orphan*/  glUniform1i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (scalar_t__) ; 
 int /*<<< orphan*/  gl_glsl_compile_shader (TYPE_1__*,void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl_glsl_get_uniform (TYPE_1__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  gl_glsl_link_program (scalar_t__) ; 

__attribute__((used)) static bool gl_glsl_compile_program(
      void *data,
      unsigned idx,
      void *program_data,
      struct shader_program_info *program_info)
{
   glsl_shader_data_t *glsl = (glsl_shader_data_t*)data;
   struct shader_program_glsl_data *program = (struct shader_program_glsl_data*)program_data;
   GLuint prog = glCreateProgram();

   if (!program)
      program = &glsl->prg[idx];

   if (!prog)
      goto error;

   if (program_info->vertex)
   {
      RARCH_LOG("[GLSL]: Found GLSL vertex shader.\n");
      program->vprg = glCreateShader(GL_VERTEX_SHADER);

      if (!gl_glsl_compile_shader(
               glsl,
               program->vprg,
               "#define VERTEX\n#define PARAMETER_UNIFORM\n", program_info->vertex))
      {
         RARCH_ERR("Failed to compile vertex shader #%u\n", idx);
         goto error;
      }

      glAttachShader(prog, program->vprg);
   }

   if (program_info->fragment)
   {
      RARCH_LOG("[GLSL]: Found GLSL fragment shader.\n");
      program->fprg = glCreateShader(GL_FRAGMENT_SHADER);
      if (!gl_glsl_compile_shader(glsl, program->fprg,
               "#define FRAGMENT\n#define PARAMETER_UNIFORM\n", program_info->fragment))
      {
         RARCH_ERR("Failed to compile fragment shader #%u\n", idx);
         goto error;
      }

      glAttachShader(prog, program->fprg);
   }

   if (program_info->vertex || program_info->fragment)
   {
      RARCH_LOG("[GLSL]: Linking GLSL program.\n");
      if (!gl_glsl_link_program(prog))
         goto error;

      /* Clean up dead memory. We're not going to relink the program.
       * Detaching first seems to kill some mobile drivers
       * (according to the intertubes anyways). */
      if (program->vprg)
         glDeleteShader(program->vprg);
      if (program->fprg)
         glDeleteShader(program->fprg);
      program->vprg = 0;
      program->fprg = 0;

      glUseProgram(prog);
      glUniform1i(gl_glsl_get_uniform(glsl, prog, "Texture"), 0);
      glUseProgram(0);
   }

   program->id = prog;

   return true;

error:
   RARCH_ERR("Failed to link program #%u.\n", idx);
   program->id = 0;
   return false;
}