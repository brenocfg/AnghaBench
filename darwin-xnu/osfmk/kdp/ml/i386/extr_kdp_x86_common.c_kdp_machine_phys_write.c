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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ mach_vm_size_t ;
typedef  scalar_t__ mach_vm_address_t ;
typedef  int /*<<< orphan*/  kdp_x86_xcpu_func_t ;
struct TYPE_4__ {scalar_t__ nbytes; scalar_t__ address; } ;
typedef  TYPE_1__ kdp_writephysmem64_req_t ;
typedef  scalar_t__ caddr_t ;
typedef  unsigned int addr64_t ;

/* Variables and functions */
 scalar_t__ EFAULT ; 
 scalar_t__ KDP_CURRENT_LCPU ; 
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ cpu_number () ; 
 unsigned int kdp_vtophys (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kdp_x86_xcpu_invoke (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ ml_copy_phys (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  printf (char*,void*,scalar_t__,scalar_t__,unsigned int,unsigned int) ; 

mach_vm_size_t
kdp_machine_phys_write(kdp_writephysmem64_req_t *rq, caddr_t src,
		       uint16_t lcpu)
{       
	mach_vm_address_t dst = rq->address;
	mach_vm_size_t    len = rq->nbytes;
	addr64_t cur_virt_src;
	addr64_t cur_phys_src, cur_phys_dst;
	unsigned resid, cnt, cnt_src, cnt_dst;

        if ((lcpu != KDP_CURRENT_LCPU) && (lcpu != cpu_number())) {
		return (mach_vm_size_t) 
			kdp_x86_xcpu_invoke(lcpu, (kdp_x86_xcpu_func_t)kdp_machine_phys_write, rq, src);
        }

#ifdef KDP_VM_WRITE_DEBUG
	printf("kdp_phys_write: src %p dst %llx len %llx - %08X %08X\n", (void *)src, dst, len, ((unsigned int *)src)[0], ((unsigned int *)src)[1]);
#endif

	cur_virt_src = (addr64_t)(intptr_t)src;
	cur_phys_dst = (addr64_t)dst;

	resid = (unsigned)len;

	while (resid != 0) {
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
		cur_phys_dst +=cnt;
		resid -= cnt;
	}

exit:
	return (len - resid);
}