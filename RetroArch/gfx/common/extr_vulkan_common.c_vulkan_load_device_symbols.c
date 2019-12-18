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
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct TYPE_5__ {TYPE_1__ context; } ;
typedef  TYPE_2__ gfx_ctx_vulkan_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  VULKAN_SYMBOL_WRAPPER_LOAD_DEVICE_EXTENSION_SYMBOL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vkAcquireNextImageKHR ; 
 int /*<<< orphan*/  vkCreateSwapchainKHR ; 
 int /*<<< orphan*/  vkDestroySwapchainKHR ; 
 int /*<<< orphan*/  vkGetSwapchainImagesKHR ; 
 int /*<<< orphan*/  vkQueuePresentKHR ; 
 int /*<<< orphan*/  vulkan_symbol_wrapper_load_core_device_symbols (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vulkan_load_device_symbols(gfx_ctx_vulkan_data_t *vk)
{
   if (!vulkan_symbol_wrapper_load_core_device_symbols(vk->context.device))
      return false;

   VULKAN_SYMBOL_WRAPPER_LOAD_DEVICE_EXTENSION_SYMBOL(vk->context.device, vkCreateSwapchainKHR);
   VULKAN_SYMBOL_WRAPPER_LOAD_DEVICE_EXTENSION_SYMBOL(vk->context.device, vkDestroySwapchainKHR);
   VULKAN_SYMBOL_WRAPPER_LOAD_DEVICE_EXTENSION_SYMBOL(vk->context.device, vkGetSwapchainImagesKHR);
   VULKAN_SYMBOL_WRAPPER_LOAD_DEVICE_EXTENSION_SYMBOL(vk->context.device, vkAcquireNextImageKHR);
   VULKAN_SYMBOL_WRAPPER_LOAD_DEVICE_EXTENSION_SYMBOL(vk->context.device, vkQueuePresentKHR);
   return true;
}