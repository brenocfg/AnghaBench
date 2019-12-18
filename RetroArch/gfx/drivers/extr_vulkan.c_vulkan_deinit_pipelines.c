#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * pipelines; } ;
struct TYPE_8__ {int /*<<< orphan*/  font; int /*<<< orphan*/  alpha_blend; } ;
struct TYPE_10__ {TYPE_1__ display; TYPE_3__* context; TYPE_2__ pipelines; } ;
typedef  TYPE_4__ vk_t ;
struct TYPE_9__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vkDestroyPipeline (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_deinit_pipeline_layout (TYPE_4__*) ; 

__attribute__((used)) static void vulkan_deinit_pipelines(vk_t *vk)
{
   unsigned i;

   vulkan_deinit_pipeline_layout(vk);
   vkDestroyPipeline(vk->context->device,
         vk->pipelines.alpha_blend, NULL);
   vkDestroyPipeline(vk->context->device,
         vk->pipelines.font, NULL);

   for (i = 0; i < ARRAY_SIZE(vk->display.pipelines); i++)
      vkDestroyPipeline(vk->context->device,
            vk->display.pipelines[i], NULL);
}