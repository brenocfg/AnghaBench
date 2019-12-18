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
struct TYPE_4__ {int major; } ;
struct TYPE_5__ {scalar_t__ (* GetString ) (int /*<<< orphan*/ ) ;scalar_t__ (* GetStringi ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* GetIntegerv ) (int /*<<< orphan*/ ,int*) ;TYPE_1__ context; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_INVALID_VALUE ; 
 int /*<<< orphan*/  GLFW_NO_CURRENT_CONTEXT ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int GL_FALSE ; 
 int /*<<< orphan*/  GL_NUM_EXTENSIONS ; 
 int GL_TRUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 
 int _glfwPlatformExtensionSupported (char const*) ; 
 TYPE_2__* _glfwPlatformGetCurrentContext () ; 
 scalar_t__ _glfwStringInExtensionString (char const*,char const*) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ) ; 

int glfwExtensionSupported(const char* extension)
{
    _GLFWwindow* window;

    _GLFW_REQUIRE_INIT_OR_RETURN(GL_FALSE);

    window = _glfwPlatformGetCurrentContext();
    if (!window)
    {
        _glfwInputError(GLFW_NO_CURRENT_CONTEXT, NULL);
        return GL_FALSE;
    }

    if (*extension == '\0')
    {
        _glfwInputError(GLFW_INVALID_VALUE, NULL);
        return GL_FALSE;
    }

#if defined(_GLFW_USE_OPENGL)
    if (window->context.major >= 3)
    {
        int i;
        GLint count;

        // Check if extension is in the modern OpenGL extensions string list

        window->GetIntegerv(GL_NUM_EXTENSIONS, &count);

        for (i = 0;  i < count;  i++)
        {
            const char* en = (const char*) window->GetStringi(GL_EXTENSIONS, i);
            if (!en)
            {
                _glfwInputError(GLFW_PLATFORM_ERROR,
                                "Failed to retrieve extension string %i", i);
                return GL_FALSE;
            }

            if (strcmp(en, extension) == 0)
                return GL_TRUE;
        }
    }
    else
#endif // _GLFW_USE_OPENGL
    {
        // Check if extension is in the old style OpenGL extensions string

        const char* extensions = (const char*) window->GetString(GL_EXTENSIONS);
        if (!extensions)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Failed to retrieve extension string");
            return GL_FALSE;
        }

        if (_glfwStringInExtensionString(extension, extensions))
            return GL_TRUE;
    }

    // Check if extension is in the platform-specific string
    return _glfwPlatformExtensionSupported(extension);
}