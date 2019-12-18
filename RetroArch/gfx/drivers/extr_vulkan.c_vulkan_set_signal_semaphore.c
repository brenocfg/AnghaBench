#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  signal_semaphore; } ;
struct TYPE_4__ {TYPE_1__ hw; } ;
typedef  TYPE_2__ vk_t ;
typedef  int /*<<< orphan*/  VkSemaphore ;

/* Variables and functions */

__attribute__((used)) static void vulkan_set_signal_semaphore(void *handle, VkSemaphore semaphore)
{
   vk_t *vk = (vk_t*)handle;
   vk->hw.signal_semaphore = semaphore;
}