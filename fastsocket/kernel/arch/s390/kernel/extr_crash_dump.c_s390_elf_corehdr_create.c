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
typedef  unsigned long u64 ;
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  Elf64_Phdr ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* PTR_ADD (void*,int) ; 
 unsigned long PTR_DIFF (void*,void*) ; 
 void* ehdr_init (void*,int) ; 
 int get_cpu_cnt () ; 
 int get_mem_chunk_cnt () ; 
 void* kzalloc_panic (size_t) ; 
 int /*<<< orphan*/  loads_init (int /*<<< orphan*/ *,unsigned long) ; 
 void* notes_init (int /*<<< orphan*/ *,void*,unsigned long) ; 
 scalar_t__ relocate (unsigned long) ; 

__attribute__((used)) static void s390_elf_corehdr_create(char **elfcorebuf, size_t *elfcorebuf_sz)
{
	Elf64_Phdr *phdr_notes, *phdr_loads;
	int mem_chunk_cnt;
	void *ptr, *hdr;
	u32 alloc_size;
	u64 hdr_off;

	mem_chunk_cnt = get_mem_chunk_cnt();

	alloc_size = 0x1000 + get_cpu_cnt() * 0x300 +
		mem_chunk_cnt * sizeof(Elf64_Phdr);
	hdr = kzalloc_panic(alloc_size);
	/* Init elf header */
	ptr = ehdr_init(hdr, mem_chunk_cnt);
	/* Init program headers */
	phdr_notes = ptr;
	ptr = PTR_ADD(ptr, sizeof(Elf64_Phdr));
	phdr_loads = ptr;
	ptr = PTR_ADD(ptr, sizeof(Elf64_Phdr) * mem_chunk_cnt);
	/* Init notes */
	hdr_off = PTR_DIFF(ptr, hdr);
	ptr = notes_init(phdr_notes, ptr, ((unsigned long) hdr) + hdr_off);
	/* Init loads */
	hdr_off = PTR_DIFF(ptr, hdr);
	loads_init(phdr_loads, ((unsigned long) hdr) + hdr_off);
	*elfcorebuf_sz = hdr_off;
	*elfcorebuf = (void *) relocate((unsigned long) hdr);
	BUG_ON(*elfcorebuf_sz > alloc_size);
}