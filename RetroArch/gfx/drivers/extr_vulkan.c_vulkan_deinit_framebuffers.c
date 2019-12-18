#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned int num_swapchain_images; int /*<<< orphan*/  render_pass; TYPE_3__* context; TYPE_2__* swapchain; } ;
typedef  TYPE_4__ vk_t ;
struct TYPE_8__ {int /*<<< orphan*/  device; } ;
struct TYPE_6__ {scalar_t__ view; scalar_t__ framebuffer; } ;
struct TYPE_7__ {TYPE_1__ backbuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  vkDestroyFramebuffer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyImageView (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyRenderPass (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_deinit_framebuffers(vk_t *vk)
{
   unsigned i;
   for (i = 0; i < vk->num_swapchain_images; i++)
   {
      if (vk->swapchain[i].backbuffer.framebuffer)
      {
         vkDestroyFramebuffer(vk->context->device,
               vk->swapchain[i].backbuffer.framebuffer, NULL);
      }

      if (vk->swapchain[i].backbuffer.view)
      {
         vkDestroyImageView(vk->context->device,
               vk->swapchain[i].backbuffer.view, NULL);
      }
   }

   vkDestroyRenderPass(vk->context->device, vk->render_pass, NULL);
}