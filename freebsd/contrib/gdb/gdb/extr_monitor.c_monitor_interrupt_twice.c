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

/* Variables and functions */
 int /*<<< orphan*/  monitor_interrupt ; 
 int /*<<< orphan*/  monitor_interrupt_query () ; 
 int /*<<< orphan*/  ofunc ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
monitor_interrupt_twice (int signo)
{
  signal (signo, ofunc);

  monitor_interrupt_query ();

  signal (signo, monitor_interrupt);
}