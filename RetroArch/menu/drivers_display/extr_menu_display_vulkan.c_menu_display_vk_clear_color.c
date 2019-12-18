#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int /*<<< orphan*/  cmd; TYPE_5__* context; } ;
typedef  TYPE_6__ vk_t ;
struct TYPE_22__ {scalar_t__ userdata; } ;
typedef  TYPE_7__ video_frame_info_t ;
typedef  int /*<<< orphan*/  rect ;
struct TYPE_23__ {int /*<<< orphan*/  a; int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
typedef  TYPE_8__ menu_display_ctx_clearcolor_t ;
typedef  int /*<<< orphan*/  attachment ;
struct TYPE_18__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_19__ {TYPE_3__ extent; } ;
struct TYPE_16__ {int /*<<< orphan*/ * float32; } ;
struct TYPE_17__ {TYPE_1__ color; } ;
struct TYPE_24__ {int layerCount; TYPE_4__ rect; TYPE_2__ clearValue; int /*<<< orphan*/  aspectMask; } ;
typedef  TYPE_9__ VkClearRect ;
typedef  TYPE_9__ VkClearAttachment ;
struct TYPE_20__ {int /*<<< orphan*/  swapchain_height; int /*<<< orphan*/  swapchain_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  VK_IMAGE_ASPECT_COLOR_BIT ; 
 int /*<<< orphan*/  memset (TYPE_9__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vkCmdClearAttachments (int /*<<< orphan*/ ,int,TYPE_9__*,int,TYPE_9__*) ; 

__attribute__((used)) static void menu_display_vk_clear_color(
      menu_display_ctx_clearcolor_t *clearcolor,
      video_frame_info_t *video_info)
{
   VkClearRect rect;
   VkClearAttachment attachment;
   vk_t *vk = (vk_t*)video_info->userdata;
   if (!vk || !clearcolor)
      return;

   memset(&attachment, 0, sizeof(attachment));
   memset(&rect, 0, sizeof(rect));

   attachment.aspectMask                  = VK_IMAGE_ASPECT_COLOR_BIT;
   attachment.clearValue.color.float32[0] = clearcolor->r;
   attachment.clearValue.color.float32[1] = clearcolor->g;
   attachment.clearValue.color.float32[2] = clearcolor->b;
   attachment.clearValue.color.float32[3] = clearcolor->a;

   rect.rect.extent.width  = vk->context->swapchain_width;
   rect.rect.extent.height = vk->context->swapchain_height;
   rect.layerCount         = 1;

   vkCmdClearAttachments(vk->cmd, 1, &attachment, 1, &rect);
}