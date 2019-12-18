#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct _Elf_Extent_List {int dummy; } ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {scalar_t__ e_kind; int e_class; scalar_t__ e_version; scalar_t__ e_cmd; scalar_t__ e_fd; int /*<<< orphan*/  e_flags; } ;
typedef  scalar_t__ Elf_Cmd ;
typedef  TYPE_1__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int /*<<< orphan*/  CLASS ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_C_NULL ; 
 scalar_t__ ELF_C_READ ; 
 scalar_t__ ELF_C_WRITE ; 
 scalar_t__ ELF_K_ELF ; 
 scalar_t__ EV_CURRENT ; 
 scalar_t__ EV_NONE ; 
 int /*<<< orphan*/  LIBELF_F_SHDRS_LOADED ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE ; 
 int /*<<< orphan*/  SEQUENCE ; 
 int /*<<< orphan*/  SLIST_INIT (struct _Elf_Extent_List*) ; 
 int /*<<< orphan*/  _libelf_release_extents (struct _Elf_Extent_List*) ; 
 scalar_t__ _libelf_resync_elf (TYPE_1__*,struct _Elf_Extent_List*) ; 
 scalar_t__ _libelf_write_elf (TYPE_1__*,scalar_t__,struct _Elf_Extent_List*) ; 

off_t
elf_update(Elf *e, Elf_Cmd c)
{
	int ec;
	off_t rc;
	struct _Elf_Extent_List extents;

	rc = (off_t) -1;

	if (e == NULL || e->e_kind != ELF_K_ELF ||
	    (c != ELF_C_NULL && c != ELF_C_WRITE)) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (rc);
	}

	if ((ec = e->e_class) != ELFCLASS32 && ec != ELFCLASS64) {
		LIBELF_SET_ERROR(CLASS, 0);
		return (rc);
	}

	if (e->e_version == EV_NONE)
		e->e_version = EV_CURRENT;

	if (c == ELF_C_WRITE && e->e_cmd == ELF_C_READ) {
		LIBELF_SET_ERROR(MODE, 0);
		return (rc);
	}

	SLIST_INIT(&extents);

	if ((rc = _libelf_resync_elf(e, &extents)) < 0)
		goto done;

	if (c == ELF_C_NULL)
		goto done;

	if (e->e_fd < 0) {
		rc = (off_t) -1;
		LIBELF_SET_ERROR(SEQUENCE, 0);
		goto done;
	}

	rc = _libelf_write_elf(e, rc, &extents);

done:
	_libelf_release_extents(&extents);
	e->e_flags &= ~LIBELF_F_SHDRS_LOADED;
	return (rc);
}