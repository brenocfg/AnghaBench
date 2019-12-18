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
struct fdt_header {int dummy; } ;

/* Variables and functions */
 int FDT_ALIGN (int,int) ; 
 int /*<<< orphan*/  FDT_CHECK_HEADER (void const*) ; 
 scalar_t__ FDT_END ; 
 int FDT_ERR_NOSPACE ; 
 int /*<<< orphan*/  FDT_MAGIC ; 
 int /*<<< orphan*/  _fdt_blocks_misordered (void const*,int,int) ; 
 int /*<<< orphan*/  _fdt_packblocks (void const*,char*,int,int) ; 
 int /*<<< orphan*/  fdt_boot_cpuid_phys (void const*) ; 
 int fdt_move (void const*,void*,int) ; 
 scalar_t__ fdt_next_tag (void const*,int,int*) ; 
 int fdt_num_mem_rsv (void const*) ; 
 int /*<<< orphan*/  fdt_set_boot_cpuid_phys (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_last_comp_version (void*,int) ; 
 int /*<<< orphan*/  fdt_set_magic (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdt_set_size_dt_struct (void*,int) ; 
 int /*<<< orphan*/  fdt_set_totalsize (void*,int) ; 
 int /*<<< orphan*/  fdt_set_version (void*,int) ; 
 int fdt_size_dt_strings (void const*) ; 
 int fdt_size_dt_struct (void const*) ; 
 int fdt_totalsize (void const*) ; 
 int fdt_version (void const*) ; 
 int /*<<< orphan*/  memmove (void*,char*,int) ; 

int fdt_open_into(const void *fdt, void *buf, int bufsize)
{
	int err;
	int mem_rsv_size, struct_size;
	int newsize;
	const char *fdtstart = fdt;
	const char *fdtend = fdtstart + fdt_totalsize(fdt);
	char *tmp;

	FDT_CHECK_HEADER(fdt);

	mem_rsv_size = (fdt_num_mem_rsv(fdt)+1)
		* sizeof(struct fdt_reserve_entry);

	if (fdt_version(fdt) >= 17) {
		struct_size = fdt_size_dt_struct(fdt);
	} else {
		struct_size = 0;
		while (fdt_next_tag(fdt, struct_size, &struct_size) != FDT_END)
			;
	}

	if (!_fdt_blocks_misordered(fdt, mem_rsv_size, struct_size)) {
		/* no further work necessary */
		err = fdt_move(fdt, buf, bufsize);
		if (err)
			return err;
		fdt_set_version(buf, 17);
		fdt_set_size_dt_struct(buf, struct_size);
		fdt_set_totalsize(buf, bufsize);
		return 0;
	}

	/* Need to reorder */
	newsize = FDT_ALIGN(sizeof(struct fdt_header), 8) + mem_rsv_size
		+ struct_size + fdt_size_dt_strings(fdt);

	if (bufsize < newsize)
		return -FDT_ERR_NOSPACE;

	/* First attempt to build converted tree at beginning of buffer */
	tmp = buf;
	/* But if that overlaps with the old tree... */
	if (((tmp + newsize) > fdtstart) && (tmp < fdtend)) {
		/* Try right after the old tree instead */
		tmp = (char *)(uintptr_t)fdtend;
		if ((tmp + newsize) > ((char *)buf + bufsize))
			return -FDT_ERR_NOSPACE;
	}

	_fdt_packblocks(fdt, tmp, mem_rsv_size, struct_size);
	memmove(buf, tmp, newsize);

	fdt_set_magic(buf, FDT_MAGIC);
	fdt_set_totalsize(buf, bufsize);
	fdt_set_version(buf, 17);
	fdt_set_last_comp_version(buf, 16);
	fdt_set_boot_cpuid_phys(buf, fdt_boot_cpuid_phys(fdt));

	return 0;
}