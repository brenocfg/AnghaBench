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
typedef  int /*<<< orphan*/  vm_address_t ;
struct procinfo {int state; } ;
struct inf {int stopped; int nomsg; int traced; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  procinfo_t ;
typedef  scalar_t__ mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  error_t ;

/* Variables and functions */
 int PI_NOMSG ; 
 int PI_STOPPED ; 
 int PI_TRACED ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  proc_getprocinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,scalar_t__*,char**,scalar_t__*) ; 
 int /*<<< orphan*/  proc_server ; 
 int /*<<< orphan*/  vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
inf_validate_procinfo (struct inf *inf)
{
  char *noise;
  mach_msg_type_number_t noise_len = 0;
  struct procinfo *pi;
  mach_msg_type_number_t pi_len = 0;
  int info_flags = 0;
  error_t err =
  proc_getprocinfo (proc_server, inf->pid, &info_flags,
		    (procinfo_t *) &pi, &pi_len, &noise, &noise_len);

  if (!err)
    {
      inf->stopped = !!(pi->state & PI_STOPPED);
      inf->nomsg = !!(pi->state & PI_NOMSG);
      if (inf->nomsg)
	inf->traced = !!(pi->state & PI_TRACED);
      vm_deallocate (mach_task_self (), (vm_address_t) pi, pi_len);
      if (noise_len > 0)
	vm_deallocate (mach_task_self (), (vm_address_t) noise, noise_len);
    }
}