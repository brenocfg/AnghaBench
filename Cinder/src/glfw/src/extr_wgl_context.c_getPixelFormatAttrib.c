#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dc; } ;
struct TYPE_9__ {TYPE_2__ wgl; } ;
struct TYPE_10__ {TYPE_3__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_7__ {int /*<<< orphan*/  (* GetPixelFormatAttribivARB ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*,int*) ;int /*<<< orphan*/  ARB_pixel_format; } ;
struct TYPE_11__ {TYPE_1__ wgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*,int*) ; 

__attribute__((used)) static int getPixelFormatAttrib(_GLFWwindow* window, int pixelFormat, int attrib)
{
    int value = 0;

    assert(_glfw.wgl.ARB_pixel_format);

    if (!_glfw.wgl.GetPixelFormatAttribivARB(window->context.wgl.dc,
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