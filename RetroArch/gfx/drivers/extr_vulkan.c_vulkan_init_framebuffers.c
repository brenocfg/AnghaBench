#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {unsigned int num_swapchain_images; TYPE_5__* swapchain; TYPE_3__* context; int /*<<< orphan*/  render_pass; } ;
typedef  TYPE_6__ vk_t ;
struct TYPE_14__ {int /*<<< orphan*/  a; int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct TYPE_13__ {int levelCount; int layerCount; int /*<<< orphan*/  aspectMask; scalar_t__ baseArrayLayer; scalar_t__ baseMipLevel; } ;
struct TYPE_19__ {scalar_t__ image; TYPE_2__ components; TYPE_1__ subresourceRange; int /*<<< orphan*/  format; int /*<<< orphan*/  viewType; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ VkImageViewCreateInfo ;
struct TYPE_20__ {int attachmentCount; int layers; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__* pAttachments; int /*<<< orphan*/  renderPass; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_8__ VkFramebufferCreateInfo ;
struct TYPE_16__ {scalar_t__ image; scalar_t__ framebuffer; scalar_t__ view; } ;
struct TYPE_17__ {TYPE_4__ backbuffer; } ;
struct TYPE_15__ {scalar_t__* swapchain_images; int /*<<< orphan*/  device; int /*<<< orphan*/  swapchain_height; int /*<<< orphan*/  swapchain_width; int /*<<< orphan*/  swapchain_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  VK_COMPONENT_SWIZZLE_A ; 
 int /*<<< orphan*/  VK_COMPONENT_SWIZZLE_B ; 
 int /*<<< orphan*/  VK_COMPONENT_SWIZZLE_G ; 
 int /*<<< orphan*/  VK_COMPONENT_SWIZZLE_R ; 
 int /*<<< orphan*/  VK_IMAGE_ASPECT_COLOR_BIT ; 
 int /*<<< orphan*/  VK_IMAGE_VIEW_TYPE_2D ; 
 scalar_t__ VK_NULL_HANDLE ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO ; 
 int /*<<< orphan*/  vkCreateFramebuffer (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  vkCreateImageView (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  vulkan_init_render_pass (TYPE_6__*) ; 

__attribute__((used)) static void vulkan_init_framebuffers(
      vk_t *vk)
{
   unsigned i;

   vulkan_init_render_pass(vk);

   for (i = 0; i < vk->num_swapchain_images; i++)
   {
      VkImageViewCreateInfo view =
      { VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO };
      VkFramebufferCreateInfo info =
      { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };

      vk->swapchain[i].backbuffer.image = vk->context->swapchain_images[i];

      if (vk->context->swapchain_images[i] == VK_NULL_HANDLE)
      {
         vk->swapchain[i].backbuffer.view        = VK_NULL_HANDLE;
         vk->swapchain[i].backbuffer.framebuffer = VK_NULL_HANDLE;
         continue;
      }

      /* Create an image view which we can render into. */
      view.viewType                        = VK_IMAGE_VIEW_TYPE_2D;
      view.format                          = vk->context->swapchain_format;
      view.image                           = vk->swapchain[i].backbuffer.image;
      view.subresourceRange.baseMipLevel   = 0;
      view.subresourceRange.baseArrayLayer = 0;
      view.subresourceRange.levelCount     = 1;
      view.subresourceRange.layerCount     = 1;
      view.subresourceRange.aspectMask     = VK_IMAGE_ASPECT_COLOR_BIT;
      view.components.r                    = VK_COMPONENT_SWIZZLE_R;
      view.components.g                    = VK_COMPONENT_SWIZZLE_G;
      view.components.b                    = VK_COMPONENT_SWIZZLE_B;
      view.components.a                    = VK_COMPONENT_SWIZZLE_A;

      vkCreateImageView(vk->context->device,
            &view, NULL, &vk->swapchain[i].backbuffer.view);

      /* Create the framebuffer */
      info.renderPass      = vk->render_pass;
      info.attachmentCount = 1;
      info.pAttachments    = &vk->swapchain[i].backbuffer.view;
      info.width           = vk->context->swapchain_width;
      info.height          = vk->context->swapchain_height;
      info.layers          = 1;

      vkCreateFramebuffer(vk->context->device,
            &info, NULL, &vk->swapchain[i].backbuffer.framebuffer);
   }
}