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
struct fdt_reserve_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_RW_CHECK_HEADER (void*) ; 
 int /*<<< orphan*/  _fdt_data_size (void*) ; 
 int /*<<< orphan*/  _fdt_packblocks (void*,void*,int,int /*<<< orphan*/ ) ; 
 int fdt_num_mem_rsv (void*) ; 
 int /*<<< orphan*/  fdt_set_totalsize (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_size_dt_struct (void*) ; 

int fdt_pack(void *fdt)
{
	int mem_rsv_size;

	FDT_RW_CHECK_HEADER(fdt);

	mem_rsv_size = (fdt_num_mem_rsv(fdt)+1)
		* sizeof(struct fdt_reserve_entry);
	_fdt_packblocks(fdt, fdt, mem_rsv_size, fdt_size_dt_struct(fdt));
	fdt_set_totalsize(fdt, _fdt_data_size(fdt));

	return 0;
}