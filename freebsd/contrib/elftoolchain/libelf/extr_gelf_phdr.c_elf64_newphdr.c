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
typedef  int /*<<< orphan*/  Elf64_Phdr ;
typedef  int /*<<< orphan*/  Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ELFCLASS64 ; 
 int /*<<< orphan*/ * _libelf_newphdr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

Elf64_Phdr *
elf64_newphdr(Elf *e, size_t count)
{
	return (_libelf_newphdr(e, ELFCLASS64, count));
}