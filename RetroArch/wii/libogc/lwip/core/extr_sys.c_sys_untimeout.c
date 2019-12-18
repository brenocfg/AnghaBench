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
typedef  scalar_t__ sys_timeout_handler ;
struct sys_timeouts {struct sys_timeout* next; } ;
struct sys_timeout {scalar_t__ h; void* arg; scalar_t__ time; struct sys_timeout* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMP_SYS_TIMEOUT ; 
 int /*<<< orphan*/  memp_free (int /*<<< orphan*/ ,struct sys_timeout*) ; 
 struct sys_timeouts* sys_arch_timeouts () ; 

void
sys_untimeout(sys_timeout_handler h, void *arg)
{
    struct sys_timeouts *timeouts;
    struct sys_timeout *prev_t, *t;

    timeouts = sys_arch_timeouts();

    if (timeouts->next == NULL)
        return;

    for (t = timeouts->next, prev_t = NULL; t != NULL; prev_t = t, t = t->next)
    {
        if ((t->h == h) && (t->arg == arg))
        {
            /* We have a match */
            /* Unlink from previous in list */
            if (prev_t == NULL)
                timeouts->next = t->next;
            else
                prev_t->next = t->next;
            /* If not the last one, add time of this one back to next */
            if (t->next != NULL)
                t->next->time += t->time;
            memp_free(MEMP_SYS_TIMEOUT, t);
            return;
        }
    }
    return;
}