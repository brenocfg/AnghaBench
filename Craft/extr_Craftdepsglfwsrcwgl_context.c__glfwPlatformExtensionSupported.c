#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* (* GetExtensionsStringEXT ) () ;char* (* GetExtensionsStringARB ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  dc; } ;
struct TYPE_5__ {TYPE_1__ wgl; } ;
typedef  TYPE_2__ _GLFWwindow ;

/* Variables and functions */
 int GL_FALSE ; 
 int GL_TRUE ; 
 TYPE_2__* _glfwPlatformGetCurrentContext () ; 
 scalar_t__ _glfwStringInExtensionString (char const*,char const*) ; 
 char* stub1 () ; 
 char* stub2 (int /*<<< orphan*/ ) ; 

int _glfwPlatformExtensionSupported(const char* extension)
{
    const char* extensions;

    _GLFWwindow* window = _glfwPlatformGetCurrentContext();

    if (window->wgl.GetExtensionsStringEXT != NULL)
    {
        extensions = window->wgl.GetExtensionsStringEXT();
        if (extensions)
        {
            if (_glfwStringInExtensionString(extension, extensions))
                return GL_TRUE;
        }
    }

    if (window->wgl.GetExtensionsStringARB != NULL)
    {
        extensions = window->wgl.GetExtensionsStringARB(window->wgl.dc);
        if (extensions)
        {
            if (_glfwStringInExtensionString(extension, extensions))
                return GL_TRUE;
        }
    }

    return GL_FALSE;
}