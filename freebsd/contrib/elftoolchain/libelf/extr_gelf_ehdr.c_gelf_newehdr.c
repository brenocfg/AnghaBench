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
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* _libelf_ehdr (int /*<<< orphan*/ *,int,int) ; 

void *
gelf_newehdr(Elf *e, int ec)
{
	if (e != NULL &&
	    (ec == ELFCLASS32 || ec == ELFCLASS64))
		return (_libelf_ehdr(e, ec, 1));

	LIBELF_SET_ERROR(ARGUMENT, 0);
	return (NULL);
}