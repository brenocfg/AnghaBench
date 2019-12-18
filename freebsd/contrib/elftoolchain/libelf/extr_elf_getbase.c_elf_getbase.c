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
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_5__ {TYPE_1__* e_parent; scalar_t__ e_rawfile; } ;
struct TYPE_4__ {scalar_t__ e_rawfile; } ;
typedef  TYPE_2__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

off_t
elf_getbase(Elf *e)
{
	if (e == NULL) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return ((off_t) -1);
	}

	if (e->e_parent == NULL)
		return ((off_t) 0);

	return ((off_t) ((uintptr_t) e->e_rawfile -
	    (uintptr_t) e->e_parent->e_rawfile));
}