#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vulkan_context {int dummy; } ;
struct vk_buffer_range {int dummy; } ;
struct vk_buffer_chain {size_t block_size; TYPE_1__* current; int /*<<< orphan*/  usage; scalar_t__ offset; TYPE_1__* head; } ;
struct TYPE_2__ {void* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  retro_assert (scalar_t__) ; 
 void* vulkan_buffer_chain_alloc_node (struct vulkan_context const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vulkan_buffer_chain_step (struct vk_buffer_chain*) ; 
 scalar_t__ vulkan_buffer_chain_suballoc (struct vk_buffer_chain*,size_t,struct vk_buffer_range*) ; 

bool vulkan_buffer_chain_alloc(const struct vulkan_context *context,
      struct vk_buffer_chain *chain,
      size_t size, struct vk_buffer_range *range)
{
   if (!chain->head)
   {
      chain->head = vulkan_buffer_chain_alloc_node(context,
            chain->block_size, chain->usage);
      if (!chain->head)
         return false;

      chain->current = chain->head;
      chain->offset = 0;
   }

   if (vulkan_buffer_chain_suballoc(chain, size, range))
      return true;

   /* We've exhausted the current chain, traverse list until we
    * can find a block we can use. Usually, we just step once. */
   while (chain->current->next)
   {
      vulkan_buffer_chain_step(chain);
      if (vulkan_buffer_chain_suballoc(chain, size, range))
         return true;
   }

   /* We have to allocate a new node, might allocate larger
    * buffer here than block_size in case we have
    * a very large allocation. */
   if (size < chain->block_size)
      size = chain->block_size;

   chain->current->next = vulkan_buffer_chain_alloc_node(
         context, size, chain->usage);
   if (!chain->current->next)
      return false;

   vulkan_buffer_chain_step(chain);
   /* This cannot possibly fail. */
   retro_assert(vulkan_buffer_chain_suballoc(chain, size, range));
   return true;
}