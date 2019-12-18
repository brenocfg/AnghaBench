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
struct vk_buffer_node {int /*<<< orphan*/  buffer; struct vk_buffer_node* next; } ;
struct vk_buffer_chain {struct vk_buffer_node* head; } ;
typedef  int /*<<< orphan*/  VkDevice ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct vk_buffer_node*) ; 
 int /*<<< orphan*/  memset (struct vk_buffer_chain*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vulkan_destroy_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void vulkan_buffer_chain_free(
      VkDevice device,
      struct vk_buffer_chain *chain)
{
   struct vk_buffer_node *node = chain->head;
   while (node)
   {
      struct vk_buffer_node *next = node->next;
      vulkan_destroy_buffer(device, &node->buffer);

      free(node);
      node = next;
   }
   memset(chain, 0, sizeof(*chain));
}