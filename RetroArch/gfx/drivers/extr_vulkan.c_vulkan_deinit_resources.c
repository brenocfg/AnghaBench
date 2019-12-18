#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vk_t ;

/* Variables and functions */
 int /*<<< orphan*/  vulkan_deinit_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_deinit_command_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_deinit_descriptor_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_deinit_framebuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_deinit_pipelines (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vulkan_deinit_textures (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vulkan_deinit_resources(vk_t *vk)
{
   vulkan_deinit_pipelines(vk);
   vulkan_deinit_framebuffers(vk);
   vulkan_deinit_descriptor_pool(vk);
   vulkan_deinit_textures(vk);
   vulkan_deinit_buffers(vk);
   vulkan_deinit_command_buffers(vk);
}