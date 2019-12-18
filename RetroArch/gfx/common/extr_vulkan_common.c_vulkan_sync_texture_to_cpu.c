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
struct TYPE_7__ {TYPE_1__* context; } ;
typedef  TYPE_2__ vk_t ;
struct vk_texture {scalar_t__ memory; int /*<<< orphan*/  need_manual_cache_management; } ;
struct TYPE_8__ {scalar_t__ memory; int /*<<< orphan*/  size; scalar_t__ offset; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ VkMappedMemoryRange ;
struct TYPE_6__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ VK_NULL_HANDLE ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE ; 
 int /*<<< orphan*/  VK_WHOLE_SIZE ; 
 int /*<<< orphan*/  vkInvalidateMappedMemoryRanges (int /*<<< orphan*/ ,int,TYPE_3__*) ; 

void vulkan_sync_texture_to_cpu(vk_t *vk, const struct vk_texture *tex)
{
   VkMappedMemoryRange range = { VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE };
   if (!tex || !tex->need_manual_cache_management || tex->memory == VK_NULL_HANDLE)
      return;

   range.memory = tex->memory;
   range.offset = 0;
   range.size = VK_WHOLE_SIZE;
   vkInvalidateMappedMemoryRanges(vk->context->device, 1, &range);
}