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
struct _ps_strings {scalar_t__ val; } ;
typedef  int /*<<< orphan*/  _ps ;
typedef  void* CORE_ADDR ;

/* Variables and functions */
 int CTL_VM ; 
 int VM_PSSTRINGS ; 
 void* i386obsd_sigtramp_end_addr ; 
 void* i386obsd_sigtramp_start_addr ; 
 scalar_t__ sysctl (int*,int,struct _ps_strings*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
_initialize_i386obsd_nat (void)
{
  /* OpenBSD provides a vm.psstrings sysctl that we can use to locate
     the sigtramp.  That way we can still recognize a sigtramp if its
     location is changed in a new kernel.  This is especially
     important for OpenBSD, since it uses a different memory layout
     than NetBSD, yet we cannot distinguish between the two.

     Of course this is still based on the assumption that the sigtramp
     is placed directly under the location where the program arguments
     and environment can be found.  */
#ifdef VM_PSSTRINGS
  {
    struct _ps_strings _ps;
    int mib[2];
    size_t len;

    mib[0] = CTL_VM;
    mib[1] = VM_PSSTRINGS;
    len = sizeof (_ps);
    if (sysctl (mib, 2, &_ps, &len, NULL, 0) == 0)
      {
	i386obsd_sigtramp_start_addr = (CORE_ADDR)_ps.val - 128;
	i386obsd_sigtramp_end_addr = (CORE_ADDR)_ps.val;
      }
  }
#endif
}