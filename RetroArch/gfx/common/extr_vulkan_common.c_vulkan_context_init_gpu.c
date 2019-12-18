#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
union string_list_elem_attr {int /*<<< orphan*/  member_0; } ;
typedef  int uint32_t ;
struct TYPE_9__ {int vulkan_gpu_index; } ;
struct TYPE_11__ {TYPE_1__ ints; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_10__ {void* gpu; int /*<<< orphan*/  instance; } ;
struct TYPE_12__ {TYPE_2__ context; } ;
typedef  TYPE_4__ gfx_ctx_vulkan_data_t ;
struct TYPE_13__ {int /*<<< orphan*/  deviceName; } ;
typedef  TYPE_5__ VkPhysicalDeviceProperties ;
typedef  void* VkPhysicalDevice ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_CTX_VULKAN_API ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,int,...) ; 
 int /*<<< orphan*/  RARCH_WARN (char*,size_t) ; 
 scalar_t__ VK_SUCCESS ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  free (void**) ; 
 int /*<<< orphan*/  string_list_append (scalar_t__,int /*<<< orphan*/ ,union string_list_elem_attr) ; 
 int /*<<< orphan*/  string_list_free (scalar_t__) ; 
 scalar_t__ string_list_new () ; 
 int /*<<< orphan*/  video_driver_set_gpu_api_devices (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vkEnumeratePhysicalDevices (int /*<<< orphan*/ ,int*,void**) ; 
 int /*<<< orphan*/  vkGetPhysicalDeviceProperties (void*,TYPE_5__*) ; 
 scalar_t__ vulkan_gpu_list ; 

__attribute__((used)) static bool vulkan_context_init_gpu(gfx_ctx_vulkan_data_t *vk)
{
   unsigned i;
   uint32_t gpu_count               = 0;
   VkPhysicalDevice *gpus           = NULL;
   union string_list_elem_attr attr = {0};
   settings_t *settings             = config_get_ptr();

   if (vkEnumeratePhysicalDevices(vk->context.instance,
            &gpu_count, NULL) != VK_SUCCESS)
   {
      RARCH_ERR("[Vulkan]: Failed to enumerate physical devices.\n");
      return false;
   }

   gpus = (VkPhysicalDevice*)calloc(gpu_count, sizeof(*gpus));
   if (!gpus)
   {
      RARCH_ERR("[Vulkan]: Failed to enumerate physical devices.\n");
      return false;
   }

   if (vkEnumeratePhysicalDevices(vk->context.instance,
            &gpu_count, gpus) != VK_SUCCESS)
   {
      RARCH_ERR("[Vulkan]: Failed to enumerate physical devices.\n");
      free(gpus);
      return false;
   }

   if (gpu_count < 1)
   {
      RARCH_ERR("[Vulkan]: Failed to enumerate Vulkan physical device.\n");
      free(gpus);
      return false;
   }

   if (vulkan_gpu_list)
      string_list_free(vulkan_gpu_list);

   vulkan_gpu_list = string_list_new();

   for (i = 0; i < gpu_count; i++)
   {
      VkPhysicalDeviceProperties gpu_properties;

      vkGetPhysicalDeviceProperties(gpus[i],
            &gpu_properties);

      RARCH_LOG("[Vulkan]: Found GPU at index %d: %s\n", i, gpu_properties.deviceName);

      string_list_append(vulkan_gpu_list, gpu_properties.deviceName, attr);
   }

   video_driver_set_gpu_api_devices(GFX_CTX_VULKAN_API, vulkan_gpu_list);

   if (0 <= settings->ints.vulkan_gpu_index && settings->ints.vulkan_gpu_index < (int)gpu_count)
   {
      RARCH_LOG("[Vulkan]: Using GPU index %d.\n", settings->ints.vulkan_gpu_index);
      vk->context.gpu = gpus[settings->ints.vulkan_gpu_index];
   }
   else
   {
      RARCH_WARN("[Vulkan]: Invalid GPU index %d, using first device found.\n", settings->ints.vulkan_gpu_index);
      vk->context.gpu = gpus[0];
   }

   free(gpus);
   return true;
}