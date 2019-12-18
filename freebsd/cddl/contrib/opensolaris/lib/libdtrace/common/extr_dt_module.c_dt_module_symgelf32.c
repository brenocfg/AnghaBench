#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_value; int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_other; int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_name; } ;
struct TYPE_6__ {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_value; int /*<<< orphan*/  st_shndx; int /*<<< orphan*/  st_other; int /*<<< orphan*/  st_info; int /*<<< orphan*/  st_name; } ;
typedef  TYPE_1__ GElf_Sym ;
typedef  TYPE_2__ Elf32_Sym ;

/* Variables and functions */

__attribute__((used)) static GElf_Sym *
dt_module_symgelf32(const Elf32_Sym *src, GElf_Sym *dst)
{
	if (dst != NULL) {
		dst->st_name = src->st_name;
		dst->st_info = src->st_info;
		dst->st_other = src->st_other;
		dst->st_shndx = src->st_shndx;
		dst->st_value = src->st_value;
		dst->st_size = src->st_size;
	}

	return (dst);
}