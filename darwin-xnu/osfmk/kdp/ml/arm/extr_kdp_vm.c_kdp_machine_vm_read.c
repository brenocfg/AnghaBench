#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ pmap_t ;
typedef  int mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
struct TYPE_3__ {scalar_t__ nbytes; scalar_t__ address; } ;
typedef  TYPE_1__ kdp_readphysmem64_req_t ;
typedef  scalar_t__ caddr_t ;
typedef  int addr64_t ;

/* Variables and functions */
 int ARM_PGBYTES ; 
 int PAGE_MASK ; 
 int /*<<< orphan*/  bcopy_phys (int,int,int) ; 
 int kdp_machine_phys_read (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ kdp_pmap ; 
 int /*<<< orphan*/  kdp_read_io ; 
 scalar_t__ kdp_trans_off ; 
 int kdp_vtophys (scalar_t__,int) ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  kprintf (char*,int,...) ; 
 int /*<<< orphan*/  pmap_valid_address (int) ; 

mach_vm_size_t
kdp_machine_vm_read( mach_vm_address_t src, caddr_t dst, mach_vm_size_t len)
{
	addr64_t        cur_virt_src, cur_virt_dst;
	addr64_t        cur_phys_src, cur_phys_dst;
	mach_vm_size_t	resid, cnt;
	pmap_t          pmap;

#ifdef KDP_VM_READ_DEBUG
	kprintf("kdp_machine_vm_read1: src %x dst %x len %x - %08X %08X\n", src, dst, len, ((unsigned long *) src)[0], ((unsigned long *) src)[1]);
#endif

	cur_virt_src = (addr64_t) src;
	cur_virt_dst = (addr64_t) dst;

	if (kdp_trans_off) {
		kdp_readphysmem64_req_t rq;
		mach_vm_size_t ret;

		rq.address = src;
		rq.nbytes = (uint32_t)len;
		ret = kdp_machine_phys_read(&rq, dst, 0 /* unused */);
		return ret;
	} else {

		resid = len;

		if (kdp_pmap)
			pmap = kdp_pmap;	/* If special pmap, use it */
		else
			pmap = kernel_pmap;	/* otherwise, use kernel's */

		while (resid != 0) {
			/*
			 * Always translate the destination using the
			 * kernel_pmap.
			 */
			if ((cur_phys_dst = kdp_vtophys(kernel_pmap, cur_virt_dst)) == 0)
				goto exit;

			if ((cur_phys_src = kdp_vtophys(pmap, cur_virt_src)) == 0)
				goto exit;

			/* Attempt to ensure that there are valid translations for src and dst. */
			if  (!kdp_read_io && ((!pmap_valid_address(cur_phys_dst)) || (!pmap_valid_address(cur_phys_src))))
				goto exit;

			cnt = ARM_PGBYTES - (cur_virt_src & PAGE_MASK);	/* Get length left on
									 * page */
			if (cnt > (ARM_PGBYTES - (cur_virt_dst & PAGE_MASK)))
				cnt = ARM_PGBYTES - (cur_virt_dst & PAGE_MASK);

			if (cnt > resid)
				cnt = resid;

#ifdef KDP_VM_READ_DEBUG
			kprintf("kdp_machine_vm_read2: pmap %08X, virt %016LLX, phys %016LLX\n",
				pmap, cur_virt_src, cur_phys_src);
#endif
			bcopy_phys(cur_phys_src, cur_phys_dst, cnt);

			cur_virt_src += cnt;
			cur_virt_dst += cnt;
			resid -= cnt;
		}
	}
exit:
#ifdef KDP_VM_READ_DEBUG
	kprintf("kdp_machine_vm_read: ret %08X\n", len - resid);
#endif
	return (len - resid);
}