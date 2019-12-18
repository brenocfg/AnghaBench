#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vk_texture {int /*<<< orphan*/  layout; int /*<<< orphan*/  view; } ;
struct TYPE_5__ {int dstBinding; int descriptorCount; TYPE_2__* pImageInfo; int /*<<< orphan*/  descriptorType; void* dstSet; TYPE_3__* pBufferInfo; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ VkWriteDescriptorSet ;
typedef  int /*<<< orphan*/  VkSampler ;
typedef  void* VkDeviceSize ;
typedef  int /*<<< orphan*/  VkDevice ;
typedef  void* VkDescriptorSet ;
struct TYPE_6__ {int /*<<< orphan*/  imageLayout; int /*<<< orphan*/  imageView; int /*<<< orphan*/  sampler; } ;
typedef  TYPE_2__ VkDescriptorImageInfo ;
struct TYPE_7__ {void* range; void* offset; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_3__ VkDescriptorBufferInfo ;
typedef  int /*<<< orphan*/  VkBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER ; 
 int /*<<< orphan*/  VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET ; 
 int /*<<< orphan*/  vkUpdateDescriptorSets (int /*<<< orphan*/ ,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_write_quad_descriptors(
      VkDevice device,
      VkDescriptorSet set,
      VkBuffer buffer,
      VkDeviceSize offset,
      VkDeviceSize range,
      const struct vk_texture *texture,
      VkSampler sampler)
{
   VkDescriptorBufferInfo buffer_info;
   VkWriteDescriptorSet write      = { VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET };

   buffer_info.buffer              = buffer;
   buffer_info.offset              = offset;
   buffer_info.range               = range;

   write.dstSet                    = set;
   write.dstBinding                = 0;
   write.descriptorCount           = 1;
   write.descriptorType            = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
   write.pBufferInfo               = &buffer_info;
   vkUpdateDescriptorSets(device, 1, &write, 0, NULL);

   if (texture)
   {
      VkDescriptorImageInfo image_info;

      image_info.sampler              = sampler;
      image_info.imageView            = texture->view;
      image_info.imageLayout          = texture->layout;

      write.dstSet                    = set;
      write.dstBinding                = 1;
      write.descriptorCount           = 1;
      write.descriptorType            = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
      write.pImageInfo                = &image_info;
      vkUpdateDescriptorSets(device, 1, &write, 0, NULL);
   }
}