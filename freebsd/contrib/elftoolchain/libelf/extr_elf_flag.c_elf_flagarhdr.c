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
struct TYPE_3__ {unsigned int ar_flags; } ;
typedef  scalar_t__ Elf_Cmd ;
typedef  TYPE_1__ Elf_Arhdr ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 scalar_t__ ELF_C_CLR ; 
 scalar_t__ ELF_C_SET ; 
 unsigned int ELF_F_DIRTY ; 
 unsigned int LIBELF_F_API_MASK ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

unsigned int
elf_flagarhdr(Elf_Arhdr *a, Elf_Cmd c, unsigned int flags)
{
	unsigned int r;

	if (a == NULL)
		return (0);

	if ((c != ELF_C_SET && c != ELF_C_CLR) ||
	    (flags & ~ELF_F_DIRTY) != 0) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	if (c == ELF_C_SET)
		r = a->ar_flags |= flags;
	else
		r = a->ar_flags &= ~flags;

	return (r & LIBELF_F_API_MASK);
}