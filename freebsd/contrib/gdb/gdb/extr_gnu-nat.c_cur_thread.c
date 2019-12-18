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
struct proc {int dummy; } ;
struct inf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 struct inf* cur_inf () ; 
 int /*<<< orphan*/  error (char*) ; 
 struct proc* inf_tid_to_thread (struct inf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 

__attribute__((used)) static struct proc *
cur_thread (void)
{
  struct inf *inf = cur_inf ();
  struct proc *thread = inf_tid_to_thread (inf, PIDGET (inferior_ptid));
  if (!thread)
    error ("No current thread.");
  return thread;
}