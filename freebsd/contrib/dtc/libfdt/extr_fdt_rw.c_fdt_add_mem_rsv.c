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
typedef  int /*<<< orphan*/  uint64_t ;
struct fdt_reserve_entry {void* size; void* address; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_RW_CHECK_HEADER (void*) ; 
 struct fdt_reserve_entry* _fdt_mem_rsv_w (void*,int /*<<< orphan*/ ) ; 
 int _fdt_splice_mem_rsv (void*,struct fdt_reserve_entry*,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_fdt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_num_mem_rsv (void*) ; 

int fdt_add_mem_rsv(void *fdt, uint64_t address, uint64_t size)
{
	struct fdt_reserve_entry *re;
	int err;

	FDT_RW_CHECK_HEADER(fdt);

	re = _fdt_mem_rsv_w(fdt, fdt_num_mem_rsv(fdt));
	err = _fdt_splice_mem_rsv(fdt, re, 0, 1);
	if (err)
		return err;

	re->address = cpu_to_fdt64(address);
	re->size = cpu_to_fdt64(size);
	return 0;
}