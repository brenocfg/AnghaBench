#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
struct TYPE_5__ {int e_next; } ;
struct TYPE_6__ {TYPE_1__ e_ar; } ;
struct TYPE_7__ {scalar_t__ e_kind; scalar_t__ e_cmd; scalar_t__ e_rawfile; scalar_t__ e_rawsize; TYPE_2__ e_u; struct TYPE_7__* e_parent; } ;
typedef  scalar_t__ Elf_Cmd ;
typedef  TYPE_3__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 scalar_t__ ELF_C_NULL ; 
 scalar_t__ ELF_C_READ ; 
 scalar_t__ ELF_K_AR ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

Elf_Cmd
elf_next(Elf *e)
{
	off_t next;
	Elf *parent;

	if (e == NULL)
		return (ELF_C_NULL);

	 if ((parent = e->e_parent) == NULL) {
		 LIBELF_SET_ERROR(ARGUMENT, 0);
		 return (ELF_C_NULL);
	 }

	assert(parent->e_kind == ELF_K_AR);
	assert(parent->e_cmd == ELF_C_READ);
	assert(e->e_rawfile > parent->e_rawfile);

	next = e->e_rawfile - parent->e_rawfile + (off_t) e->e_rawsize;
	next = (next + 1) & ~1;	/* round up to an even boundary */

	/*
	 * Setup the 'e_next' field of the archive descriptor for the
	 * next call to 'elf_begin()'.
	 */
	parent->e_u.e_ar.e_next = (next >= (off_t) parent->e_rawsize) ?
	    (off_t) 0 : next;

	return (ELF_C_READ);
}