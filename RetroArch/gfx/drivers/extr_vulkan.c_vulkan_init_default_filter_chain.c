#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ smooth; } ;
struct TYPE_9__ {int /*<<< orphan*/  cache; } ;
struct TYPE_15__ {int /*<<< orphan*/  filter_chain; TYPE_6__ video; int /*<<< orphan*/  tex_fmt; TYPE_5__* context; int /*<<< orphan*/  render_pass; int /*<<< orphan*/  vk_vp; int /*<<< orphan*/  tex_h; int /*<<< orphan*/  tex_w; TYPE_2__* swapchain; TYPE_1__ pipelines; } ;
typedef  TYPE_7__ vk_t ;
struct TYPE_12__ {int /*<<< orphan*/  num_indices; int /*<<< orphan*/  render_pass; int /*<<< orphan*/  format; int /*<<< orphan*/  viewport; } ;
struct TYPE_11__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct vulkan_filter_chain_create_info {int /*<<< orphan*/  original_format; TYPE_4__ swapchain; TYPE_3__ max_input_size; int /*<<< orphan*/  command_pool; int /*<<< orphan*/  queue; int /*<<< orphan*/  pipeline_cache; int /*<<< orphan*/ * memory_properties; int /*<<< orphan*/  gpu; int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_13__ {size_t current_swapchain_index; int /*<<< orphan*/  num_swapchain_images; int /*<<< orphan*/  swapchain_format; int /*<<< orphan*/  queue; int /*<<< orphan*/  memory_properties; int /*<<< orphan*/  gpu; int /*<<< orphan*/  device; } ;
struct TYPE_10__ {int /*<<< orphan*/  cmd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  VULKAN_FILTER_CHAIN_LINEAR ; 
 int /*<<< orphan*/  VULKAN_FILTER_CHAIN_NEAREST ; 
 int /*<<< orphan*/  memset (struct vulkan_filter_chain_create_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vulkan_filter_chain_create_default (struct vulkan_filter_chain_create_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool vulkan_init_default_filter_chain(vk_t *vk)
{
   struct vulkan_filter_chain_create_info info;

   memset(&info, 0, sizeof(info));

   if (!vk->context)
      return false;

   info.device                = vk->context->device;
   info.gpu                   = vk->context->gpu;
   info.memory_properties     = &vk->context->memory_properties;
   info.pipeline_cache        = vk->pipelines.cache;
   info.queue                 = vk->context->queue;
   info.command_pool          = vk->swapchain[vk->context->current_swapchain_index].cmd_pool;
   info.max_input_size.width  = vk->tex_w;
   info.max_input_size.height = vk->tex_h;
   info.swapchain.viewport    = vk->vk_vp;
   info.swapchain.format      = vk->context->swapchain_format;
   info.swapchain.render_pass = vk->render_pass;
   info.swapchain.num_indices = vk->context->num_swapchain_images;
   info.original_format       = vk->tex_fmt;

   vk->filter_chain           = vulkan_filter_chain_create_default(
         &info,
         vk->video.smooth ?
         VULKAN_FILTER_CHAIN_LINEAR : VULKAN_FILTER_CHAIN_NEAREST);

   if (!vk->filter_chain)
   {
      RARCH_ERR("Failed to create filter chain.\n");
      return false;
   }

   return true;
}