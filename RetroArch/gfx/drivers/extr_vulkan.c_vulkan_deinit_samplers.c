#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mipmap_linear; int /*<<< orphan*/  mipmap_nearest; int /*<<< orphan*/  linear; int /*<<< orphan*/  nearest; } ;
struct TYPE_7__ {TYPE_2__ samplers; TYPE_1__* context; } ;
typedef  TYPE_3__ vk_t ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  vkDestroySampler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_deinit_samplers(vk_t *vk)
{
   vkDestroySampler(vk->context->device, vk->samplers.nearest, NULL);
   vkDestroySampler(vk->context->device, vk->samplers.linear, NULL);
   vkDestroySampler(vk->context->device, vk->samplers.mipmap_nearest, NULL);
   vkDestroySampler(vk->context->device, vk->samplers.mipmap_linear, NULL);
}