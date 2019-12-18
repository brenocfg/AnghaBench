#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ pe_cmd; int pe_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  ps_sh; TYPE_2__* ps_pe; } ;
typedef  int /*<<< orphan*/  PE_SecHdr ;
typedef  TYPE_1__ PE_Scn ;
typedef  TYPE_2__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 int LIBPE_F_DIRTY_SEC_HEADER ; 
 int LIBPE_F_FD_DONE ; 
 scalar_t__ PE_C_READ ; 
 int /*<<< orphan*/  errno ; 

int
pe_update_section_header(PE_Scn *ps, PE_SecHdr *sh)
{
	PE *pe;

	if (ps == NULL || sh == NULL) {
		errno = EINVAL;
		return (-1);
	}

	pe = ps->ps_pe;

	if (pe->pe_cmd == PE_C_READ || pe->pe_flags & LIBPE_F_FD_DONE) {
		errno = EACCES;
		return (-1);
	}

	ps->ps_sh = *sh;
	pe->pe_flags |= LIBPE_F_DIRTY_SEC_HEADER;

	return (0);
}