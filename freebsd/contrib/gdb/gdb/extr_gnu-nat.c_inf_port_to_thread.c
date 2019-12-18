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
struct proc {scalar_t__ port; struct proc* next; } ;
struct inf {struct proc* threads; } ;
typedef  scalar_t__ mach_port_t ;

/* Variables and functions */

struct proc *
inf_port_to_thread (struct inf *inf, mach_port_t port)
{
  struct proc *thread = inf->threads;
  while (thread)
    if (thread->port == port)
      return thread;
    else
      thread = thread->next;
  return 0;
}