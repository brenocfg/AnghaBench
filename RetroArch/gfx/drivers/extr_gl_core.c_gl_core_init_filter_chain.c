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
typedef  int /*<<< orphan*/  gl_core_t ;
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*) ; 
 int RARCH_SHADER_SLANG ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int gl_core_init_default_filter_chain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_core_init_filter_chain_preset (int /*<<< orphan*/ *,char const*) ; 
 char* retroarch_get_shader_preset () ; 
 scalar_t__ string_is_empty (char const*) ; 
 int video_shader_parse_type (char const*) ; 

__attribute__((used)) static bool gl_core_init_filter_chain(gl_core_t *gl)
{
   const char *shader_path     = retroarch_get_shader_preset();
   enum rarch_shader_type type = video_shader_parse_type(shader_path);

   if (string_is_empty(shader_path))
   {
      RARCH_LOG("[GLCore]: Loading stock shader.\n");
      return gl_core_init_default_filter_chain(gl);
   }

   if (type != RARCH_SHADER_SLANG)
   {
      RARCH_WARN("[GLCore]: Only Slang shaders are supported, falling back to stock.\n");
      return gl_core_init_default_filter_chain(gl);
   }

   if (!gl_core_init_filter_chain_preset(gl, shader_path))
      gl_core_init_default_filter_chain(gl);

   return true;
}