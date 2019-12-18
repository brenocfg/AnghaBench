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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  arg ;

/* Variables and functions */
 int EPERM ; 
 scalar_t__ PE_parse_boot_argn (char*,char*,int) ; 
 int copyin_update (int /*<<< orphan*/ ) ; 
 scalar_t__ global_update ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  xcpu_update () ; 

int
ucode_interface(uint64_t addr)
{
	int error;
	char arg[16]; 

	if (PE_parse_boot_argn("-x", arg, sizeof (arg))) {
		printf("ucode: no updates in safe mode\n");
		return EPERM;
	}

#if !DEBUG
	/*
	 * Userland may only call this once per boot. Anything else
	 * would not make sense (all updates are cumulative), and also
	 * leak memory, because we don't free previous updates.
	 */
	if (global_update)
		return EPERM;
#endif

	/* Get the whole microcode */
	error = copyin_update(addr);

	if (error)
		return error;

	/* Farm out the updates */
	xcpu_update();

	return 0;
}