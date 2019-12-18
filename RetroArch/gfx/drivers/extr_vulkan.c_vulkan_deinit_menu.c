#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* textures_optimal; TYPE_4__* textures; } ;
struct TYPE_8__ {TYPE_1__ menu; TYPE_2__* context; } ;
typedef  TYPE_3__ vk_t ;
struct TYPE_9__ {scalar_t__ memory; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 unsigned int VULKAN_MAX_SWAPCHAIN_IMAGES ; 
 int /*<<< orphan*/  vulkan_destroy_texture (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void vulkan_deinit_menu(vk_t *vk)
{
   unsigned i;
   for (i = 0; i < VULKAN_MAX_SWAPCHAIN_IMAGES; i++)
   {
      if (vk->menu.textures[i].memory)
         vulkan_destroy_texture(
               vk->context->device, &vk->menu.textures[i]);
      if (vk->menu.textures_optimal[i].memory)
         vulkan_destroy_texture(
               vk->context->device, &vk->menu.textures_optimal[i]);
   }
}