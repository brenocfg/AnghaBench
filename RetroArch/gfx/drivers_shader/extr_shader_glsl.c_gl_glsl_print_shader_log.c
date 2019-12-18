#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (int /*<<< orphan*/ ,scalar_t__,scalar_t__*,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ malloc (scalar_t__) ; 

__attribute__((used)) static void gl_glsl_print_shader_log(GLuint obj)
{
   char *info_log = NULL;
   GLint max_len, info_len = 0;

   glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &max_len);

   if (max_len == 0)
      return;

   info_log = (char*)malloc(max_len);
   if (!info_log)
      return;

   glGetShaderInfoLog(obj, max_len, &info_len, info_log);

   if (info_len > 0)
      RARCH_LOG("Shader log: %s\n", info_log);

   free(info_log);
}