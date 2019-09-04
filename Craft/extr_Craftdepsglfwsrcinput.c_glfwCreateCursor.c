#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ _GLFWcursor ;
struct TYPE_6__ {TYPE_1__* cursorListHead; } ;
typedef  int /*<<< orphan*/  GLFWimage ;
typedef  int /*<<< orphan*/  GLFWcursor ;

/* Variables and functions */
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int /*<<< orphan*/ *) ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwPlatformCreateCursor (TYPE_1__*,int /*<<< orphan*/  const*,int,int) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  glfwDestroyCursor (int /*<<< orphan*/ *) ; 

GLFWcursor* glfwCreateCursor(const GLFWimage* image, int xhot, int yhot)
{
    _GLFWcursor* cursor;

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    cursor = calloc(1, sizeof(_GLFWcursor));
    cursor->next = _glfw.cursorListHead;
    _glfw.cursorListHead = cursor;

    if (!_glfwPlatformCreateCursor(cursor, image, xhot, yhot))
    {
        glfwDestroyCursor((GLFWcursor*) cursor);
        return NULL;
    }

    return (GLFWcursor*) cursor;
}