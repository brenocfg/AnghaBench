#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int event_tail; int /*<<< orphan*/ * event; } ;
typedef  TYPE_1__ user_info_t ;
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int MAX_EVENTS ; 

__attribute__((used)) static event_t get_queued_event(user_info_t *user)
{
    user->event_tail = (user->event_tail+1) % MAX_EVENTS;
    return user->event[user->event_tail];
}