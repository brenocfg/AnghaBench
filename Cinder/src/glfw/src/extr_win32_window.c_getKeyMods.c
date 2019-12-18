#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int GLFW_MOD_ALT ; 
 int GLFW_MOD_CONTROL ; 
 int GLFW_MOD_SHIFT ; 
 int GLFW_MOD_SUPER ; 
 int GetKeyState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VK_CONTROL ; 
 int /*<<< orphan*/  VK_LWIN ; 
 int /*<<< orphan*/  VK_MENU ; 
 int /*<<< orphan*/  VK_RWIN ; 
 int /*<<< orphan*/  VK_SHIFT ; 

__attribute__((used)) static int getKeyMods(void)
{
    int mods = 0;

    if (GetKeyState(VK_SHIFT) & (1 << 31))
        mods |= GLFW_MOD_SHIFT;
    if (GetKeyState(VK_CONTROL) & (1 << 31))
        mods |= GLFW_MOD_CONTROL;
    if (GetKeyState(VK_MENU) & (1 << 31))
        mods |= GLFW_MOD_ALT;
    if ((GetKeyState(VK_LWIN) | GetKeyState(VK_RWIN)) & (1 << 31))
        mods |= GLFW_MOD_SUPER;

    return mods;
}