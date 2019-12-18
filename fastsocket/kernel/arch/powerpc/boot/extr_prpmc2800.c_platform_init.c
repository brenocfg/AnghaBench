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
struct elf_info {scalar_t__ elfoffset; scalar_t__ memsize; } ;
typedef  int /*<<< orphan*/  elfheader ;
struct TYPE_2__ {int /*<<< orphan*/  exit; int /*<<< orphan*/  fixups; } ;

/* Variables and functions */
 int /*<<< orphan*/  HEAP_SIZE ; 
 int KB ; 
 int MB ; 
 int _dtb_end ; 
 int _dtb_start ; 
 scalar_t__ _end ; 
 void* _vmlinux_end ; 
 void* _vmlinux_start ; 
 int /*<<< orphan*/  bridge_base ; 
 int /*<<< orphan*/  exit () ; 
 int /*<<< orphan*/  fdt_init (char*) ; 
 int /*<<< orphan*/  gunzip_exactly (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gunzip_start (int /*<<< orphan*/ *,void*,unsigned long) ; 
 int /*<<< orphan*/  gzstate ; 
 char* malloc (int) ; 
 char* max (char*,char*) ; 
 int /*<<< orphan*/  memmove (char*,int,int) ; 
 int /*<<< orphan*/  mv64x60_get_bridge_base () ; 
 int /*<<< orphan*/  parse_elf32 (char*,struct elf_info*) ; 
 TYPE_1__ platform_ops ; 
 int /*<<< orphan*/  prpmc2800_fixups ; 
 int /*<<< orphan*/  prpmc2800_reset ; 
 scalar_t__ serial_console_init () ; 
 scalar_t__ simple_alloc_init (char*,int /*<<< orphan*/ ,int,int) ; 

void platform_init(unsigned long r3, unsigned long r4, unsigned long r5,
                   unsigned long r6, unsigned long r7)
{
	struct elf_info ei;
	char *heap_start, *dtb;
	int dt_size = _dtb_end - _dtb_start;
	void *vmlinuz_addr = _vmlinux_start;
	unsigned long vmlinuz_size = _vmlinux_end - _vmlinux_start;
	char elfheader[256];

	if (dt_size <= 0) /* No fdt */
		exit();

	/*
	 * Start heap after end of the kernel (after decompressed to
	 * address 0) or the end of the zImage, whichever is higher.
	 * That's so things allocated by simple_alloc won't overwrite
	 * any part of the zImage and the kernel won't overwrite the dtb
	 * when decompressed & relocated.
	 */
	gunzip_start(&gzstate, vmlinuz_addr, vmlinuz_size);
	gunzip_exactly(&gzstate, elfheader, sizeof(elfheader));

	if (!parse_elf32(elfheader, &ei))
		exit();

	heap_start = (char *)(ei.memsize + ei.elfoffset); /* end of kernel*/
	heap_start = max(heap_start, (char *)_end); /* end of zImage */

	if ((unsigned)simple_alloc_init(heap_start, HEAP_SIZE, 2*KB, 16)
			> (128*MB))
		exit();

	/* Relocate dtb to safe area past end of zImage & kernel */
	dtb = malloc(dt_size);
	if (!dtb)
		exit();
	memmove(dtb, _dtb_start, dt_size);
	fdt_init(dtb);

	bridge_base = mv64x60_get_bridge_base();

	platform_ops.fixups = prpmc2800_fixups;
	platform_ops.exit = prpmc2800_reset;

	if (serial_console_init() < 0)
		exit();
}