#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int pe_flags; } ;
struct TYPE_10__ {int ps_flags; TYPE_3__* ps_pe; } ;
struct TYPE_9__ {int sb_flags; } ;
typedef  TYPE_1__ PE_SecBuf ;
typedef  TYPE_2__ PE_Scn ;
typedef  int /*<<< orphan*/  PE_Buffer ;
typedef  TYPE_3__ PE ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 int LIBPE_F_FD_DONE ; 
 int LIBPE_F_LOAD_SECTION ; 
 int PE_F_DIRTY ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* libpe_alloc_buffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ libpe_load_section (TYPE_3__*,TYPE_2__*) ; 

PE_Buffer *
pe_newbuffer(PE_Scn *ps)
{
	PE *pe;
	PE_SecBuf *sb;

	if (ps == NULL) {
		errno = EINVAL;
		return (NULL);
	}

	pe = ps->ps_pe;

	if (pe->pe_flags & LIBPE_F_FD_DONE) {
		errno = EACCES;
		return (NULL);
	}

	if ((ps->ps_flags & LIBPE_F_LOAD_SECTION) == 0) {
		if (libpe_load_section(pe, ps) < 0)
			return (NULL);
	}

	if ((sb = libpe_alloc_buffer(ps, 0)) == NULL)
		return (NULL);

	sb->sb_flags |= PE_F_DIRTY;
	ps->ps_flags |= PE_F_DIRTY;

	return ((PE_Buffer *) sb);
}