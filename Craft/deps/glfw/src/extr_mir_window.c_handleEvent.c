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
typedef  int /*<<< orphan*/  MirEvent ;

/* Variables and functions */
 int /*<<< orphan*/  handleInput (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mir_event_get_input_event (int /*<<< orphan*/  const*) ; 
 int mir_event_get_type (int /*<<< orphan*/  const*) ; 
#define  mir_event_type_input 128 

__attribute__((used)) static void handleEvent(const MirEvent* event, _GLFWwindow* window)
{
    int type = mir_event_get_type(event);

    switch (type)
    {
        case mir_event_type_input:
            handleInput(mir_event_get_input_event(event), window);
            break;
        default:
            break;
    }
}