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
typedef  scalar_t__ WGLSHARELISTS_T ;
typedef  scalar_t__ WGLMAKECURRENT_T ;
typedef  scalar_t__ WGLGETPROCADDRESS_T ;
typedef  scalar_t__ WGLGETCURRENTDC_T ;
typedef  scalar_t__ WGLDELETECONTEXT_T ;
typedef  scalar_t__ WGLCREATECONTEXT_T ;
struct TYPE_3__ {scalar_t__ instance; scalar_t__ ShareLists; scalar_t__ MakeCurrent; scalar_t__ GetCurrentDC; scalar_t__ GetProcAddress; scalar_t__ DeleteContext; scalar_t__ CreateContext; } ;
struct TYPE_4__ {TYPE_1__ wgl; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 scalar_t__ GetProcAddress (scalar_t__,char*) ; 
 scalar_t__ LoadLibraryA (char*) ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

GLFWbool _glfwInitWGL(void)
{
    if (_glfw.wgl.instance)
        return GLFW_TRUE;

    _glfw.wgl.instance = LoadLibraryA("opengl32.dll");
    if (!_glfw.wgl.instance)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR, "WGL: Failed to load opengl32.dll");
        return GLFW_FALSE;
    }

    _glfw.wgl.CreateContext = (WGLCREATECONTEXT_T)
        GetProcAddress(_glfw.wgl.instance, "wglCreateContext");
    _glfw.wgl.DeleteContext = (WGLDELETECONTEXT_T)
        GetProcAddress(_glfw.wgl.instance, "wglDeleteContext");
    _glfw.wgl.GetProcAddress = (WGLGETPROCADDRESS_T)
        GetProcAddress(_glfw.wgl.instance, "wglGetProcAddress");
    _glfw.wgl.GetCurrentDC = (WGLGETCURRENTDC_T)
        GetProcAddress(_glfw.wgl.instance, "wglGetCurrentDC");
    _glfw.wgl.MakeCurrent = (WGLMAKECURRENT_T)
        GetProcAddress(_glfw.wgl.instance, "wglMakeCurrent");
    _glfw.wgl.ShareLists = (WGLSHARELISTS_T)
        GetProcAddress(_glfw.wgl.instance, "wglShareLists");

    return GLFW_TRUE;
}