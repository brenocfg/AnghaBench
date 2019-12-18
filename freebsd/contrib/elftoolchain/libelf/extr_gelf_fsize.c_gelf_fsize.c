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
struct TYPE_3__ {scalar_t__ e_class; } ;
typedef  int /*<<< orphan*/  Elf_Type ;
typedef  TYPE_1__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 scalar_t__ ELFCLASS32 ; 
 scalar_t__ ELFCLASS64 ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t _libelf_fsize (int /*<<< orphan*/ ,scalar_t__,unsigned int,size_t) ; 

size_t
gelf_fsize(Elf *e, Elf_Type t, size_t c, unsigned int v)
{

	if (e == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	if (e->e_class == ELFCLASS32 || e->e_class == ELFCLASS64)
		return (_libelf_fsize(t, e->e_class, v, c));

	LIBELF_SET_ERROR(ARGUMENT, 0);
	return (0);
}