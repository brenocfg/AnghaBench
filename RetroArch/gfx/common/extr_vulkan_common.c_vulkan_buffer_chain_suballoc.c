#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct vk_buffer_range {int offset; int /*<<< orphan*/  buffer; int /*<<< orphan*/ * data; } ;
struct vk_buffer_chain {size_t offset; int alignment; TYPE_2__* current; } ;
typedef  int VkDeviceSize ;
struct TYPE_3__ {int size; int /*<<< orphan*/  buffer; scalar_t__ mapped; } ;
struct TYPE_4__ {TYPE_1__ buffer; } ;

/* Variables and functions */

__attribute__((used)) static bool vulkan_buffer_chain_suballoc(struct vk_buffer_chain *chain,
      size_t size, struct vk_buffer_range *range)
{
   VkDeviceSize next_offset = chain->offset + size;
   if (next_offset <= chain->current->buffer.size)
   {
      range->data   = (uint8_t*)chain->current->buffer.mapped + chain->offset;
      range->buffer = chain->current->buffer.buffer;
      range->offset = chain->offset;
      chain->offset = (next_offset + chain->alignment - 1)
         & ~(chain->alignment - 1);

      return true;
   }

   return false;
}