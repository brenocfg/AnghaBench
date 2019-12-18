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
typedef  int /*<<< orphan*/  vk_t ;
struct vk_texture {scalar_t__ layout; int type; int /*<<< orphan*/  image; } ;
typedef  int /*<<< orphan*/  VkCommandBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  VK_ACCESS_HOST_WRITE_BIT ; 
 int /*<<< orphan*/  VK_ACCESS_SHADER_READ_BIT ; 
 scalar_t__ VK_IMAGE_LAYOUT_GENERAL ; 
 scalar_t__ VK_IMAGE_LAYOUT_PREINITIALIZED ; 
 int /*<<< orphan*/  VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT ; 
 int /*<<< orphan*/  VK_PIPELINE_STAGE_HOST_BIT ; 
#define  VULKAN_TEXTURE_STREAMED 128 
 int /*<<< orphan*/  retro_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_image_layout_transition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vulkan_transition_texture(vk_t *vk, VkCommandBuffer cmd, struct vk_texture *texture)
{
   if (!texture->image)
      return;

   /* Transition to GENERAL layout for linear streamed textures.
    * We're using linear textures here, so only
    * GENERAL layout is supported.
    * If we're already in GENERAL, add a host -> shader read memory barrier
    * to invalidate texture caches.
    */
   if (texture->layout != VK_IMAGE_LAYOUT_PREINITIALIZED &&
       texture->layout != VK_IMAGE_LAYOUT_GENERAL)
      return;

   switch (texture->type)
   {
      case VULKAN_TEXTURE_STREAMED:
         vulkan_image_layout_transition(vk, cmd, texture->image,
               texture->layout, VK_IMAGE_LAYOUT_GENERAL,
               VK_ACCESS_HOST_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT,
               VK_PIPELINE_STAGE_HOST_BIT,
               VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);
         break;

      default:
         retro_assert(0 && "Attempting to transition invalid texture type.\n");
         break;
   }
   texture->layout = VK_IMAGE_LAYOUT_GENERAL;
}