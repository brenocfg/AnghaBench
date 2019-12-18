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
struct inf {int traced; int /*<<< orphan*/  pid; TYPE_1__* task; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  scalar_t__ error_t ;
struct TYPE_2__ {int /*<<< orphan*/  dead; } ;

/* Variables and functions */
 scalar_t__ EIEIO ; 
 scalar_t__ INF_RESUME_MSGPORT_RPC (struct inf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_TRACEMASK ; 
 int /*<<< orphan*/  msg_set_init_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgport ; 
 int /*<<< orphan*/  refport ; 
 char* safe_strerror (scalar_t__) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,char*) ; 

void
inf_set_traced (struct inf *inf, int on)
{
  if (on == inf->traced)
    return;
  
  if (inf->task && !inf->task->dead)
    /* Make it take effect immediately.  */
    {
      sigset_t mask = on ? ~(sigset_t) 0 : 0;
      error_t err =
	INF_RESUME_MSGPORT_RPC (inf, msg_set_init_int (msgport, refport,
						       INIT_TRACEMASK, mask));
      if (err == EIEIO)
	{
	  if (on)
	    warning ("Can't modify tracing state for pid %d: %s",
		     inf->pid, "No signal thread");
	  inf->traced = on;
	}
      else if (err)
	warning ("Can't modify tracing state for pid %d: %s",
		 inf->pid, safe_strerror (err));
      else
	inf->traced = on;
    }
  else
    inf->traced = on;
}