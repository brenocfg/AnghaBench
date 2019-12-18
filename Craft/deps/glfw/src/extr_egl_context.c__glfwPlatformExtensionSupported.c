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
struct TYPE_3__ {int /*<<< orphan*/  display; } ;
struct TYPE_4__ {TYPE_1__ egl; } ;

/* Variables and functions */
 int /*<<< orphan*/  EGL_EXTENSIONS ; 
 int GL_FALSE ; 
 int GL_TRUE ; 
 TYPE_2__ _glfw ; 
 scalar_t__ _glfwStringInExtensionString (char const*,char const*) ; 
 char* _glfw_eglQueryString (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int _glfwPlatformExtensionSupported(const char* extension)
{
    const char* extensions = _glfw_eglQueryString(_glfw.egl.display,
                                                  EGL_EXTENSIONS);
    if (extensions)
    {
        if (_glfwStringInExtensionString(extension, extensions))
            return GL_TRUE;
    }

    return GL_FALSE;
}