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
struct netpoll {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netpoll_poll_dev (int /*<<< orphan*/ ) ; 

void netpoll_poll(struct netpoll *np)
{
	netpoll_poll_dev(np->dev);
}