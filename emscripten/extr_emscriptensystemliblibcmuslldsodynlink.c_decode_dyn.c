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
struct dso {void* versym; int /*<<< orphan*/  dynv; void* ghashtab; void* got; void* strings; void* rpath_orig; void* hashtab; void* syms; } ;

/* Variables and functions */
 int /*<<< orphan*/  DT_GNU_HASH ; 
 int DT_HASH ; 
 int DT_PLTGOT ; 
 int DT_RPATH ; 
 int DT_RUNPATH ; 
 size_t DT_STRTAB ; 
 size_t DT_SYMTAB ; 
 int /*<<< orphan*/  DT_VERSYM ; 
 int DYN_CNT ; 
 int /*<<< orphan*/  decode_vec (int /*<<< orphan*/ ,size_t*,int) ; 
 void* laddr (struct dso*,size_t) ; 
 scalar_t__ search_vec (int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void decode_dyn(struct dso *p)
{
	size_t dyn[DYN_CNT];
	decode_vec(p->dynv, dyn, DYN_CNT);
	p->syms = laddr(p, dyn[DT_SYMTAB]);
	p->strings = laddr(p, dyn[DT_STRTAB]);
	if (dyn[0]&(1<<DT_HASH))
		p->hashtab = laddr(p, dyn[DT_HASH]);
	if (dyn[0]&(1<<DT_RPATH))
		p->rpath_orig = p->strings + dyn[DT_RPATH];
	if (dyn[0]&(1<<DT_RUNPATH))
		p->rpath_orig = p->strings + dyn[DT_RUNPATH];
	if (dyn[0]&(1<<DT_PLTGOT))
		p->got = laddr(p, dyn[DT_PLTGOT]);
	if (search_vec(p->dynv, dyn, DT_GNU_HASH))
		p->ghashtab = laddr(p, *dyn);
	if (search_vec(p->dynv, dyn, DT_VERSYM))
		p->versym = laddr(p, *dyn);
}