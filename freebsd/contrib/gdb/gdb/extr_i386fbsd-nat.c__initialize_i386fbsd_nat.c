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
typedef  void* u_long ;
typedef  int /*<<< orphan*/  ps_strings ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_PS_STRINGS ; 
 void* i386fbsd_sigtramp_end_addr ; 
 void* i386fbsd_sigtramp_start_addr ; 
 scalar_t__ sysctl (int*,int,void**,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
_initialize_i386fbsd_nat (void)
{
  /* FreeBSD provides a kern.ps_strings sysctl that we can use to
     locate the sigtramp.  That way we can still recognize a sigtramp
     if its location is changed in a new kernel.  Of course this is
     still based on the assumption that the sigtramp is placed
     directly under the location where the program arguments and
     environment can be found.  */
#ifdef KERN_PS_STRINGS
  {
    int mib[2];
    u_long ps_strings;
    size_t len;

    mib[0] = CTL_KERN;
    mib[1] = KERN_PS_STRINGS;
    len = sizeof (ps_strings);
    if (sysctl (mib, 2, &ps_strings, &len, NULL, 0) == 0)
      {
	i386fbsd_sigtramp_start_addr = ps_strings - 128;
	i386fbsd_sigtramp_end_addr = ps_strings;
      }
  }
#endif
}