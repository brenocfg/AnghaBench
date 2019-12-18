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
struct _Libelf_Data {unsigned int d_flags; } ;
typedef  int /*<<< orphan*/  Elf_Data ;
typedef  scalar_t__ Elf_Cmd ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 scalar_t__ ELF_C_CLR ; 
 scalar_t__ ELF_C_SET ; 
 unsigned int ELF_F_DIRTY ; 
 unsigned int LIBELF_F_API_MASK ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int
elf_flagdata(Elf_Data *d, Elf_Cmd c, unsigned int flags)
{
	unsigned int r;
	struct _Libelf_Data *ld;

	if (d == NULL)
		return (0);

	if ((c != ELF_C_SET && c != ELF_C_CLR) ||
	    (flags & ~ELF_F_DIRTY) != 0) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	ld = (struct _Libelf_Data *) d;

	if (c == ELF_C_SET)
		r = ld->d_flags |= flags;
	else
		r = ld->d_flags &= ~flags;

	return (r & LIBELF_F_API_MASK);
}