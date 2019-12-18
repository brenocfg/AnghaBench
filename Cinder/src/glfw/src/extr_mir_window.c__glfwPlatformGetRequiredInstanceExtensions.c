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
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  KHR_mir_surface; } ;
struct TYPE_4__ {TYPE_1__ vk; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 char** calloc (int,int) ; 
 char* strdup (char*) ; 

char** _glfwPlatformGetRequiredInstanceExtensions(uint32_t* count)
{
    char** extensions;

    *count = 0;

    if (!_glfw.vk.KHR_mir_surface)
        return NULL;

    extensions = calloc(2, sizeof(char*));
    extensions[0] = strdup("VK_KHR_surface");
    extensions[1] = strdup("VK_KHR_mir_surface");

    *count = 2;
    return extensions;
}