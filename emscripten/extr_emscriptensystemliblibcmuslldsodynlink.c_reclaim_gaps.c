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
struct dso {size_t phnum; int phentsize; TYPE_1__* phdr; } ;
struct TYPE_2__ {scalar_t__ p_type; int p_flags; int p_vaddr; int p_memsz; } ;
typedef  TYPE_1__ Phdr ;

/* Variables and functions */
 scalar_t__ DL_FDPIC ; 
 int PAGE_SIZE ; 
 int PF_R ; 
 int PF_W ; 
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  reclaim (struct dso*,int,int) ; 

__attribute__((used)) static void reclaim_gaps(struct dso *dso)
{
	Phdr *ph = dso->phdr;
	size_t phcnt = dso->phnum;

	if (DL_FDPIC) return; // FIXME
	for (; phcnt--; ph=(void *)((char *)ph+dso->phentsize)) {
		if (ph->p_type!=PT_LOAD) continue;
		if ((ph->p_flags&(PF_R|PF_W))!=(PF_R|PF_W)) continue;
		reclaim(dso, ph->p_vaddr & -PAGE_SIZE, ph->p_vaddr);
		reclaim(dso, ph->p_vaddr+ph->p_memsz,
			ph->p_vaddr+ph->p_memsz+PAGE_SIZE-1 & -PAGE_SIZE);
	}
}