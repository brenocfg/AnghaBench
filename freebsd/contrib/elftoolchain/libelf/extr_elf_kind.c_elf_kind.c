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
struct TYPE_3__ {scalar_t__ e_kind; } ;
typedef  scalar_t__ Elf_Kind ;
typedef  TYPE_1__ Elf ;

/* Variables and functions */
 scalar_t__ ELF_K_AR ; 
 scalar_t__ ELF_K_ELF ; 
 scalar_t__ ELF_K_NONE ; 

Elf_Kind
elf_kind(Elf *e)
{
	if (e == NULL)
		return (ELF_K_NONE);
	if (e->e_kind == ELF_K_AR ||
	    e->e_kind == ELF_K_ELF)
		return (e->e_kind);
	return (ELF_K_NONE);
}