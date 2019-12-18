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
struct TYPE_4__ {int pe_stub_ex; int pe_flags; char* pe_stub; } ;
typedef  int /*<<< orphan*/  PE_DosHdr ;
typedef  TYPE_1__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int LIBPE_F_LOAD_DOS_STUB ; 
 int LIBPE_F_SPECIAL_FILE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  libpe_read_msdos_stub (TYPE_1__*) ; 

char *
pe_msdos_stub(PE *pe, size_t *len)
{

	if (pe == NULL || len == NULL) {
		errno = EINVAL;
		return (NULL);
	}

	if (pe->pe_stub_ex > 0 &&
	    (pe->pe_flags & LIBPE_F_LOAD_DOS_STUB) == 0) {
		assert((pe->pe_flags & LIBPE_F_SPECIAL_FILE) == 0);
		(void) libpe_read_msdos_stub(pe);
	}

	*len = sizeof(PE_DosHdr) + pe->pe_stub_ex;

	return (pe->pe_stub);
}