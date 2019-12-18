#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ pe_cmd; int pe_flags; char* pe_stub_app; size_t pe_stub_app_sz; } ;
typedef  TYPE_1__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 int LIBPE_F_FD_DONE ; 
 scalar_t__ PE_C_READ ; 
 int /*<<< orphan*/  errno ; 

int
ps_update_msdos_stub(PE *pe, char *dos_stub, size_t sz)
{

	if (pe == NULL || dos_stub == NULL || sz == 0) {
		errno = EINVAL;
		return (-1);
	}

	if (pe->pe_cmd == PE_C_READ || pe->pe_flags & LIBPE_F_FD_DONE) {
		errno = EACCES;
		return (-1);
	}

	pe->pe_stub_app = dos_stub;
	pe->pe_stub_app_sz = sz;

	return (0);
}