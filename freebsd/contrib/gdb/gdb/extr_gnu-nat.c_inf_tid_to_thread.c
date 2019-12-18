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
struct proc {int tid; struct proc* next; } ;
struct inf {struct proc* threads; } ;

/* Variables and functions */

struct proc *
inf_tid_to_thread (struct inf *inf, int tid)
{
  struct proc *thread = inf->threads;

  while (thread)
    if (thread->tid == tid)
      return thread;
    else
      thread = thread->next;
  return 0;
}