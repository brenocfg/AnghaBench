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
typedef  int /*<<< orphan*/  VkInstance ;
typedef  int /*<<< orphan*/  VkBool32 ;
typedef  int /*<<< orphan*/ * PFN_vkVoidFunction ;

/* Variables and functions */
 int /*<<< orphan*/ * GetInstanceProcAddr (int /*<<< orphan*/ ,char const*) ; 

VkBool32 vulkan_symbol_wrapper_load_instance_symbol(VkInstance instance, const char *name, PFN_vkVoidFunction *ppSymbol)
{
    *ppSymbol = GetInstanceProcAddr(instance, name);
    return *ppSymbol != NULL;
}