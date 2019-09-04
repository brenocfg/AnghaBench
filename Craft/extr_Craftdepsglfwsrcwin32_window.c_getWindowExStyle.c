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
struct TYPE_3__ {int /*<<< orphan*/  monitor; scalar_t__ decorated; } ;
typedef  TYPE_1__ _GLFWwindow ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  WS_EX_APPWINDOW ; 
 int /*<<< orphan*/  WS_EX_WINDOWEDGE ; 

__attribute__((used)) static DWORD getWindowExStyle(const _GLFWwindow* window)
{
    DWORD style = WS_EX_APPWINDOW;

    if (window->decorated && !window->monitor)
        style |= WS_EX_WINDOWEDGE;

    return style;
}