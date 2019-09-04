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
typedef  scalar_t__ WPARAM ;
struct TYPE_5__ {int* publicKeys; } ;
struct TYPE_7__ {TYPE_1__ win32; } ;
struct TYPE_6__ {scalar_t__ message; scalar_t__ wParam; int lParam; scalar_t__ time; } ;
typedef  TYPE_2__ MSG ;
typedef  int LPARAM ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int GLFW_KEY_LEFT_CONTROL ; 
 int GLFW_KEY_RIGHT_CONTROL ; 
 scalar_t__ GetMessageTime () ; 
 int HIWORD (int) ; 
 int /*<<< orphan*/  PM_NOREMOVE ; 
 scalar_t__ PeekMessageW (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VK_CONTROL ; 
 scalar_t__ VK_MENU ; 
 scalar_t__ WM_KEYDOWN ; 
 scalar_t__ WM_KEYUP ; 
 scalar_t__ WM_SYSKEYDOWN ; 
 scalar_t__ WM_SYSKEYUP ; 
 int _GLFW_KEY_INVALID ; 
 TYPE_3__ _glfw ; 

__attribute__((used)) static int translateKey(WPARAM wParam, LPARAM lParam)
{
    if (wParam == VK_CONTROL)
    {
        // The CTRL keys require special handling

        MSG next;
        DWORD time;

        // Is this an extended key (i.e. right key)?
        if (lParam & 0x01000000)
            return GLFW_KEY_RIGHT_CONTROL;

        // Here is a trick: "Alt Gr" sends LCTRL, then RALT. We only
        // want the RALT message, so we try to see if the next message
        // is a RALT message. In that case, this is a false LCTRL!
        time = GetMessageTime();

        if (PeekMessageW(&next, NULL, 0, 0, PM_NOREMOVE))
        {
            if (next.message == WM_KEYDOWN ||
                next.message == WM_SYSKEYDOWN ||
                next.message == WM_KEYUP ||
                next.message == WM_SYSKEYUP)
            {
                if (next.wParam == VK_MENU &&
                    (next.lParam & 0x01000000) &&
                    next.time == time)
                {
                    // Next message is a RALT down message, which
                    // means that this is not a proper LCTRL message
                    return _GLFW_KEY_INVALID;
                }
            }
        }

        return GLFW_KEY_LEFT_CONTROL;
    }

    return _glfw.win32.publicKeys[HIWORD(lParam) & 0x1FF];
}