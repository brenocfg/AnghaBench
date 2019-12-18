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
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_5__ {int /*<<< orphan*/  event_mutex; int /*<<< orphan*/  event_cond; TYPE_1__* event_queue; } ;
struct TYPE_6__ {TYPE_2__ mir; } ;
struct TYPE_4__ {int /*<<< orphan*/  head; } ;
typedef  int /*<<< orphan*/  MirEvent ;
typedef  int /*<<< orphan*/  EventNode ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/ * newEventNode (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enqueueEvent(const MirEvent* event, _GLFWwindow* context)
{
    pthread_mutex_lock(&_glfw.mir.event_mutex);

    EventNode* new_node = newEventNode(event, context);
    TAILQ_INSERT_TAIL(&_glfw.mir.event_queue->head, new_node, entries);

    pthread_cond_signal(&_glfw.mir.event_cond);

    pthread_mutex_unlock(&_glfw.mir.event_mutex);
}