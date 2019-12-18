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
struct TYPE_3__ {scalar_t__ context; int /*<<< orphan*/  allocated; } ;
struct TYPE_4__ {TYPE_1__ win32_tls; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 scalar_t__ TLS_OUT_OF_INDEXES ; 
 scalar_t__ TlsAlloc () ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

GLFWbool _glfwInitThreadLocalStorageWin32(void)
{
    _glfw.win32_tls.context = TlsAlloc();
    if (_glfw.win32_tls.context == TLS_OUT_OF_INDEXES)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Win32: Failed to allocate TLS index");
        return GLFW_FALSE;
    }

    _glfw.win32_tls.allocated = GLFW_TRUE;
    return GLFW_TRUE;
}