#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sig; } ;
struct TYPE_5__ {TYPE_1__ value; int /*<<< orphan*/  kind; } ;
struct TYPE_6__ {int suppress; TYPE_2__ status; } ;
struct inf {int stopped; TYPE_3__ wait; } ;
typedef  int /*<<< orphan*/  mach_port_t ;
typedef  scalar_t__ error_t ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  TARGET_SIGNAL_0 ; 
 int /*<<< orphan*/  TARGET_WAITKIND_STOPPED ; 
 int /*<<< orphan*/  safe_strerror (scalar_t__) ; 
 struct inf* waiting_inf ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

error_t
S_msg_sig_post_untraced_reply (mach_port_t reply, error_t err)
{
  struct inf *inf = waiting_inf;

  if (err == EBUSY)
    /* EBUSY is what we get when the crash server has grabbed control of the
       process and doesn't like what signal we tried to send it.  Just act
       like the process stopped (using a signal of 0 should mean that the
       *next* time the user continues, it will pass signal 0, which the crash
       server should like).  */
    {
      inf->wait.status.kind = TARGET_WAITKIND_STOPPED;
      inf->wait.status.value.sig = TARGET_SIGNAL_0;
    }
  else if (err)
    warning ("Signal delivery failed: %s", safe_strerror (err));

  if (err)
    /* We only get this reply when we've posted a signal to a process which we
       thought was stopped, and which we expected to continue after the signal.
       Given that the signal has failed for some reason, it's reasonable to
       assume it's still stopped.  */
    inf->stopped = 1;
  else
    inf->wait.suppress = 1;

  return 0;
}