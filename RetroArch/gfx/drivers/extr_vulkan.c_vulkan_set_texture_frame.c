#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {float alpha; unsigned int last_index; int* dirty; struct vk_texture* textures_optimal; struct vk_texture* textures; } ;
struct TYPE_10__ {TYPE_2__ menu; TYPE_1__* context; } ;
typedef  TYPE_3__ vk_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vk_texture {scalar_t__ type; scalar_t__ memory; int /*<<< orphan*/  stride; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ VkComponentMapping ;
struct TYPE_8__ {unsigned int current_swapchain_index; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  VK_COMPONENT_SWIZZLE_A ; 
 int /*<<< orphan*/  VK_COMPONENT_SWIZZLE_B ; 
 int /*<<< orphan*/  VK_COMPONENT_SWIZZLE_G ; 
 int /*<<< orphan*/  VK_COMPONENT_SWIZZLE_R ; 
 int /*<<< orphan*/  VK_FORMAT_B4G4R4A4_UNORM_PACK16 ; 
 int /*<<< orphan*/  VK_FORMAT_B8G8R8A8_UNORM ; 
 scalar_t__ VULKAN_TEXTURE_DYNAMIC ; 
 scalar_t__ VULKAN_TEXTURE_STAGING ; 
 scalar_t__ VULKAN_TEXTURE_STREAMED ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  vkMapMemory (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  vkUnmapMemory (int /*<<< orphan*/ ,scalar_t__) ; 
 struct vk_texture vulkan_create_texture (TYPE_3__*,struct vk_texture*,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__ const*,scalar_t__) ; 
 int /*<<< orphan*/  vulkan_sync_texture_to_gpu (TYPE_3__*,struct vk_texture*) ; 

__attribute__((used)) static void vulkan_set_texture_frame(void *data,
      const void *frame, bool rgb32, unsigned width, unsigned height,
      float alpha)
{
   unsigned y, stride;
   uint8_t *ptr                       = NULL;
   uint8_t *dst                       = NULL;
   const uint8_t *src                 = NULL;
   vk_t *vk                           = (vk_t*)data;
   unsigned index                     = 0;
   struct vk_texture *texture         = NULL;
   struct vk_texture *texture_optimal = NULL;
   const VkComponentMapping br_swizzle = {
      VK_COMPONENT_SWIZZLE_B,
      VK_COMPONENT_SWIZZLE_G,
      VK_COMPONENT_SWIZZLE_R,
      VK_COMPONENT_SWIZZLE_A,
   };

   if (!vk)
      return;

   index           = vk->context->current_swapchain_index;
   texture         = &vk->menu.textures[index];
   texture_optimal = &vk->menu.textures_optimal[index];

   /* B4G4R4A4 must be supported, but R4G4B4A4 is optional,
    * just apply the swizzle in the image view instead. */
   *texture = vulkan_create_texture(vk,
         texture->memory ? texture : NULL,
         width, height,
         rgb32 ? VK_FORMAT_B8G8R8A8_UNORM : VK_FORMAT_B4G4R4A4_UNORM_PACK16,
         NULL, rgb32 ? NULL : &br_swizzle,
         texture_optimal->memory ? VULKAN_TEXTURE_STAGING : VULKAN_TEXTURE_STREAMED);

   vkMapMemory(vk->context->device, texture->memory,
         texture->offset, texture->size, 0, (void**)&ptr);

   dst       = ptr;
   src       = (const uint8_t*)frame;
   stride    = (rgb32 ? sizeof(uint32_t) : sizeof(uint16_t)) * width;

   for (y = 0; y < height; y++, dst += texture->stride, src += stride)
      memcpy(dst, src, stride);

   vk->menu.alpha      = alpha;
   vk->menu.last_index = index;

   if (texture->type == VULKAN_TEXTURE_STAGING)
   {
      *texture_optimal = vulkan_create_texture(vk,
            texture_optimal->memory ? texture_optimal : NULL,
            width, height,
            rgb32 ? VK_FORMAT_B8G8R8A8_UNORM : VK_FORMAT_B4G4R4A4_UNORM_PACK16,
            NULL, rgb32 ? NULL : &br_swizzle,
            VULKAN_TEXTURE_DYNAMIC);
   }
   else
       vulkan_sync_texture_to_gpu(vk, texture);

   vkUnmapMemory(vk->context->device, texture->memory);
   vk->menu.dirty[index] = true;
}