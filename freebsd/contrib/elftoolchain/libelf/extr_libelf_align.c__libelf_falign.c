#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int a32; unsigned int a64; } ;
typedef  size_t Elf_Type ;

/* Variables and functions */
 int ELFCLASS32 ; 
 size_t ELF_T_NUM ; 
 TYPE_1__* falign ; 

unsigned int
_libelf_falign(Elf_Type t, int elfclass)
{
	if (t >= ELF_T_NUM || (int) t < 0)
		return (0);

	return (elfclass == ELFCLASS32 ? falign[t].a32 :
	    falign[t].a64);
}