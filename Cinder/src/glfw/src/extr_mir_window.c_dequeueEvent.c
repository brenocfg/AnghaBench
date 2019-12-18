#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * tqh_first; } ;
struct TYPE_6__ {int /*<<< orphan*/  event_mutex; } ;
struct TYPE_8__ {TYPE_1__ mir; } ;
struct TYPE_7__ {TYPE_5__ head; } ;
typedef  TYPE_2__ EventQueue ;
typedef  int /*<<< orphan*/  EventNode ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static EventNode* dequeueEvent(EventQueue* queue)
{
    EventNode* node = NULL;

    pthread_mutex_lock(&_glfw.mir.event_mutex);

    node = queue->head.tqh_first;

    if (node)
        TAILQ_REMOVE(&queue->head, node, entries);

    pthread_mutex_unlock(&_glfw.mir.event_mutex);

    return node;
}