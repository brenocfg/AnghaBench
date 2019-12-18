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
typedef  int /*<<< orphan*/  log ;
struct TYPE_5__ {char** attribute_names; int* attribute_locations; char** uniform_names; int* uniform_locations; void* vs; void* fs; int /*<<< orphan*/  program; struct TYPE_5__* fragment_source; struct TYPE_5__* vertex_source; } ;
typedef  TYPE_1__ RASPITEXUTIL_SHADER_PROGRAM_T ;
typedef  int /*<<< orphan*/  GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int SHADER_MAX_ATTRIBUTES ; 
 int SHADER_MAX_UNIFORMS ; 
 char* VCOS_FUNCTION ; 
 int /*<<< orphan*/  glAttachShader (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  glCompileShader (void*) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 void* glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glDeleteShader (void*) ; 
 int glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glGetProgramInfoLog (int /*<<< orphan*/ ,int,int*,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (void*,int,int*,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glLinkProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShaderSource (void*,int,TYPE_1__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_assert (TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_log_error (char*,...) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,char*,int) ; 

int raspitexutil_build_shader_program(RASPITEXUTIL_SHADER_PROGRAM_T *p)
{
   GLint status;
   int i = 0;
   char log[1024];
   int logLen = 0;
   vcos_assert(p);
   vcos_assert(p->vertex_source);
   vcos_assert(p->fragment_source);

   if (! (p && p->vertex_source && p->fragment_source))
      goto fail;

   p->vs = p->fs = 0;

   p->vs = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(p->vs, 1, &p->vertex_source, NULL);
   glCompileShader(p->vs);
   glGetShaderiv(p->vs, GL_COMPILE_STATUS, &status);
   if (! status)
   {
      glGetShaderInfoLog(p->vs, sizeof(log), &logLen, log);
      vcos_log_error("Program info log %s", log);
      goto fail;
   }

   p->fs = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(p->fs, 1, &p->fragment_source, NULL);
   glCompileShader(p->fs);

   glGetShaderiv(p->fs, GL_COMPILE_STATUS, &status);
   if (! status)
   {
      glGetShaderInfoLog(p->fs, sizeof(log), &logLen, log);
      vcos_log_error("Program info log %s", log);
      goto fail;
   }

   p->program = glCreateProgram();
   glAttachShader(p->program, p->vs);
   glAttachShader(p->program, p->fs);
   glLinkProgram(p->program);
   glGetProgramiv(p->program, GL_LINK_STATUS, &status);
   if (! status)
   {
      vcos_log_error("Failed to link shader program");
      glGetProgramInfoLog(p->program, sizeof(log), &logLen, log);
      vcos_log_error("Program info log %s", log);
      goto fail;
   }

   for (i = 0; i < SHADER_MAX_ATTRIBUTES; ++i)
   {
      if (! p->attribute_names[i])
         break;
      p->attribute_locations[i] = glGetAttribLocation(p->program, p->attribute_names[i]);
      if (p->attribute_locations[i] == -1)
      {
         vcos_log_error("Failed to get location for attribute %s",
                        p->attribute_names[i]);
         goto fail;
      }
      else
      {
         vcos_log_trace("Attribute for %s is %d",
                        p->attribute_names[i], p->attribute_locations[i]);
      }
   }

   for (i = 0; i < SHADER_MAX_UNIFORMS; ++i)
   {
      if (! p->uniform_names[i])
         break;
      p->uniform_locations[i] = glGetUniformLocation(p->program, p->uniform_names[i]);
      if (p->uniform_locations[i] == -1)
      {
         vcos_log_error("Failed to get location for uniform %s",
                        p->uniform_names[i]);
         goto fail;
      }
      else
      {
         vcos_log_trace("Uniform for %s is %d",
                        p->uniform_names[i], p->uniform_locations[i]);
      }
   }

   return 0;

fail:
   vcos_log_error("%s: Failed to build shader program", VCOS_FUNCTION);
   if (p)
   {
      glDeleteProgram(p->program);
      glDeleteShader(p->fs);
      glDeleteShader(p->vs);
   }
   return -1;
}