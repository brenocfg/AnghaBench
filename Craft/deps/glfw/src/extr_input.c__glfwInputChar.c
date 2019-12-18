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
struct TYPE_4__ {int /*<<< orphan*/  (* character ) (int /*<<< orphan*/ *,unsigned int) ;int /*<<< orphan*/  (* charmods ) (int /*<<< orphan*/ *,unsigned int,int) ;} ;
struct TYPE_5__ {TYPE_1__ callbacks; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,unsigned int) ; 

void _glfwInputChar(_GLFWwindow* window, unsigned int codepoint, int mods, int plain)
{
    if (codepoint < 32 || (codepoint > 126 && codepoint < 160))
        return;

    if (window->callbacks.charmods)
        window->callbacks.charmods((GLFWwindow*) window, codepoint, mods);

    if (plain)
    {
        if (window->callbacks.character)
            window->callbacks.character((GLFWwindow*) window, codepoint);
    }
}