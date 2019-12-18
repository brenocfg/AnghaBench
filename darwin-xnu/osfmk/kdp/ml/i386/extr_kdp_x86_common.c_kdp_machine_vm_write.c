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
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  scalar_t__ caddr_t ;
typedef  unsigned int addr64_t ;

/* Variables and functions */
 scalar_t__ EFAULT ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SIZE ; 
 unsigned int PAL_KDP_ADDR (unsigned int) ; 
 unsigned int kdp_vtophys (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ ml_copy_phys (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,void*,scalar_t__,scalar_t__,unsigned int,unsigned int) ; 

mach_vm_size_t
kdp_machine_vm_write( caddr_t src, mach_vm_address_t dst, mach_vm_size_t len)
{       
	addr64_t cur_virt_src, cur_virt_dst;
	addr64_t cur_phys_src, cur_phys_dst;
	unsigned resid, cnt, cnt_src, cnt_dst;

#ifdef KDP_VM_WRITE_DEBUG
	printf("kdp_vm_write: src %p dst %llx len %llx - %08X %08X\n", (void *)src, dst, len, ((unsigned int *)src)[0], ((unsigned int *)src)[1]);
#endif

	cur_virt_src = PAL_KDP_ADDR((addr64_t)(intptr_t)src);
	cur_virt_dst = PAL_KDP_ADDR((addr64_t)dst);

	resid = (unsigned)len;

	while (resid != 0) {
		if ((cur_phys_dst = kdp_vtophys(kernel_pmap, cur_virt_dst)) == 0) 
			goto exit;

		if ((cur_phys_src = kdp_vtophys(kernel_pmap, cur_virt_src)) == 0) 
			goto exit;

		/* Copy as many bytes as possible without crossing a page */
		cnt_src = (unsigned)(PAGE_SIZE - (cur_phys_src & PAGE_MASK));
		cnt_dst = (unsigned)(PAGE_SIZE - (cur_phys_dst & PAGE_MASK));

		if (cnt_src > cnt_dst)
			cnt = cnt_dst;
		else
			cnt = cnt_src;
		if (cnt > resid) 
			cnt = resid;

		if (EFAULT == ml_copy_phys(cur_phys_src, cur_phys_dst, cnt))
			goto exit;		/* Copy stuff over */

		cur_virt_src +=cnt;
		cur_virt_dst +=cnt;
		resid -= cnt;
	}
exit:
	return (len - resid);
}