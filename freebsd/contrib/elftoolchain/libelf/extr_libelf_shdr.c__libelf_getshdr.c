#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ e_kind; int e_class; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_shdr; TYPE_2__* s_elf; } ;
typedef  TYPE_1__ Elf_Scn ;
typedef  TYPE_2__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int /*<<< orphan*/  CLASS ; 
 int ELFCLASSNONE ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
_libelf_getshdr(Elf_Scn *s, int ec)
{
	Elf *e;

	if (s == NULL || (e = s->s_elf) == NULL ||
	    e->e_kind != ELF_K_ELF) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (NULL);
	}

	if (ec == ELFCLASSNONE)
		ec = e->e_class;

	if (ec != e->e_class) {
		LIBELF_SET_ERROR(CLASS, 0);
		return (NULL);
	}

	return ((void *) &s->s_shdr);
}