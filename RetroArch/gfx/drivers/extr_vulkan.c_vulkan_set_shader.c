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
typedef  int /*<<< orphan*/  vulkan_filter_chain_t ;
struct TYPE_4__ {int /*<<< orphan*/ * filter_chain; } ;
typedef  TYPE_1__ vk_t ;
typedef  enum rarch_shader_type { ____Placeholder_rarch_shader_type } rarch_shader_type ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*,char const*) ; 
 int RARCH_SHADER_SLANG ; 
 int /*<<< orphan*/  RARCH_WARN (char*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 int /*<<< orphan*/  vulkan_filter_chain_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_init_default_filter_chain (TYPE_1__*) ; 
 int /*<<< orphan*/  vulkan_init_filter_chain_preset (TYPE_1__*,char const*) ; 

__attribute__((used)) static bool vulkan_set_shader(void *data,
      enum rarch_shader_type type, const char *path)
{
   vk_t *vk = (vk_t*)data;
   if (!vk)
      return false;

   if (vk->filter_chain)
      vulkan_filter_chain_free((vulkan_filter_chain_t*)vk->filter_chain);
   vk->filter_chain = NULL;

   if (!string_is_empty(path) && type != RARCH_SHADER_SLANG)
   {
      RARCH_WARN("[Vulkan]: Only Slang shaders are supported. Falling back to stock.\n");
      path = NULL;
   }

   if (string_is_empty(path))
   {
      vulkan_init_default_filter_chain(vk);
      return true;
   }

   if (!vulkan_init_filter_chain_preset(vk, path))
   {
      RARCH_ERR("[Vulkan]: Failed to create filter chain: \"%s\". Falling back to stock.\n", path);
      vulkan_init_default_filter_chain(vk);
      return false;
   }

   return true;
}