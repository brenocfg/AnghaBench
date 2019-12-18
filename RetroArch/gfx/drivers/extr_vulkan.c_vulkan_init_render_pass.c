#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  render_pass; TYPE_1__* context; } ;
typedef  TYPE_2__ vk_t ;
struct TYPE_11__ {int colorAttachmentCount; TYPE_5__* pColorAttachments; int /*<<< orphan*/  pipelineBindPoint; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ VkSubpassDescription ;
struct TYPE_12__ {int attachmentCount; int subpassCount; TYPE_3__* pSubpasses; TYPE_6__* pAttachments; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ VkRenderPassCreateInfo ;
struct TYPE_13__ {void* member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ VkAttachmentReference ;
struct TYPE_14__ {void* finalLayout; void* initialLayout; int /*<<< orphan*/  stencilStoreOp; int /*<<< orphan*/  stencilLoadOp; int /*<<< orphan*/  storeOp; int /*<<< orphan*/  loadOp; int /*<<< orphan*/  samples; int /*<<< orphan*/  format; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_6__ VkAttachmentDescription ;
struct TYPE_9__ {int /*<<< orphan*/  device; int /*<<< orphan*/  swapchain_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  VK_ATTACHMENT_LOAD_OP_CLEAR ; 
 int /*<<< orphan*/  VK_ATTACHMENT_LOAD_OP_DONT_CARE ; 
 int /*<<< orphan*/  VK_ATTACHMENT_STORE_OP_DONT_CARE ; 
 int /*<<< orphan*/  VK_ATTACHMENT_STORE_OP_STORE ; 
 void* VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL ; 
 int /*<<< orphan*/  VK_PIPELINE_BIND_POINT_GRAPHICS ; 
 int /*<<< orphan*/  VK_SAMPLE_COUNT_1_BIT ; 
 int /*<<< orphan*/  VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO ; 
 int /*<<< orphan*/  vkCreateRenderPass (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_init_render_pass(
      vk_t *vk)
{
   VkRenderPassCreateInfo rp_info = {
      VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO };
   VkAttachmentDescription attachment = {0};
   VkSubpassDescription subpass       = {0};
   VkAttachmentReference color_ref    = { 0,
      VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL };

   /* Backbuffer format. */
   attachment.format            = vk->context->swapchain_format;
   /* Not multisampled. */
   attachment.samples           = VK_SAMPLE_COUNT_1_BIT;
   /* When starting the frame, we want tiles to be cleared. */
   attachment.loadOp            = VK_ATTACHMENT_LOAD_OP_CLEAR;
   /* When end the frame, we want tiles to be written out. */
   attachment.storeOp           = VK_ATTACHMENT_STORE_OP_STORE;
   /* Don't care about stencil since we're not using it. */
   attachment.stencilLoadOp     = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
   attachment.stencilStoreOp    = VK_ATTACHMENT_STORE_OP_DONT_CARE;

   /* The image layout will be attachment_optimal
    * when we're executing the renderpass. */
   attachment.initialLayout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
   attachment.finalLayout       = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

   /* We have one subpass.
    * This subpass has 1 color attachment. */
   subpass.pipelineBindPoint    = VK_PIPELINE_BIND_POINT_GRAPHICS;
   subpass.colorAttachmentCount = 1;
   subpass.pColorAttachments    = &color_ref;

   /* Finally, create the renderpass. */
   rp_info.attachmentCount      = 1;
   rp_info.pAttachments         = &attachment;
   rp_info.subpassCount         = 1;
   rp_info.pSubpasses           = &subpass;

   vkCreateRenderPass(vk->context->device,
         &rp_info, NULL, &vk->render_pass);
}