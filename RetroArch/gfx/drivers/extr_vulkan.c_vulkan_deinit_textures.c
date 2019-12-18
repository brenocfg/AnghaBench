#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ memory; } ;
struct TYPE_9__ {unsigned int num_swapchain_images; TYPE_4__ default_texture; TYPE_2__* context; TYPE_1__* swapchain; } ;
typedef  TYPE_3__ vk_t ;
struct TYPE_8__ {int /*<<< orphan*/  device; } ;
struct TYPE_7__ {TYPE_4__ texture_optimal; TYPE_4__ texture; } ;

/* Variables and functions */
 scalar_t__ VK_NULL_HANDLE ; 
 int /*<<< orphan*/  vulkan_deinit_samplers (TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_destroy_texture (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void vulkan_deinit_textures(vk_t *vk)
{
   unsigned i;

   vulkan_deinit_samplers(vk);

   for (i = 0; i < vk->num_swapchain_images; i++)
   {
      if (vk->swapchain[i].texture.memory != VK_NULL_HANDLE)
         vulkan_destroy_texture(
               vk->context->device, &vk->swapchain[i].texture);

      if (vk->swapchain[i].texture_optimal.memory != VK_NULL_HANDLE)
         vulkan_destroy_texture(
               vk->context->device, &vk->swapchain[i].texture_optimal);
   }

   if (vk->default_texture.memory != VK_NULL_HANDLE)
      vulkan_destroy_texture(vk->context->device, &vk->default_texture);
}