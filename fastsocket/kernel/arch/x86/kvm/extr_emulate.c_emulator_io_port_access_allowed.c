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
typedef  unsigned int u8 ;
typedef  int u16 ;
struct x86_emulate_ops {int (* read_std ) (scalar_t__,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct x86_emulate_ctxt {int /*<<< orphan*/  vcpu; } ;
struct kvm_segment {int limit; scalar_t__ base; scalar_t__ unusable; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_SREG_TR ; 
 int X86EMUL_CONTINUE ; 
 int /*<<< orphan*/  kvm_get_segment (int /*<<< orphan*/ ,struct kvm_segment*,int /*<<< orphan*/ ) ; 
 int stub1 (scalar_t__,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (scalar_t__,unsigned int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool emulator_io_port_access_allowed(struct x86_emulate_ctxt *ctxt,
					    struct x86_emulate_ops *ops,
					    u16 port, u16 len)
{
	struct kvm_segment tr_seg;
	int r;
	u16 io_bitmap_ptr;
	u8 perm, bit_idx = port & 0x7;
	unsigned mask = (1 << len) - 1;

	kvm_get_segment(ctxt->vcpu, &tr_seg, VCPU_SREG_TR);
	if (tr_seg.unusable)
		return false;
	if (tr_seg.limit < 103)
		return false;
	r = ops->read_std(tr_seg.base + 102, &io_bitmap_ptr, 2, ctxt->vcpu,
			  NULL);
	if (r != X86EMUL_CONTINUE)
		return false;
	if (io_bitmap_ptr + port/8 > tr_seg.limit)
		return false;
	r = ops->read_std(tr_seg.base + io_bitmap_ptr + port/8, &perm, 1,
			  ctxt->vcpu, NULL);
	if (r != X86EMUL_CONTINUE)
		return false;
	if ((perm >> bit_idx) & mask)
		return false;
	return true;
}