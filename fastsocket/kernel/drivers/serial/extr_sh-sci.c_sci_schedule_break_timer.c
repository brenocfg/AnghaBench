#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ expires; } ;
struct sci_port {TYPE_1__ break_timer; } ;

/* Variables and functions */
 scalar_t__ SCI_BREAK_JIFFIES ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 

__attribute__((used)) static void sci_schedule_break_timer(struct sci_port *port)
{
	port->break_timer.expires = jiffies + SCI_BREAK_JIFFIES;
	add_timer(&port->break_timer);
}