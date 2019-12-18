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
struct TYPE_9__ {int /*<<< orphan*/ * handle; scalar_t__ window; } ;
struct TYPE_8__ {TYPE_3__ glx; } ;
struct TYPE_10__ {TYPE_2__ context; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_7__ {int /*<<< orphan*/  display; } ;
struct TYPE_11__ {TYPE_1__ x11; } ;

/* Variables and functions */
 scalar_t__ None ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  glXDestroyContext (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glXDestroyWindow (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void destroyContextGLX(_GLFWwindow* window)
{
    if (window->context.glx.window)
    {
        glXDestroyWindow(_glfw.x11.display, window->context.glx.window);
        window->context.glx.window = None;
    }

    if (window->context.glx.handle)
    {
        glXDestroyContext(_glfw.x11.display, window->context.glx.handle);
        window->context.glx.handle = NULL;
    }
}