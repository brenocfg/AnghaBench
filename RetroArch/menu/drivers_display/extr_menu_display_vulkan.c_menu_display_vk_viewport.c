#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {float minDepth; float maxDepth; scalar_t__ height; int /*<<< orphan*/  width; scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_10__ {TYPE_2__ vk_vp; TYPE_1__* context; } ;
typedef  TYPE_3__ vk_t ;
struct TYPE_11__ {scalar_t__ userdata; } ;
typedef  TYPE_4__ video_frame_info_t ;
struct TYPE_12__ {scalar_t__ height; int /*<<< orphan*/  width; scalar_t__ y; int /*<<< orphan*/  x; } ;
typedef  TYPE_5__ menu_display_ctx_draw_t ;
struct TYPE_8__ {scalar_t__ swapchain_height; } ;

/* Variables and functions */

__attribute__((used)) static void menu_display_vk_viewport(menu_display_ctx_draw_t *draw,
      video_frame_info_t *video_info)
{
   vk_t *vk                      = (vk_t*)video_info->userdata;

   if (!vk || !draw)
      return;

   vk->vk_vp.x        = draw->x;
   vk->vk_vp.y        = vk->context->swapchain_height - draw->y - draw->height;
   vk->vk_vp.width    = draw->width;
   vk->vk_vp.height   = draw->height;
   vk->vk_vp.minDepth = 0.0f;
   vk->vk_vp.maxDepth = 1.0f;
}