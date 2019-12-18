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
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/ * host_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  Debugger (char*) ; 
 int /*<<< orphan*/ * HOST_PRIV_NULL ; 
 int HOST_REBOOT_DEBUGGER ; 
 int HOST_REBOOT_HALT ; 
 int HOST_REBOOT_UPSDELAY ; 
 int /*<<< orphan*/  KERN_INVALID_HOST ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PEHaltRestart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  halt_all_cpus (int) ; 
 int /*<<< orphan*/  kPEUPSDelayHaltCPU ; 
 int /*<<< orphan*/  realhost ; 

kern_return_t
host_reboot(
	host_priv_t		host_priv,
	int				options)
{
	if (host_priv == HOST_PRIV_NULL)
		return (KERN_INVALID_HOST);

	assert(host_priv == &realhost);

#if DEVELOPMENT || DEBUG
	if (options & HOST_REBOOT_DEBUGGER) {
		Debugger("Debugger");
		return (KERN_SUCCESS);
	}
#endif

    if (options & HOST_REBOOT_UPSDELAY) {
        // UPS power cutoff path
        PEHaltRestart( kPEUPSDelayHaltCPU );
    } else {
       halt_all_cpus(!(options & HOST_REBOOT_HALT));
    }

	return (KERN_SUCCESS);
}