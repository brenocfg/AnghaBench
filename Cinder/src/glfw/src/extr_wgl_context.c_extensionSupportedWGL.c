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
struct TYPE_3__ {char* (* GetExtensionsStringEXT ) () ;char* (* GetExtensionsStringARB ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ wgl; } ;

/* Variables and functions */
 int GLFW_FALSE ; 
 int GLFW_TRUE ; 
 TYPE_2__ _glfw ; 
 scalar_t__ _glfwStringInExtensionString (char const*,char const*) ; 
 char* stub1 () ; 
 char* stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wglGetCurrentDC () ; 

__attribute__((used)) static int extensionSupportedWGL(const char* extension)
{
    const char* extensions;

    if (_glfw.wgl.GetExtensionsStringEXT)
    {
        extensions = _glfw.wgl.GetExtensionsStringEXT();
        if (extensions)
        {
            if (_glfwStringInExtensionString(extension, extensions))
                return GLFW_TRUE;
        }
    }

    if (_glfw.wgl.GetExtensionsStringARB)
    {
        extensions = _glfw.wgl.GetExtensionsStringARB(wglGetCurrentDC());
        if (extensions)
        {
            if (_glfwStringInExtensionString(extension, extensions))
                return GLFW_TRUE;
        }
    }

    return GLFW_FALSE;
}