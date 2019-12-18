#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ resizable; int /*<<< orphan*/  monitor; scalar_t__ decorated; } ;
typedef  TYPE_1__ _GLFWwindow ;
typedef  int DWORD ;

/* Variables and functions */
 int WS_CAPTION ; 
 int WS_CLIPCHILDREN ; 
 int WS_CLIPSIBLINGS ; 
 int WS_MAXIMIZEBOX ; 
 int WS_MINIMIZEBOX ; 
 int WS_POPUP ; 
 int WS_SIZEBOX ; 
 int WS_SYSMENU ; 

__attribute__((used)) static DWORD getWindowStyle(const _GLFWwindow* window)
{
    DWORD style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

    if (window->decorated && !window->monitor)
    {
        style |= WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

        if (window->resizable)
            style |= WS_MAXIMIZEBOX | WS_SIZEBOX;
    }
    else
        style |= WS_POPUP;

    return style;
}