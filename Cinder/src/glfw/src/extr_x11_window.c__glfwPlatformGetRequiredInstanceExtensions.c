#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {scalar_t__ handle; } ;
struct TYPE_7__ {TYPE_2__ x11xcb; } ;
struct TYPE_5__ {scalar_t__ KHR_xcb_surface; int /*<<< orphan*/  KHR_xlib_surface; } ;
struct TYPE_8__ {TYPE_3__ x11; TYPE_1__ vk; } ;

/* Variables and functions */
 TYPE_4__ _glfw ; 
 char** calloc (int,int) ; 
 char* strdup (char*) ; 

char** _glfwPlatformGetRequiredInstanceExtensions(uint32_t* count)
{
    char** extensions;

    *count = 0;

    if (!_glfw.vk.KHR_xcb_surface || !_glfw.x11.x11xcb.handle)
    {
        if (!_glfw.vk.KHR_xlib_surface)
            return NULL;
    }

    extensions = calloc(2, sizeof(char*));
    extensions[0] = strdup("VK_KHR_surface");

    if (_glfw.vk.KHR_xcb_surface && _glfw.x11.x11xcb.handle)
        extensions[1] = strdup("VK_KHR_xcb_surface");
    else
        extensions[1] = strdup("VK_KHR_xlib_surface");

    *count = 2;
    return extensions;
}