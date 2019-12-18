#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vk_t ;
struct vk_texture {scalar_t__ type; int /*<<< orphan*/  layout; int /*<<< orphan*/  image; int /*<<< orphan*/  buffer; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  region ;
typedef  int /*<<< orphan*/  VkCommandBuffer ;
struct TYPE_7__ {int layerCount; int /*<<< orphan*/  aspectMask; } ;
struct TYPE_6__ {int depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {TYPE_2__ imageSubresource; TYPE_1__ imageExtent; } ;
typedef  TYPE_3__ VkBufferImageCopy ;

/* Variables and functions */
 int /*<<< orphan*/  VK_ACCESS_SHADER_READ_BIT ; 
 int /*<<< orphan*/  VK_ACCESS_TRANSFER_WRITE_BIT ; 
 int /*<<< orphan*/  VK_IMAGE_ASPECT_COLOR_BIT ; 
 int /*<<< orphan*/  VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL ; 
 int /*<<< orphan*/  VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL ; 
 int /*<<< orphan*/  VK_IMAGE_LAYOUT_UNDEFINED ; 
 int /*<<< orphan*/  VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT ; 
 int /*<<< orphan*/  VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT ; 
 int /*<<< orphan*/  VK_PIPELINE_STAGE_TRANSFER_BIT ; 
 scalar_t__ VULKAN_TEXTURE_DYNAMIC ; 
 scalar_t__ VULKAN_TEXTURE_STAGING ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  retro_assert (int) ; 
 int /*<<< orphan*/  vkCmdCopyBufferToImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_3__*) ; 
 int /*<<< orphan*/  vulkan_image_layout_transition (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_sync_texture_to_gpu (int /*<<< orphan*/ *,struct vk_texture*) ; 

void vulkan_copy_staging_to_dynamic(vk_t *vk, VkCommandBuffer cmd,
      struct vk_texture *dynamic,
      struct vk_texture *staging)
{
   VkBufferImageCopy region;

   retro_assert(dynamic->type == VULKAN_TEXTURE_DYNAMIC);
   retro_assert(staging->type == VULKAN_TEXTURE_STAGING);

   vulkan_sync_texture_to_gpu(vk, staging);

   /* We don't have to sync against previous TRANSFER,
    * since we observed the completion by fences.
    *
    * If we have a single texture_optimal, we would need to sync against
    * previous transfers to avoid races.
    *
    * We would also need to optionally maintain extra textures due to
    * changes in resolution, so this seems like the sanest and
    * simplest solution. */
   vulkan_image_layout_transition(vk, cmd, dynamic->image,
         VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
         0, VK_ACCESS_TRANSFER_WRITE_BIT,
         VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
         VK_PIPELINE_STAGE_TRANSFER_BIT);

   memset(&region, 0, sizeof(region));
   region.imageExtent.width           = dynamic->width;
   region.imageExtent.height          = dynamic->height;
   region.imageExtent.depth           = 1;
   region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
   region.imageSubresource.layerCount = 1;

   vkCmdCopyBufferToImage(cmd,
         staging->buffer,
         dynamic->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
         1, &region);

   vulkan_image_layout_transition(vk, cmd,
         dynamic->image,
         VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
         VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
         VK_ACCESS_TRANSFER_WRITE_BIT,
         VK_ACCESS_SHADER_READ_BIT,
         VK_PIPELINE_STAGE_TRANSFER_BIT,
         VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);

   dynamic->layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
}