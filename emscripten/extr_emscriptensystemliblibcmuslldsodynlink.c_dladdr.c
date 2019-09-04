#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct dso {char* strings; int /*<<< orphan*/  base; int /*<<< orphan*/  name; TYPE_1__* syms; void* funcdescs; } ;
struct TYPE_5__ {char* dli_sname; void* dli_saddr; int /*<<< orphan*/  dli_fbase; int /*<<< orphan*/  dli_fname; } ;
struct TYPE_4__ {int st_info; int st_name; scalar_t__ st_value; } ;
typedef  TYPE_1__ Sym ;
typedef  TYPE_2__ Dl_info ;

/* Variables and functions */
 scalar_t__ DL_FDPIC ; 
 int OK_BINDS ; 
 int OK_TYPES ; 
 int STT_FUNC ; 
 struct dso* addr2dso (size_t) ; 
 size_t count_syms (struct dso*) ; 
 void* laddr (struct dso*,scalar_t__) ; 
 int /*<<< orphan*/  lock ; 
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 

int dladdr(const void *addr, Dl_info *info)
{
	struct dso *p;
	Sym *sym, *bestsym;
	uint32_t nsym;
	char *strings;
	void *best = 0;

	pthread_rwlock_rdlock(&lock);
	p = addr2dso((size_t)addr);
	pthread_rwlock_unlock(&lock);

	if (!p) return 0;

	sym = p->syms;
	strings = p->strings;
	nsym = count_syms(p);

	if (DL_FDPIC) {
		size_t idx = ((size_t)addr-(size_t)p->funcdescs)
			/ sizeof(*p->funcdescs);
		if (idx < nsym && (sym[idx].st_info&0xf) == STT_FUNC) {
			best = p->funcdescs + idx;
			bestsym = sym + idx;
		}
	}

	if (!best) for (; nsym; nsym--, sym++) {
		if (sym->st_value
		 && (1<<(sym->st_info&0xf) & OK_TYPES)
		 && (1<<(sym->st_info>>4) & OK_BINDS)) {
			void *symaddr = laddr(p, sym->st_value);
			if (symaddr > addr || symaddr < best)
				continue;
			best = symaddr;
			bestsym = sym;
			if (addr == symaddr)
				break;
		}
	}

	if (!best) return 0;

	if (DL_FDPIC && (bestsym->st_info&0xf) == STT_FUNC)
		best = p->funcdescs + (bestsym - p->syms);

	info->dli_fname = p->name;
	info->dli_fbase = p->base;
	info->dli_sname = strings + bestsym->st_name;
	info->dli_saddr = best;

	return 1;
}