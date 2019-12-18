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
 int /*<<< orphan*/  ELF_C_READ ; 
 scalar_t__ EV_NONE ; 
 scalar_t__ LIBELF_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEQUENCE ; 
 int /*<<< orphan*/ * _libelf_open_object (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  version ; 

Elf *
elf_open(int fd)
{
	if (LIBELF_PRIVATE(version) == EV_NONE) {
		LIBELF_SET_ERROR(SEQUENCE, 0);
		return (NULL);
	}

	return (_libelf_open_object(fd, ELF_C_READ, 0));
}