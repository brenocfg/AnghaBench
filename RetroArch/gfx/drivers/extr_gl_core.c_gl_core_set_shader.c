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
struct TYPE_5__ {int /*<<< orphan*/ * filter_chain; } ;
typedef  TYPE_1__ gl_core_t ;
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,char const*) ; 
 int RARCH_SHADER_SLANG ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 int /*<<< orphan*/  gl_core_context_bind_hw_render (TYPE_1__*,int) ; 
 int /*<<< orphan*/  gl_core_filter_chain_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gl_core_init_default_filter_chain (TYPE_1__*) ; 
 int /*<<< orphan*/  gl_core_init_filter_chain_preset (TYPE_1__*,char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 

__attribute__((used)) static bool gl_core_set_shader(void *data,
                               enum rarch_shader_type type, const char *path)
{
   gl_core_t *gl = (gl_core_t *)data;
   if (!gl)
      return false;

   gl_core_context_bind_hw_render(gl, false);

   if (gl->filter_chain)
      gl_core_filter_chain_free(gl->filter_chain);
   gl->filter_chain = NULL;

   if (!string_is_empty(path) && type != RARCH_SHADER_SLANG)
   {
      RARCH_WARN("[GLCore]: Only Slang shaders are supported. Falling back to stock.\n");
      path = NULL;
   }

   if (string_is_empty(path))
   {
      gl_core_init_default_filter_chain(gl);
      gl_core_context_bind_hw_render(gl, true);
      return true;
   }

   if (!gl_core_init_filter_chain_preset(gl, path))
   {
      RARCH_ERR("[GLCore]: Failed to create filter chain: \"%s\". Falling back to stock.\n", path);
      gl_core_init_default_filter_chain(gl);
      gl_core_context_bind_hw_render(gl, true);
      return false;
   }

   gl_core_context_bind_hw_render(gl, true);
   return true;
}