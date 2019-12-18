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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int PIDGET (int /*<<< orphan*/ ) ; 
 struct inf* current_inferior ; 
 struct proc* inf_tid_to_thread (struct inf*,int) ; 
 char* proc_string (struct proc*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static char *
gnu_pid_to_str (ptid_t ptid)
{
  struct inf *inf = current_inferior;
  int tid = PIDGET (ptid);
  struct proc *thread = inf_tid_to_thread (inf, tid);

  if (thread)
    return proc_string (thread);
  else
    {
      static char tid_str[80];
      sprintf (tid_str, "bogus thread id %d", tid);
      return tid_str;
    }
}