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
 int FDT_ERR_NOTFOUND ; 
 int /*<<< orphan*/  FDT_RW_CHECK_HEADER (void*) ; 
 struct fdt_reserve_entry* _fdt_mem_rsv_w (void*,int) ; 
 int _fdt_splice_mem_rsv (void*,struct fdt_reserve_entry*,int,int /*<<< orphan*/ ) ; 
 int fdt_num_mem_rsv (void*) ; 

int fdt_del_mem_rsv(void *fdt, int n)
{
	struct fdt_reserve_entry *re = _fdt_mem_rsv_w(fdt, n);
	int err;

	FDT_RW_CHECK_HEADER(fdt);

	if (n >= fdt_num_mem_rsv(fdt))
		return -FDT_ERR_NOTFOUND;

	err = _fdt_splice_mem_rsv(fdt, re, 1, 0);
	if (err)
		return err;
	return 0;
}