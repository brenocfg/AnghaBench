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
typedef  int /*<<< orphan*/  MirInputEvent ;

/* Variables and functions */
 int /*<<< orphan*/  handleKeyEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handlePointerEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mir_input_event_get_keyboard_event (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  mir_input_event_get_pointer_event (int /*<<< orphan*/  const*) ; 
 int mir_input_event_get_type (int /*<<< orphan*/  const*) ; 
#define  mir_input_event_type_key 129 
#define  mir_input_event_type_pointer 128 

__attribute__((used)) static void handleInput(const MirInputEvent* input_event, _GLFWwindow* window)
{
    int type = mir_input_event_get_type(input_event);

    switch (type)
    {
        case mir_input_event_type_key:
            handleKeyEvent(mir_input_event_get_keyboard_event(input_event), window);
            break;
        case mir_input_event_type_pointer:
            handlePointerEvent(mir_input_event_get_pointer_event(input_event), window);
            break;
        default:
            break;
    }
}