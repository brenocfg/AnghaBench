#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  kdp_x86_xcpu_func_t ;
struct TYPE_4__ {scalar_t__ nbytes; scalar_t__ address; } ;
typedef  TYPE_1__ kdp_readphysmem64_req_t ;
typedef  scalar_t__ caddr_t ;
typedef  scalar_t__ addr64_t ;

/* Variables and functions */
 scalar_t__ EFAULT ; 
 scalar_t__ KDP_CURRENT_LCPU ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ cpu_number () ; 
 scalar_t__ kdp_vtophys (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kdp_x86_xcpu_invoke (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ ml_copy_phys (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,void*,scalar_t__) ; 

mach_vm_size_t
kdp_machine_phys_read(kdp_readphysmem64_req_t *rq, caddr_t dst,
		      uint16_t lcpu)
{
	mach_vm_address_t src = rq->address;
	mach_vm_size_t    len = rq->nbytes;
	
	addr64_t cur_virt_dst;
	addr64_t cur_phys_dst, cur_phys_src;
	mach_vm_size_t resid = len;
	mach_vm_size_t cnt = 0, cnt_src, cnt_dst;

        if ((lcpu != KDP_CURRENT_LCPU) && (lcpu != cpu_number())) {
		return (mach_vm_size_t) 
			kdp_x86_xcpu_invoke(lcpu, (kdp_x86_xcpu_func_t)kdp_machine_phys_read, rq, dst);
        }

#ifdef KDP_VM_READ_DEBUG
	printf("kdp_phys_read: src %llx dst %p len %llx\n", src, (void *)dst, len);
#endif

	cur_virt_dst = (addr64_t)(intptr_t)dst;
	cur_phys_src = (addr64_t)src;

	while (resid != 0) {

		if(!(cur_phys_dst = kdp_vtophys(kernel_pmap, cur_virt_dst)))
			goto exit;

/* Get length left on page */
		cnt_src = PAGE_SIZE - (cur_phys_src & PAGE_MASK);
		cnt_dst = PAGE_SIZE - (cur_phys_dst & PAGE_MASK);
		if (cnt_src > cnt_dst)
			cnt = cnt_dst;
		else
			cnt = cnt_src;
		if (cnt > resid) 
			cnt = resid;

	/* Do a physical copy; use ml_copy_phys() in the event this is
	 * a short read with potential side effects.
	 */
		if (EFAULT == ml_copy_phys(cur_phys_src,
					   cur_phys_dst,
					   (vm_size_t)cnt))
			goto exit;
		cur_phys_src += cnt;
		cur_virt_dst += cnt;
		resid -= cnt;
	}
exit:
	return (len - resid);
}