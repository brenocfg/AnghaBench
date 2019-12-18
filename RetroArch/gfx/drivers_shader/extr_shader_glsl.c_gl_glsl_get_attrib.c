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
struct TYPE_5__ {TYPE_1__* shader; } ;
typedef  TYPE_2__ glsl_shader_data_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int /*<<< orphan*/  prefix; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ GLint ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * glsl_prefixes ; 
 int /*<<< orphan*/  strlcat (char*,char const*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static GLint gl_glsl_get_attrib(glsl_shader_data_t *glsl,
      GLuint prog, const char *base)
{
   unsigned i;
   GLint loc;
   char buf[80];

   buf[0] = '\0';

   strlcpy(buf, glsl->shader->prefix, sizeof(buf));
   strlcat(buf, base, sizeof(buf));
   loc = glGetUniformLocation(prog, buf);
   if (loc >= 0)
      return loc;

   for (i = 0; i < ARRAY_SIZE(glsl_prefixes); i++)
   {
      strlcpy(buf, glsl_prefixes[i], sizeof(buf));
      strlcat(buf, base, sizeof(buf));
      loc = glGetAttribLocation(prog, buf);
      if (loc >= 0)
         return loc;
   }

   return -1;
}