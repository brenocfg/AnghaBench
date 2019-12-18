#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  pe_cmd; int /*<<< orphan*/  pe_flags; } ;
typedef  int PE_Cmd ;
typedef  TYPE_1__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LIBPE_F_FD_DONE ; 
#define  PE_C_FDDONE 129 
#define  PE_C_FDREAD 128 
 int /*<<< orphan*/  PE_C_WRITE ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  libpe_load_all_sections (TYPE_1__*) ; 

int
pe_cntl(PE *pe, PE_Cmd cmd)
{

	if (pe == NULL) {
		errno = EINVAL;
		return (-1);
	}

	switch (cmd) {
	case PE_C_FDDONE:
		pe->pe_flags |= LIBPE_F_FD_DONE;
		break;

	case PE_C_FDREAD:
		if (pe->pe_cmd == PE_C_WRITE) {
			errno = EACCES;
			return (-1);
		}
		if (libpe_load_all_sections(pe) < 0)
			return (-1);
		break;

	default:
		errno = EINVAL;
		return (-1);
	}

	return (0);
}