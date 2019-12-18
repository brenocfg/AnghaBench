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
typedef  int /*<<< orphan*/  __sighandler_t ;

/* Variables and functions */
 int SA_ONSTACK ; 
 int SA_RESTART ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGVTALRM ; 
 int /*<<< orphan*/  SIGWINCH ; 
 scalar_t__ alarm_handler ; 
 int /*<<< orphan*/  set_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void timer_init(void)
{
	set_handler(SIGVTALRM, (__sighandler_t) alarm_handler,
		    SA_ONSTACK | SA_RESTART, SIGUSR1, SIGIO, SIGWINCH, -1);
}