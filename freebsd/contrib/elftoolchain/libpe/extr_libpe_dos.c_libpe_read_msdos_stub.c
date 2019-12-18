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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {scalar_t__ pe_stub_ex; int pe_flags; void* pe_stub; int /*<<< orphan*/  pe_fd; } ;
typedef  int /*<<< orphan*/  PE_DosHdr ;
typedef  TYPE_1__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int LIBPE_F_LOAD_DOS_STUB ; 
 int LIBPE_F_SPECIAL_FILE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  libpe_parse_rich_header (TYPE_1__*) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int /*<<< orphan*/ ,void*,scalar_t__) ; 
 void* realloc (void*,scalar_t__) ; 

int
libpe_read_msdos_stub(PE *pe)
{
	void *m;

	assert(pe->pe_stub_ex > 0 &&
	    (pe->pe_flags & LIBPE_F_LOAD_DOS_STUB) == 0);

	if ((pe->pe_flags & LIBPE_F_SPECIAL_FILE) == 0) {
		if (lseek(pe->pe_fd, (off_t) sizeof(PE_DosHdr), SEEK_SET) <
		    0) {
			errno = EIO;
			goto fail;
		}
	}

	if ((m = realloc(pe->pe_stub, sizeof(PE_DosHdr) + pe->pe_stub_ex)) ==
	    NULL) {
		errno = ENOMEM;
		goto fail;
	}
	pe->pe_stub = m;

	if (read(pe->pe_fd, pe->pe_stub + sizeof(PE_DosHdr), pe->pe_stub_ex) !=
	    (ssize_t) pe->pe_stub_ex) {
		errno = EIO;
		goto fail;
	}

	pe->pe_flags |= LIBPE_F_LOAD_DOS_STUB;

	/* Search for the Rich header embedded just before the PE header. */
	(void) libpe_parse_rich_header(pe);

	return (0);

fail:
	pe->pe_stub_ex = 0;

	return (-1);
}