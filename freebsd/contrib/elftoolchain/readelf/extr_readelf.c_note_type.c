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

/* Variables and functions */
 unsigned int ET_CORE ; 
 char const* note_type_freebsd (unsigned int) ; 
 char const* note_type_freebsd_core (unsigned int) ; 
 char const* note_type_gnu (unsigned int) ; 
 char const* note_type_linux_core (unsigned int) ; 
 char const* note_type_netbsd (unsigned int) ; 
 char const* note_type_openbsd (unsigned int) ; 
 char const* note_type_unknown (unsigned int) ; 
 char const* note_type_xen (unsigned int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static const char *
note_type(const char *name, unsigned int et, unsigned int nt)
{
	if ((strcmp(name, "CORE") == 0 || strcmp(name, "LINUX") == 0) &&
	    et == ET_CORE)
		return note_type_linux_core(nt);
	else if (strcmp(name, "FreeBSD") == 0)
		if (et == ET_CORE)
			return note_type_freebsd_core(nt);
		else
			return note_type_freebsd(nt);
	else if (strcmp(name, "GNU") == 0 && et != ET_CORE)
		return note_type_gnu(nt);
	else if (strcmp(name, "NetBSD") == 0 && et != ET_CORE)
		return note_type_netbsd(nt);
	else if (strcmp(name, "OpenBSD") == 0 && et != ET_CORE)
		return note_type_openbsd(nt);
	else if (strcmp(name, "Xen") == 0 && et != ET_CORE)
		return note_type_xen(nt);
	return note_type_unknown(nt);
}