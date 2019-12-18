#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_fault {unsigned long pgoff; scalar_t__ virtual_address; } ;
struct vm_area_struct {TYPE_2__* vm_file; } ;
struct b3dfg_dev {unsigned int frame_size; TYPE_1__* buffers; } ;
struct TYPE_4__ {struct b3dfg_dev* private_data; } ;
struct TYPE_3__ {unsigned char** frame; } ;

/* Variables and functions */
 unsigned int B3DFG_FRAMES_PER_BUFFER ; 
 unsigned long PAGE_SHIFT ; 
 int VM_FAULT_NOPAGE ; 
 int VM_FAULT_SIGBUS ; 
 unsigned int b3dfg_nbuf ; 
 scalar_t__ unlikely (int) ; 
 unsigned long virt_to_phys (unsigned char*) ; 
 int /*<<< orphan*/  vm_insert_pfn (struct vm_area_struct*,unsigned long,unsigned long) ; 

__attribute__((used)) static int b3dfg_vma_fault(struct vm_area_struct *vma,
	struct vm_fault *vmf)
{
	struct b3dfg_dev *fgdev = vma->vm_file->private_data;
	unsigned long off = vmf->pgoff << PAGE_SHIFT;
	unsigned int frame_size = fgdev->frame_size;
	unsigned int buf_size = frame_size * B3DFG_FRAMES_PER_BUFFER;
	unsigned char *addr;

	/* determine which buffer the offset lies within */
	unsigned int buf_idx = off / buf_size;
	/* and the offset into the buffer */
	unsigned int buf_off = off % buf_size;

	/* determine which frame inside the buffer the offset lies in */
	unsigned int frm_idx = buf_off / frame_size;
	/* and the offset into the frame */
	unsigned int frm_off = buf_off % frame_size;

	if (unlikely(buf_idx >= b3dfg_nbuf))
		return VM_FAULT_SIGBUS;

	addr = fgdev->buffers[buf_idx].frame[frm_idx] + frm_off;
	vm_insert_pfn(vma, (unsigned long)vmf->virtual_address,
			  virt_to_phys(addr) >> PAGE_SHIFT);

	return VM_FAULT_NOPAGE;
}