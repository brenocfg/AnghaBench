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
struct epoll_event {int dummy; } ;

/* Variables and functions */
 int epoll_pwait (int,struct epoll_event*,int,int,int /*<<< orphan*/ ) ; 

int epoll_wait(int fd, struct epoll_event *ev, int cnt, int to)
{
	return epoll_pwait(fd, ev, cnt, to, 0);
}