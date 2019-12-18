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
struct TYPE_3__ {int /*<<< orphan*/  pe_flags; } ;
typedef  scalar_t__ PE_Cmd ;
typedef  TYPE_1__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LIBPE_F_DIRTY_COFF_HEADER ; 
 scalar_t__ PE_C_CLR ; 
 scalar_t__ PE_C_SET ; 
 unsigned int PE_F_DIRTY ; 
 int /*<<< orphan*/  errno ; 

int
pe_flag_coff_header(PE *pe, PE_Cmd c, unsigned int flags)
{

	if (pe == NULL || (c != PE_C_SET && c != PE_C_CLR) ||
	    (flags & ~PE_F_DIRTY) != 0) {
		errno = EINVAL;
		return (-1);
	}

	if (c == PE_C_SET)
		pe->pe_flags |= LIBPE_F_DIRTY_COFF_HEADER;
	else
		pe->pe_flags &= ~LIBPE_F_DIRTY_COFF_HEADER;

	return (0);
}