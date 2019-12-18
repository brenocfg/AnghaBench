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
typedef  int /*<<< orphan*/  Elf_Type ;

/* Variables and functions */
 int /*<<< orphan*/  ELFCLASS32 ; 
 size_t _libelf_fsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,size_t) ; 

size_t
elf32_fsize(Elf_Type t, size_t c, unsigned int v)
{
	return (_libelf_fsize(t, ELFCLASS32, v, c));
}