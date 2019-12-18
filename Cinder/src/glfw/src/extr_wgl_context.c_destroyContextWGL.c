#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_6__ {TYPE_1__ wgl; } ;
struct TYPE_7__ {TYPE_2__ context; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  wglDeleteContext (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroyContextWGL(_GLFWwindow* window)
{
    if (window->context.wgl.handle)
    {
        wglDeleteContext(window->context.wgl.handle);
        window->context.wgl.handle = NULL;
    }
}