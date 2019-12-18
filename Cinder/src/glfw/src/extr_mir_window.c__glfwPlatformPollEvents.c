#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  event_queue; } ;
struct TYPE_8__ {TYPE_1__ mir; } ;
struct TYPE_7__ {int /*<<< orphan*/  window; int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ EventNode ;

/* Variables and functions */
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  deleteNode (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* dequeueEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handleEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _glfwPlatformPollEvents(void)
{
    EventNode* node = NULL;

    while ((node = dequeueEvent(_glfw.mir.event_queue)))
    {
        handleEvent(node->event, node->window);
        deleteNode(_glfw.mir.event_queue, node);
    }
}