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
typedef  int /*<<< orphan*/  _GLFWwindow ;
typedef  int /*<<< orphan*/  MirKeyboardEvent ;

/* Variables and functions */
 int const GLFW_MOD_ALT ; 
 int const GLFW_MOD_CONTROL ; 
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 int /*<<< orphan*/  _glfwInputChar (int /*<<< orphan*/ *,long const,int const,int const) ; 
 int /*<<< orphan*/  _glfwInputKey (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int const,int const) ; 
 long _glfwKeySym2Unicode (int const) ; 
 int mirModToGLFWMod (int const) ; 
 int const mir_keyboard_action_up ; 
 int mir_keyboard_event_action (int /*<<< orphan*/  const*) ; 
 int mir_keyboard_event_key_code (int /*<<< orphan*/  const*) ; 
 int mir_keyboard_event_modifiers (int /*<<< orphan*/  const*) ; 
 int mir_keyboard_event_scan_code (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  toGLFWKeyCode (int const) ; 

__attribute__((used)) static void handleKeyEvent(const MirKeyboardEvent* key_event, _GLFWwindow* window)
{
    const int action    = mir_keyboard_event_action   (key_event);
    const int scan_code = mir_keyboard_event_scan_code(key_event);
    const int key_code  = mir_keyboard_event_key_code (key_event);
    const int modifiers = mir_keyboard_event_modifiers(key_event);

    const int  pressed = action == mir_keyboard_action_up ? GLFW_RELEASE : GLFW_PRESS;
    const int  mods    = mirModToGLFWMod(modifiers);
    const long text    = _glfwKeySym2Unicode(key_code);
    const int  plain   = !(mods & (GLFW_MOD_CONTROL | GLFW_MOD_ALT));

    _glfwInputKey(window, toGLFWKeyCode(scan_code), scan_code, pressed, mods);

    if (text != -1)
        _glfwInputChar(window, text, mods, plain);
}