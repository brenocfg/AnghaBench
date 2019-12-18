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
typedef  scalar_t__ GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_NUM_EXTENSIONS ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ glGetString (int /*<<< orphan*/ ) ; 
 scalar_t__ glGetStringi (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gl_query_core_context_in_use () ; 
 scalar_t__ strstr (char const*,char const*) ; 

bool gl_query_extension(const char *ext)
{
   bool ret = false;

   if (gl_query_core_context_in_use())
   {
#ifdef GL_NUM_EXTENSIONS
      GLint i;
      GLint exts = 0;
      glGetIntegerv(GL_NUM_EXTENSIONS, &exts);
      for (i = 0; i < exts; i++)
      {
         const char *str = (const char*)glGetStringi(GL_EXTENSIONS, i);
         if (str && strstr(str, ext))
         {
            ret = true;
            break;
         }
      }
#endif
   }
   else
   {
      const char *str = (const char*)glGetString(GL_EXTENSIONS);
      ret = str && strstr(str, ext);
   }

   return ret;
}