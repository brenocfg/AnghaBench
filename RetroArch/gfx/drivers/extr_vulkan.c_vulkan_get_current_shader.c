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
typedef  int /*<<< orphan*/  vulkan_filter_chain_t ;
struct TYPE_2__ {scalar_t__ filter_chain; } ;
typedef  TYPE_1__ vk_t ;
struct video_shader {int dummy; } ;

/* Variables and functions */
 struct video_shader* vulkan_filter_chain_get_preset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct video_shader *vulkan_get_current_shader(void *data)
{
   vk_t *vk = (vk_t*)data;
   if (!vk || !vk->filter_chain)
      return NULL;

   return vulkan_filter_chain_get_preset((vulkan_filter_chain_t*)vk->filter_chain);
}