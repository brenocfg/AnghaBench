#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  e_shstrndx; int /*<<< orphan*/  e_shnum; int /*<<< orphan*/  e_shentsize; int /*<<< orphan*/  e_phnum; int /*<<< orphan*/  e_phentsize; int /*<<< orphan*/  e_ehsize; int /*<<< orphan*/  e_flags; scalar_t__ e_shoff; scalar_t__ e_phoff; scalar_t__ e_entry; int /*<<< orphan*/  e_version; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_ident; } ;
struct TYPE_5__ {int /*<<< orphan*/  e_shstrndx; int /*<<< orphan*/  e_shnum; int /*<<< orphan*/  e_shentsize; int /*<<< orphan*/  e_phnum; int /*<<< orphan*/  e_phentsize; int /*<<< orphan*/  e_ehsize; int /*<<< orphan*/  e_flags; void* e_shoff; void* e_phoff; scalar_t__ e_entry; int /*<<< orphan*/  e_version; int /*<<< orphan*/  e_machine; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_ident; } ;
typedef  TYPE_1__ GElf_Ehdr ;
typedef  void* Elf64_Off ;
typedef  scalar_t__ Elf64_Addr ;
typedef  TYPE_2__ Elf32_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  EI_NIDENT ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ehdr_to_gelf(const Elf32_Ehdr *src, GElf_Ehdr *dst)
{
	bcopy(src->e_ident, dst->e_ident, EI_NIDENT);
	dst->e_type = src->e_type;
	dst->e_machine = src->e_machine;
	dst->e_version = src->e_version;
	dst->e_entry = (Elf64_Addr)src->e_entry;
	dst->e_phoff = (Elf64_Off)src->e_phoff;
	dst->e_shoff = (Elf64_Off)src->e_shoff;
	dst->e_flags = src->e_flags;
	dst->e_ehsize = src->e_ehsize;
	dst->e_phentsize = src->e_phentsize;
	dst->e_phnum = src->e_phnum;
	dst->e_shentsize = src->e_shentsize;
	dst->e_shnum = src->e_shnum;
	dst->e_shstrndx = src->e_shstrndx;
}