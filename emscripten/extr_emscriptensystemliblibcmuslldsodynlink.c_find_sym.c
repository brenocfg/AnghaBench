#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct symdef {struct dso* dso; TYPE_1__* sym; int /*<<< orphan*/  member_0; } ;
struct dso {int* ghashtab; int /*<<< orphan*/  global; struct dso* next; } ;
struct TYPE_5__ {int st_info; int /*<<< orphan*/  st_value; int /*<<< orphan*/  st_shndx; } ;
typedef  TYPE_1__ Sym ;

/* Variables and functions */
 scalar_t__ ARCH_SYM_REJECT_UND (TYPE_1__*) ; 
 int OK_BINDS ; 
 int OK_TYPES ; 
 int STB_GLOBAL ; 
 int STB_WEAK ; 
 int STT_TLS ; 
 int gnu_hash (char const*) ; 
 TYPE_1__* gnu_lookup_filtered (int,int*,struct dso*,char const*,int,size_t) ; 
 int sysv_hash (char const*) ; 
 TYPE_1__* sysv_lookup (char const*,int,struct dso*) ; 

__attribute__((used)) static struct symdef find_sym(struct dso *dso, const char *s, int need_def)
{
	uint32_t h = 0, gh, gho, *ght;
	size_t ghm = 0;
	struct symdef def = {0};
	for (; dso; dso=dso->next) {
		Sym *sym;
		if (!dso->global) continue;
		if ((ght = dso->ghashtab)) {
			if (!ghm) {
				gh = gnu_hash(s);
				int maskbits = 8 * sizeof ghm;
				gho = gh / maskbits;
				ghm = 1ul << gh % maskbits;
			}
			sym = gnu_lookup_filtered(gh, ght, dso, s, gho, ghm);
		} else {
			if (!h) h = sysv_hash(s);
			sym = sysv_lookup(s, h, dso);
		}
		if (!sym) continue;
		if (!sym->st_shndx)
			if (need_def || (sym->st_info&0xf) == STT_TLS
			    || ARCH_SYM_REJECT_UND(sym))
				continue;
		if (!sym->st_value)
			if ((sym->st_info&0xf) != STT_TLS)
				continue;
		if (!(1<<(sym->st_info&0xf) & OK_TYPES)) continue;
		if (!(1<<(sym->st_info>>4) & OK_BINDS)) continue;

		if (def.sym && sym->st_info>>4 == STB_WEAK) continue;
		def.sym = sym;
		def.dso = dso;
		if (sym->st_info>>4 == STB_GLOBAL) break;
	}
	return def;
}