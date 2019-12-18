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
typedef  int /*<<< orphan*/  VkPhysicalDevice ;
typedef  int /*<<< orphan*/  VkExtensionProperties ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 scalar_t__ VK_SUCCESS ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,char const**,unsigned int) ; 
 scalar_t__ vkEnumerateDeviceExtensionProperties (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 scalar_t__ vulkan_find_extensions (char const**,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool vulkan_find_device_extensions(VkPhysicalDevice gpu,
      const char **enabled, unsigned *enabled_count,
      const char **exts, unsigned num_exts,
      const char **optional_exts, unsigned num_optional_exts)
{
   uint32_t property_count;
   unsigned i;
   bool ret                          = true;
   VkExtensionProperties *properties = NULL;

   if (vkEnumerateDeviceExtensionProperties(gpu, NULL, &property_count, NULL) != VK_SUCCESS)
      return false;

   properties = (VkExtensionProperties*)malloc(property_count * sizeof(*properties));
   if (!properties)
   {
      ret = false;
      goto end;
   }

   if (vkEnumerateDeviceExtensionProperties(gpu, NULL, &property_count, properties) != VK_SUCCESS)
   {
      ret = false;
      goto end;
   }

   if (!vulkan_find_extensions(exts, num_exts, properties, property_count))
   {
      RARCH_ERR("[Vulkan]: Could not find device extension. Will attempt without it.\n");
      ret = false;
      goto end;
   }

   memcpy((void*)enabled, exts, num_exts * sizeof(*exts));
   *enabled_count = num_exts;

   for (i = 0; i < num_optional_exts; i++)
      if (vulkan_find_extensions(&optional_exts[i], 1, properties, property_count))
         enabled[(*enabled_count)++] = optional_exts[i];

end:
   free(properties);
   return ret;
}