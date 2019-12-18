#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* RIOHosts; } ;
struct TYPE_3__ {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  func_enter () ; 
 int /*<<< orphan*/  func_exit () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* p ; 
 int /*<<< orphan*/  rio_interrupt (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ rio_poll ; 

__attribute__((used)) static void rio_pollfunc(unsigned long data)
{
	func_enter();

	rio_interrupt(0, &p->RIOHosts[data]);
	mod_timer(&p->RIOHosts[data].timer, jiffies + rio_poll);

	func_exit();
}