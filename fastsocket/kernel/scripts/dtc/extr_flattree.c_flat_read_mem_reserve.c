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
struct reserve_info {int dummy; } ;
struct inbuf {char* ptr; } ;
struct fdt_reserve_entry {scalar_t__ address; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  re ;

/* Variables and functions */
 struct reserve_info* add_reserve_entry (struct reserve_info*,struct reserve_info*) ; 
 struct reserve_info* build_reserve_entry (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 void* fdt64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  flat_read_chunk (struct inbuf*,struct fdt_reserve_entry*,int) ; 

__attribute__((used)) static struct reserve_info *flat_read_mem_reserve(struct inbuf *inb)
{
	struct reserve_info *reservelist = NULL;
	struct reserve_info *new;
	const char *p;
	struct fdt_reserve_entry re;

	/*
	 * Each entry is a pair of u64 (addr, size) values for 4 cell_t's.
	 * List terminates at an entry with size equal to zero.
	 *
	 * First pass, count entries.
	 */
	p = inb->ptr;
	while (1) {
		flat_read_chunk(inb, &re, sizeof(re));
		re.address  = fdt64_to_cpu(re.address);
		re.size = fdt64_to_cpu(re.size);
		if (re.size == 0)
			break;

		new = build_reserve_entry(re.address, re.size, NULL);
		reservelist = add_reserve_entry(reservelist, new);
	}

	return reservelist;
}