#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_23__ {struct vk_texture* staging; } ;
struct TYPE_28__ {int /*<<< orphan*/  cmd; TYPE_8__* chain; TYPE_6__ vp; TYPE_5__* context; TYPE_4__ readback; } ;
typedef  TYPE_9__ vk_t ;
struct vk_texture {scalar_t__ memory; int /*<<< orphan*/  buffer; } ;
struct video_viewport {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  region ;
struct TYPE_18__ {int /*<<< orphan*/  dstAccessMask; int /*<<< orphan*/  srcAccessMask; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_10__ VkMemoryBarrier ;
struct TYPE_22__ {int depth; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_21__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_20__ {int layerCount; int /*<<< orphan*/  aspectMask; } ;
struct TYPE_19__ {TYPE_3__ imageExtent; TYPE_2__ imageOffset; TYPE_1__ imageSubresource; } ;
typedef  TYPE_11__ VkBufferImageCopy ;
struct TYPE_26__ {int /*<<< orphan*/  image; } ;
struct TYPE_27__ {TYPE_7__ backbuffer; } ;
struct TYPE_24__ {size_t current_swapchain_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  VK_ACCESS_HOST_READ_BIT ; 
 int /*<<< orphan*/  VK_ACCESS_TRANSFER_WRITE_BIT ; 
 int /*<<< orphan*/  VK_FORMAT_B8G8R8A8_UNORM ; 
 int /*<<< orphan*/  VK_IMAGE_ASPECT_COLOR_BIT ; 
 int /*<<< orphan*/  VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL ; 
 scalar_t__ VK_NULL_HANDLE ; 
 int /*<<< orphan*/  VK_PIPELINE_STAGE_HOST_BIT ; 
 int /*<<< orphan*/  VK_PIPELINE_STAGE_TRANSFER_BIT ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_MEMORY_BARRIER ; 
 int /*<<< orphan*/  VULKAN_TEXTURE_READBACK ; 
 int /*<<< orphan*/  memset (TYPE_11__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkCmdCopyImageToBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_11__*) ; 
 int /*<<< orphan*/  vkCmdPipelineBarrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vk_texture vulkan_create_texture (TYPE_9__*,struct vk_texture*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_viewport_info (TYPE_9__*,struct video_viewport*) ; 

__attribute__((used)) static void vulkan_readback(vk_t *vk)
{
   VkBufferImageCopy region;
   struct vk_texture *staging;
   struct video_viewport vp;
   VkMemoryBarrier barrier = { VK_STRUCTURE_TYPE_MEMORY_BARRIER };

   vulkan_viewport_info(vk, &vp);
   memset(&region, 0, sizeof(region));
   region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
   region.imageSubresource.layerCount = 1;
   region.imageOffset.x               = vp.x;
   region.imageOffset.y               = vp.y;
   region.imageExtent.width           = vp.width;
   region.imageExtent.height          = vp.height;
   region.imageExtent.depth           = 1;

   staging  = &vk->readback.staging[vk->context->current_swapchain_index];
   *staging = vulkan_create_texture(vk,
         staging->memory != VK_NULL_HANDLE ? staging : NULL,
         vk->vp.width, vk->vp.height,
         VK_FORMAT_B8G8R8A8_UNORM, /* Formats don't matter for readback since it's a raw copy. */
         NULL, NULL, VULKAN_TEXTURE_READBACK);

   vkCmdCopyImageToBuffer(vk->cmd, vk->chain->backbuffer.image,
         VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
         staging->buffer,
         1, &region);

   /* Make the data visible to host. */
   barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
   barrier.dstAccessMask = VK_ACCESS_HOST_READ_BIT;
   vkCmdPipelineBarrier(vk->cmd,
         VK_PIPELINE_STAGE_TRANSFER_BIT,
         VK_PIPELINE_STAGE_HOST_BIT, 0,
         1, &barrier, 0, NULL, 0, NULL);
}