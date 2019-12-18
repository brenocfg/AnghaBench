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
struct TYPE_3__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  (* GetProcAddressARB ) (int /*<<< orphan*/  const*) ;int /*<<< orphan*/  (* GetProcAddress ) (int /*<<< orphan*/  const*) ;} ;
struct TYPE_4__ {TYPE_1__ glx; } ;
typedef  int /*<<< orphan*/  GLubyte ;
typedef  int /*<<< orphan*/  GLFWglproc ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  dlsym (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static GLFWglproc getProcAddressGLX(const char* procname)
{
    if (_glfw.glx.GetProcAddress)
        return _glfw.glx.GetProcAddress((const GLubyte*) procname);
    else if (_glfw.glx.GetProcAddressARB)
        return _glfw.glx.GetProcAddressARB((const GLubyte*) procname);
    else
        return dlsym(_glfw.glx.handle, procname);
}