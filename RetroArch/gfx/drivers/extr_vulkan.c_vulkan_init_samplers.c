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
struct TYPE_8__ {int /*<<< orphan*/  mipmap_linear; int /*<<< orphan*/  mipmap_nearest; int /*<<< orphan*/  linear; int /*<<< orphan*/  nearest; } ;
struct TYPE_9__ {TYPE_2__ samplers; TYPE_1__* context; } ;
typedef  TYPE_3__ vk_t ;
struct TYPE_10__ {float mipLodBias; float maxAnisotropy; int compareEnable; float minLod; float maxLod; int unnormalizedCoordinates; void* mipmapMode; void* minFilter; void* magFilter; int /*<<< orphan*/  borderColor; void* addressModeW; void* addressModeV; void* addressModeU; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ VkSamplerCreateInfo ;
struct TYPE_7__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE ; 
 void* VK_FILTER_LINEAR ; 
 void* VK_FILTER_NEAREST ; 
 float VK_LOD_CLAMP_NONE ; 
 void* VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE ; 
 void* VK_SAMPLER_MIPMAP_MODE_LINEAR ; 
 void* VK_SAMPLER_MIPMAP_MODE_NEAREST ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO ; 
 int /*<<< orphan*/  vkCreateSampler (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_init_samplers(vk_t *vk)
{
   VkSamplerCreateInfo info =
   { VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO };

   info.magFilter               = VK_FILTER_NEAREST;
   info.minFilter               = VK_FILTER_NEAREST;
   info.mipmapMode              = VK_SAMPLER_MIPMAP_MODE_NEAREST;
   info.addressModeU            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
   info.addressModeV            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
   info.addressModeW            = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
   info.mipLodBias              = 0.0f;
   info.maxAnisotropy           = 1.0f;
   info.compareEnable           = false;
   info.minLod                  = 0.0f;
   info.maxLod                  = 0.0f;
   info.unnormalizedCoordinates = false;
   info.borderColor             = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;
   vkCreateSampler(vk->context->device,
         &info, NULL, &vk->samplers.nearest);

   info.magFilter = VK_FILTER_LINEAR;
   info.minFilter = VK_FILTER_LINEAR;
   vkCreateSampler(vk->context->device,
         &info, NULL, &vk->samplers.linear);

   info.maxLod     = VK_LOD_CLAMP_NONE;
   info.magFilter  = VK_FILTER_NEAREST;
   info.minFilter  = VK_FILTER_NEAREST;
   info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
   vkCreateSampler(vk->context->device,
         &info, NULL, &vk->samplers.mipmap_nearest);

   info.magFilter  = VK_FILTER_LINEAR;
   info.minFilter  = VK_FILTER_LINEAR;
   info.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
   vkCreateSampler(vk->context->device,
         &info, NULL, &vk->samplers.mipmap_linear);
}