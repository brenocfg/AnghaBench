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
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  VkPipelineStageFlags ;
struct TYPE_4__ {int /*<<< orphan*/  layerCount; int /*<<< orphan*/  levelCount; int /*<<< orphan*/  aspectMask; } ;
struct TYPE_5__ {TYPE_1__ subresourceRange; int /*<<< orphan*/  image; void* dstQueueFamilyIndex; void* srcQueueFamilyIndex; void* newLayout; void* oldLayout; scalar_t__ dstAccessMask; scalar_t__ srcAccessMask; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ VkImageMemoryBarrier ;
typedef  void* VkImageLayout ;
typedef  int /*<<< orphan*/  VkImage ;
typedef  int /*<<< orphan*/  VkCommandBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  VK_IMAGE_ASPECT_COLOR_BIT ; 
 int /*<<< orphan*/  VK_REMAINING_ARRAY_LAYERS ; 
 int /*<<< orphan*/  VK_REMAINING_MIP_LEVELS ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER ; 
 int /*<<< orphan*/  vkCmdPipelineBarrier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,TYPE_2__*) ; 

void vulkan_transfer_image_ownership(VkCommandBuffer cmd,
      VkImage image, VkImageLayout layout,
      VkPipelineStageFlags src_stages,
      VkPipelineStageFlags dst_stages,
      uint32_t src_queue_family,
      uint32_t dst_queue_family)
{
   VkImageMemoryBarrier barrier =
   { VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER };

   barrier.srcAccessMask               = 0;
   barrier.dstAccessMask               = 0;
   barrier.oldLayout                   = layout;
   barrier.newLayout                   = layout;
   barrier.srcQueueFamilyIndex         = src_queue_family;
   barrier.dstQueueFamilyIndex         = dst_queue_family;
   barrier.image                       = image;
   barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
   barrier.subresourceRange.levelCount = VK_REMAINING_MIP_LEVELS;
   barrier.subresourceRange.layerCount = VK_REMAINING_ARRAY_LAYERS;

   vkCmdPipelineBarrier(cmd, src_stages, dst_stages,
         false, 0, NULL, 0, NULL, 1, &barrier);
}