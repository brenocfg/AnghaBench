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
struct dso {int relocated; size_t relro_start; size_t relro_end; int /*<<< orphan*/  name; int /*<<< orphan*/  dynv; struct dso* next; } ;

/* Variables and functions */
 size_t DT_JMPREL ; 
 size_t DT_PLTGOT ; 
 size_t DT_PLTREL ; 
 size_t DT_PLTRELSZ ; 
 size_t DT_REL ; 
 size_t DT_RELA ; 
 size_t DT_RELASZ ; 
 size_t DT_RELSZ ; 
 int DYN_CNT ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ NEED_MIPS_GOT_RELOCS ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  decode_vec (int /*<<< orphan*/ ,size_t*,int) ; 
 int /*<<< orphan*/  do_mips_relocs (struct dso*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_relocs (struct dso*,int /*<<< orphan*/ ,size_t,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * head ; 
 int /*<<< orphan*/  laddr (struct dso*,size_t) ; 
 int /*<<< orphan*/  ldso ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mprotect (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rtld_fail ; 
 scalar_t__ runtime ; 

__attribute__((used)) static void reloc_all(struct dso *p)
{
	size_t dyn[DYN_CNT];
	for (; p; p=p->next) {
		if (p->relocated) continue;
		decode_vec(p->dynv, dyn, DYN_CNT);
		if (NEED_MIPS_GOT_RELOCS)
			do_mips_relocs(p, laddr(p, dyn[DT_PLTGOT]));
		do_relocs(p, laddr(p, dyn[DT_JMPREL]), dyn[DT_PLTRELSZ],
			2+(dyn[DT_PLTREL]==DT_RELA));
		do_relocs(p, laddr(p, dyn[DT_REL]), dyn[DT_RELSZ], 2);
		do_relocs(p, laddr(p, dyn[DT_RELA]), dyn[DT_RELASZ], 3);

		if (head != &ldso && p->relro_start != p->relro_end &&
		    mprotect(laddr(p, p->relro_start), p->relro_end-p->relro_start, PROT_READ)
		    && errno != ENOSYS) {
			error("Error relocating %s: RELRO protection failed: %m",
				p->name);
			if (runtime) longjmp(*rtld_fail, 1);
		}

		p->relocated = 1;
	}
}