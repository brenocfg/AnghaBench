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
struct machine {int pid; } ;

/* Variables and functions */
 scalar_t__ machine__is_default_guest (struct machine*) ; 
 scalar_t__ machine__is_host (struct machine*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,...) ; 

char *machine__mmap_name(struct machine *machine, char *bf, size_t size)
{
	if (machine__is_host(machine))
		snprintf(bf, size, "[%s]", "kernel.kallsyms");
	else if (machine__is_default_guest(machine))
		snprintf(bf, size, "[%s]", "guest.kernel.kallsyms");
	else {
		snprintf(bf, size, "[%s.%d]", "guest.kernel.kallsyms",
			 machine->pid);
	}

	return bf;
}