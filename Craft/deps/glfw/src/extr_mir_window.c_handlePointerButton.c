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
typedef  int /*<<< orphan*/  MirPointerEvent ;
typedef  int MirPointerButton ;

/* Variables and functions */
 int GLFW_MOUSE_BUTTON_4 ; 
 int GLFW_MOUSE_BUTTON_5 ; 
 int GLFW_MOUSE_BUTTON_LEFT ; 
 int GLFW_MOUSE_BUTTON_MIDDLE ; 
 int GLFW_MOUSE_BUTTON_RIGHT ; 
 int /*<<< orphan*/  _glfwInputMouseClick (int /*<<< orphan*/ *,int,int,int const) ; 
 int mirModToGLFWMod (int) ; 
#define  mir_pointer_button_back 132 
#define  mir_pointer_button_forward 131 
#define  mir_pointer_button_primary 130 
#define  mir_pointer_button_secondary 129 
#define  mir_pointer_button_tertiary 128 
 int mir_pointer_event_buttons (int /*<<< orphan*/  const*) ; 
 int mir_pointer_event_modifiers (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void handlePointerButton(_GLFWwindow* window,
                              int pressed,
                              const MirPointerEvent* pointer_event)
{
    MirPointerButton button = mir_pointer_event_buttons  (pointer_event);
    int mods                = mir_pointer_event_modifiers(pointer_event);
    const int publicMods    = mirModToGLFWMod(mods);
    int publicButton;

    switch (button)
    {
        case mir_pointer_button_primary:
            publicButton = GLFW_MOUSE_BUTTON_LEFT;
            break;
        case mir_pointer_button_secondary:
            publicButton = GLFW_MOUSE_BUTTON_RIGHT;
            break;
        case mir_pointer_button_tertiary:
            publicButton = GLFW_MOUSE_BUTTON_MIDDLE;
            break;
        case mir_pointer_button_forward:
            // FIXME What is the forward button?
            publicButton = GLFW_MOUSE_BUTTON_4;
            break;
        case mir_pointer_button_back:
            // FIXME What is the back button?
            publicButton = GLFW_MOUSE_BUTTON_5;
            break;
        default:
            break;
    }

    _glfwInputMouseClick(window, publicButton, pressed, publicMods);
}