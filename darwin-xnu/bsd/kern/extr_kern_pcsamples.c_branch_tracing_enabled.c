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
struct proc {int p_btrace; } ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 struct proc* current_proc () ; 
 scalar_t__ pc_trace_frameworks ; 

int
branch_tracing_enabled(void)
{
  struct proc *p = current_proc();
  if (TRUE == pc_trace_frameworks) return TRUE;
  if (p) {
    return (p->p_btrace);
  }
  return 0;
}