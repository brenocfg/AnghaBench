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
struct vk_texture {scalar_t__ image; scalar_t__ memory; scalar_t__ buffer; scalar_t__ view; scalar_t__ mapped; } ;
typedef  int /*<<< orphan*/  VkDevice ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct vk_texture*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkDestroyBuffer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyImage (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyImageView (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkFreeMemory (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkUnmapMemory (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vulkan_track_dealloc (scalar_t__) ; 

void vulkan_destroy_texture(
      VkDevice device,
      struct vk_texture *tex)
{
   if (tex->mapped)
      vkUnmapMemory(device, tex->memory);
   if (tex->view)
      vkDestroyImageView(device, tex->view, NULL);
   if (tex->image)
      vkDestroyImage(device, tex->image, NULL);
   if (tex->buffer)
      vkDestroyBuffer(device, tex->buffer, NULL);
   if (tex->memory)
      vkFreeMemory(device, tex->memory, NULL);

#ifdef VULKAN_DEBUG_TEXTURE_ALLOC
   if (tex->image)
      vulkan_track_dealloc(tex->image);
#endif
   memset(tex, 0, sizeof(*tex));
}