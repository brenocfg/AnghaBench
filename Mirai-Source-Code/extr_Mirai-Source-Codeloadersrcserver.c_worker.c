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
struct server_worker {int /*<<< orphan*/  efd; int /*<<< orphan*/  thread_id; } ;
struct epoll_event {int dummy; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  bind_core (int /*<<< orphan*/ ) ; 
 int epoll_wait (int /*<<< orphan*/ ,struct epoll_event*,int,int) ; 
 int /*<<< orphan*/  handle_event (struct server_worker*,struct epoll_event*) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void *worker(void *arg)
{
    struct server_worker *wrker = (struct server_worker *)arg;
    struct epoll_event events[128];

    bind_core(wrker->thread_id);

    while (TRUE)
    {
        int i, n = epoll_wait(wrker->efd, events, 127, -1);

        if (n == -1)
            perror("epoll_wait");

        for (i = 0; i < n; i++)
            handle_event(wrker, &events[i]);
    }
}