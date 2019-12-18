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
typedef  int /*<<< orphan*/  Elf_Scn ;
typedef  int /*<<< orphan*/  Elf32_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  ELFCLASS32 ; 
 int /*<<< orphan*/ * _libelf_getshdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Elf32_Shdr *
elf32_getshdr(Elf_Scn *s)
{
	return (_libelf_getshdr(s, ELFCLASS32));
}