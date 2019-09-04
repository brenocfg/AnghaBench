#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xkb_keysym_t ;
typedef  scalar_t__ uint32_t ;
struct wl_keyboard {int dummy; } ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_4__ {int modifiers; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_1__ xkb; int /*<<< orphan*/ * keyboardFocus; } ;
struct TYPE_6__ {TYPE_2__ wl; } ;

/* Variables and functions */
 int const GLFW_MOD_ALT ; 
 int const GLFW_MOD_CONTROL ; 
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 scalar_t__ WL_KEYBOARD_KEY_STATE_PRESSED ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  _glfwInputChar (int /*<<< orphan*/ *,long,int const,int const) ; 
 int /*<<< orphan*/  _glfwInputKey (int /*<<< orphan*/ *,int,scalar_t__,int,int) ; 
 long _glfwKeySym2Unicode (int /*<<< orphan*/  const) ; 
 int toGLFWKeyCode (scalar_t__) ; 
 scalar_t__ xkb_key_get_syms (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static void keyboardHandleKey(void* data,
                              struct wl_keyboard* keyboard,
                              uint32_t serial,
                              uint32_t time,
                              uint32_t key,
                              uint32_t state)
{
    uint32_t code, num_syms;
    long cp;
    int keyCode;
    int action;
    const xkb_keysym_t *syms;
    _GLFWwindow* window = _glfw.wl.keyboardFocus;

    if (!window)
        return;

    keyCode = toGLFWKeyCode(key);
    action = state == WL_KEYBOARD_KEY_STATE_PRESSED
            ? GLFW_PRESS : GLFW_RELEASE;

    _glfwInputKey(window, keyCode, key, action,
                  _glfw.wl.xkb.modifiers);

    code = key + 8;
    num_syms = xkb_key_get_syms(_glfw.wl.xkb.state, code, &syms);

    if (num_syms == 1)
    {
        cp = _glfwKeySym2Unicode(syms[0]);
        if (cp != -1)
        {
            const int mods = _glfw.wl.xkb.modifiers;
            const int plain = !(mods & (GLFW_MOD_CONTROL | GLFW_MOD_ALT));
            _glfwInputChar(window, cp, mods, plain);
        }
    }
}