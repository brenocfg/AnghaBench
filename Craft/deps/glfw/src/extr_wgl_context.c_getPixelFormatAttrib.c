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
struct TYPE_4__ {int /*<<< orphan*/  dc; int /*<<< orphan*/  (* GetPixelFormatAttribivARB ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*,int*) ;int /*<<< orphan*/  ARB_pixel_format; } ;
struct TYPE_5__ {TYPE_1__ wgl; } ;
typedef  TYPE_2__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*,int*) ; 

__attribute__((used)) static int getPixelFormatAttrib(_GLFWwindow* window, int pixelFormat, int attrib)
{
    int value = 0;

    assert(window->wgl.ARB_pixel_format);

    if (!window->wgl.GetPixelFormatAttribivARB(window->wgl.dc,
                                               pixelFormat,
                                               0, 1, &attrib, &value))
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "WGL: Failed to retrieve pixel format attribute %i",
                        attrib);
        return 0;
    }

    return value;
}