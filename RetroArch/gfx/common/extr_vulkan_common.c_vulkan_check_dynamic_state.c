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
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_14__ {TYPE_2__ extent; TYPE_1__ offset; } ;
struct TYPE_12__ {int dirty; TYPE_6__ scissor; scalar_t__ use_scissor; } ;
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_13__ {TYPE_4__ tracker; int /*<<< orphan*/  cmd; int /*<<< orphan*/  vk_vp; TYPE_3__ vp; } ;
typedef  TYPE_5__ vk_t ;
typedef  TYPE_6__ VkRect2D ;

/* Variables and functions */
 int VULKAN_DIRTY_DYNAMIC_BIT ; 
 int /*<<< orphan*/  vkCmdSetScissor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_6__*) ; 
 int /*<<< orphan*/  vkCmdSetViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_check_dynamic_state(
      vk_t *vk)
{

   if (vk->tracker.dirty & VULKAN_DIRTY_DYNAMIC_BIT)
   {
      VkRect2D sci;

      if (vk->tracker.use_scissor)
      {
         sci = vk->tracker.scissor;
      }
      else
      {
         /* No scissor -> viewport */
         sci.offset.x      = vk->vp.x;
         sci.offset.y      = vk->vp.y;
         sci.extent.width  = vk->vp.width;
         sci.extent.height = vk->vp.height;
      }

      vkCmdSetViewport(vk->cmd, 0, 1, &vk->vk_vp);
      vkCmdSetScissor (vk->cmd, 0, 1, &sci);

      vk->tracker.dirty &= ~VULKAN_DIRTY_DYNAMIC_BIT;
   }
}