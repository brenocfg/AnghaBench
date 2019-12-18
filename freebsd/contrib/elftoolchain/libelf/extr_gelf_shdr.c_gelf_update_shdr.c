#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ e_kind; int e_class; scalar_t__ e_cmd; } ;
struct TYPE_14__ {int /*<<< orphan*/  sh_info; int /*<<< orphan*/  sh_link; int /*<<< orphan*/  sh_type; int /*<<< orphan*/  sh_name; } ;
struct TYPE_12__ {int /*<<< orphan*/  sh_info; int /*<<< orphan*/  sh_link; int /*<<< orphan*/  sh_type; int /*<<< orphan*/  sh_name; } ;
struct TYPE_11__ {TYPE_4__ s_shdr32; TYPE_2__ s_shdr64; } ;
struct TYPE_13__ {TYPE_1__ s_shdr; TYPE_5__* s_elf; } ;
typedef  TYPE_2__ GElf_Shdr ;
typedef  TYPE_3__ Elf_Scn ;
typedef  TYPE_4__ Elf32_Shdr ;
typedef  TYPE_5__ Elf ;

/* Variables and functions */
 int /*<<< orphan*/  ARGUMENT ; 
 int ELFCLASS32 ; 
 int ELFCLASS64 ; 
 scalar_t__ ELF_C_READ ; 
 int /*<<< orphan*/  ELF_C_SET ; 
 int /*<<< orphan*/  ELF_F_DIRTY ; 
 scalar_t__ ELF_K_ELF ; 
 int /*<<< orphan*/  LIBELF_COPY_U32 (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MODE ; 
 int /*<<< orphan*/  elf_flagscn (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_addr ; 
 int /*<<< orphan*/  sh_addralign ; 
 int /*<<< orphan*/  sh_entsize ; 
 int /*<<< orphan*/  sh_flags ; 
 int /*<<< orphan*/  sh_offset ; 
 int /*<<< orphan*/  sh_size ; 

int
gelf_update_shdr(Elf_Scn *scn, GElf_Shdr *s)
{
	int ec;
	Elf *e;
	Elf32_Shdr *sh32;


	if (s == NULL || scn == NULL || (e = scn->s_elf) == NULL ||
	    e->e_kind != ELF_K_ELF ||
	    ((ec = e->e_class) != ELFCLASS32 && ec != ELFCLASS64)) {
		LIBELF_SET_ERROR(ARGUMENT, 0);
		return (0);
	}

	if (e->e_cmd == ELF_C_READ) {
		LIBELF_SET_ERROR(MODE, 0);
		return (0);
	}

	(void) elf_flagscn(scn, ELF_C_SET, ELF_F_DIRTY);

	if (ec == ELFCLASS64) {
		scn->s_shdr.s_shdr64 = *s;
		return (1);
	}

	sh32 = &scn->s_shdr.s_shdr32;

	sh32->sh_name	 =  s->sh_name;
	sh32->sh_type	 =  s->sh_type;
	LIBELF_COPY_U32(sh32, s, sh_flags);
	LIBELF_COPY_U32(sh32, s, sh_addr);
	LIBELF_COPY_U32(sh32, s, sh_offset);
	LIBELF_COPY_U32(sh32, s, sh_size);
	sh32->sh_link	 =  s->sh_link;
	sh32->sh_info	 =  s->sh_info;
	LIBELF_COPY_U32(sh32, s, sh_addralign);
	LIBELF_COPY_U32(sh32, s, sh_entsize);

	return (1);
}