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
typedef  int mach_vm_size_t ;
typedef  int mach_vm_address_t ;
typedef  int caddr_t ;
typedef  int addr64_t ;

/* Variables and functions */
 int ARM_PGBYTES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bcopy_phys (int,int,int) ; 
 int /*<<< orphan*/  flush_dcache64 (int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_icache64 (int,unsigned int,int /*<<< orphan*/ ) ; 
 int kdp_vtophys (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_valid_address (int) ; 
 int /*<<< orphan*/  printf (char*,int,int,int,...) ; 

mach_vm_size_t
kdp_machine_vm_write( caddr_t src, mach_vm_address_t dst, mach_vm_size_t len)
{
	addr64_t        cur_virt_src, cur_virt_dst;
	addr64_t        cur_phys_src, cur_phys_dst;
	mach_vm_size_t  resid, cnt, cnt_src, cnt_dst;

#ifdef KDP_VM_WRITE_DEBUG
	printf("kdp_vm_write: src %x dst %x len %x - %08X %08X\n", src, dst, len, ((unsigned long *) src)[0], ((unsigned long *) src)[1]);
#endif

	cur_virt_src = (addr64_t) src;
	cur_virt_dst = (addr64_t) dst;

	resid = len;

	while (resid != 0) {
		if ((cur_phys_dst = kdp_vtophys(kernel_pmap, cur_virt_dst)) == 0)
			goto exit;

		if ((cur_phys_src = kdp_vtophys(kernel_pmap, cur_virt_src)) == 0)
			goto exit;

		/* Attempt to ensure that there are valid translations for src and dst. */
		/* No support for enabling writes for an invalid translation at the moment. */
		if ((!pmap_valid_address(cur_phys_dst)) || (!pmap_valid_address(cur_phys_src)))
			goto exit;

		cnt_src = ((cur_phys_src + ARM_PGBYTES) & (-ARM_PGBYTES)) - cur_phys_src;
		cnt_dst = ((cur_phys_dst + ARM_PGBYTES) & (-ARM_PGBYTES)) - cur_phys_dst;

		if (cnt_src > cnt_dst)
			cnt = cnt_dst;
		else
			cnt = cnt_src;
		if (cnt > resid)
			cnt = resid;

#ifdef KDP_VM_WRITE_DEBUG
		printf("kdp_vm_write: cur_phys_src %x cur_phys_src %x len %x - %08X %08X\n", src, dst, cnt);
#endif
		bcopy_phys(cur_phys_src, cur_phys_dst, cnt);	/* Copy stuff over */
		flush_dcache64(cur_phys_dst, (unsigned int)cnt, TRUE);
		invalidate_icache64(cur_phys_dst, (unsigned int)cnt, TRUE);

		cur_virt_src += cnt;
		cur_virt_dst += cnt;
		resid -= cnt;
	}
exit:
	return (len - resid);
}