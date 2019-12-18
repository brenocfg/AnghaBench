#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_14__ {int pe_flags; int /*<<< orphan*/  pe_fd; } ;
struct TYPE_11__ {scalar_t__ sh_rawsize; scalar_t__ sh_rawptr; } ;
struct TYPE_13__ {int ps_flags; int ps_ndx; TYPE_2__ ps_sh; } ;
struct TYPE_10__ {char* pb_buf; } ;
struct TYPE_12__ {TYPE_1__ sb_pb; } ;
typedef  TYPE_2__ PE_SecHdr ;
typedef  TYPE_3__ PE_SecBuf ;
typedef  TYPE_4__ PE_Scn ;
typedef  TYPE_5__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 int LIBPE_F_LOAD_SECTION ; 
 int LIBPE_F_SPECIAL_FILE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  errno ; 
 size_t le32dec (char*) ; 
 TYPE_3__* libpe_alloc_buffer (TYPE_4__*,size_t) ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,size_t) ; 

int
libpe_load_section(PE *pe, PE_Scn *ps)
{
	PE_SecHdr *sh;
	PE_SecBuf *sb;
	size_t sz;
	char tmp[4];

	assert(pe != NULL && ps != NULL);
	assert((ps->ps_flags & LIBPE_F_LOAD_SECTION) == 0);

	sh = &ps->ps_sh;

	/* Allocate a PE_SecBuf struct without buffer for empty sections. */
	if (sh->sh_rawsize == 0) {
		(void) libpe_alloc_buffer(ps, 0);
		ps->ps_flags |= LIBPE_F_LOAD_SECTION;
		return (0);
	}

	if ((pe->pe_flags & LIBPE_F_SPECIAL_FILE) == 0) {
		if (lseek(pe->pe_fd, (off_t) sh->sh_rawptr, SEEK_SET) < 0) {
			errno = EIO;
			return (-1);
		}
	}

	if ((sb = libpe_alloc_buffer(ps, sh->sh_rawsize)) == NULL)
		return (-1);

	if (read(pe->pe_fd, sb->sb_pb.pb_buf, sh->sh_rawsize) !=
	    (ssize_t) sh->sh_rawsize) {
		errno = EIO;
		return (-1);
	}

	if (ps->ps_ndx == 0xFFFFFFFFU) {
		/*
		 * Index 0xFFFFFFFF indicates this section is a pseudo
		 * section that contains the COFF symbol table. We should
		 * read in the string table right after it.
		 */
		if (read(pe->pe_fd, tmp, sizeof(tmp)) !=
		    (ssize_t) sizeof(tmp)) {
			errno = EIO;
			return (-1);
		}
		sz = le32dec(tmp);

		/*
		 * The minimum value for the size field is 4, which indicates
		 * there is no string table.
		 */
		if (sz > 4) {
			sz -= 4;
			if ((sb = libpe_alloc_buffer(ps, sz)) == NULL)
				return (-1);
			if (read(pe->pe_fd, sb->sb_pb.pb_buf, sz) !=
			    (ssize_t) sz) {
				errno = EIO;
				return (-1);
			}
		}
	}

	ps->ps_flags |= LIBPE_F_LOAD_SECTION;

	return (0);
}