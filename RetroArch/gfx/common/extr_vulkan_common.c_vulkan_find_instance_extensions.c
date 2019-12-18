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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  VkExtensionProperties ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 scalar_t__ VK_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ vkEnumerateInstanceExtensionProperties (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_find_extensions (char const**,unsigned int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool vulkan_find_instance_extensions(const char **exts, unsigned num_exts)
{
   uint32_t property_count;
   bool ret                          = true;
   VkExtensionProperties *properties = NULL;

   if (vkEnumerateInstanceExtensionProperties(NULL, &property_count, NULL) != VK_SUCCESS)
      return false;

   properties = (VkExtensionProperties*)malloc(property_count * sizeof(*properties));
   if (!properties)
   {
      ret = false;
      goto end;
   }

   if (vkEnumerateInstanceExtensionProperties(NULL, &property_count, properties) != VK_SUCCESS)
   {
      ret = false;
      goto end;
   }

   if (!vulkan_find_extensions(exts, num_exts, properties, property_count))
   {
      RARCH_ERR("[Vulkan]: Could not find instance extensions. Will attempt without them.\n");
      ret = false;
      goto end;
   }

end:
   free(properties);
   return ret;
}