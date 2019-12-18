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
struct gameport {int /*<<< orphan*/  poll_interval; int /*<<< orphan*/  poll_timer; scalar_t__ poll_cnt; int /*<<< orphan*/  (* poll_handler ) (struct gameport*) ;} ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct gameport*) ; 

__attribute__((used)) static void gameport_run_poll_handler(unsigned long d)
{
	struct gameport *gameport = (struct gameport *)d;

	gameport->poll_handler(gameport);
	if (gameport->poll_cnt)
		mod_timer(&gameport->poll_timer, jiffies + msecs_to_jiffies(gameport->poll_interval));
}