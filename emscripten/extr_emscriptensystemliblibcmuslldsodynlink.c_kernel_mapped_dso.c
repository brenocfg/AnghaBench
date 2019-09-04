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
struct dso {size_t phnum; int phentsize; size_t relro_start; size_t relro_end; size_t map_len; int kernel_mapped; scalar_t__ base; scalar_t__ map; int /*<<< orphan*/  dynv; TYPE_1__* phdr; } ;
struct TYPE_2__ {scalar_t__ p_type; size_t p_vaddr; size_t p_memsz; } ;
typedef  TYPE_1__ Phdr ;

/* Variables and functions */
 size_t PAGE_SIZE ; 
 scalar_t__ PT_DYNAMIC ; 
 scalar_t__ PT_GNU_RELRO ; 
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  laddr (struct dso*,size_t) ; 

__attribute__((used)) static void kernel_mapped_dso(struct dso *p)
{
	size_t min_addr = -1, max_addr = 0, cnt;
	Phdr *ph = p->phdr;
	for (cnt = p->phnum; cnt--; ph = (void *)((char *)ph + p->phentsize)) {
		if (ph->p_type == PT_DYNAMIC) {
			p->dynv = laddr(p, ph->p_vaddr);
		} else if (ph->p_type == PT_GNU_RELRO) {
			p->relro_start = ph->p_vaddr & -PAGE_SIZE;
			p->relro_end = (ph->p_vaddr + ph->p_memsz) & -PAGE_SIZE;
		}
		if (ph->p_type != PT_LOAD) continue;
		if (ph->p_vaddr < min_addr)
			min_addr = ph->p_vaddr;
		if (ph->p_vaddr+ph->p_memsz > max_addr)
			max_addr = ph->p_vaddr+ph->p_memsz;
	}
	min_addr &= -PAGE_SIZE;
	max_addr = (max_addr + PAGE_SIZE-1) & -PAGE_SIZE;
	p->map = p->base + min_addr;
	p->map_len = max_addr - min_addr;
	p->kernel_mapped = 1;
}