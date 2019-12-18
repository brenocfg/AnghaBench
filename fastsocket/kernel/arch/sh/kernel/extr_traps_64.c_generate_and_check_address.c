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
struct pt_regs {scalar_t__* regs; } ;
typedef  scalar_t__ __u64 ;
typedef  int __u32 ;
typedef  int __s64 ;

/* Variables and functions */
 scalar_t__ TASK_SIZE ; 
 int /*<<< orphan*/  address_is_sign_extended (scalar_t__) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int generate_and_check_address(struct pt_regs *regs,
				      __u32 opcode,
				      int displacement_not_indexed,
				      int width_shift,
				      __u64 *address)
{
	/* return -1 for fault, 0 for OK */

	__u64 base_address, addr;
	int basereg;

	basereg = (opcode >> 20) & 0x3f;
	base_address = regs->regs[basereg];
	if (displacement_not_indexed) {
		__s64 displacement;
		displacement = (opcode >> 10) & 0x3ff;
		displacement = ((displacement << 54) >> 54); /* sign extend */
		addr = (__u64)((__s64)base_address + (displacement << width_shift));
	} else {
		__u64 offset;
		int offsetreg;
		offsetreg = (opcode >> 10) & 0x3f;
		offset = regs->regs[offsetreg];
		addr = base_address + offset;
	}

	/* Check sign extended */
	if (!address_is_sign_extended(addr)) {
		return -1;
	}

	/* Check accessible.  For misaligned access in the kernel, assume the
	   address is always accessible (and if not, just fault when the
	   load/store gets done.) */
	if (user_mode(regs)) {
		if (addr >= TASK_SIZE) {
			return -1;
		}
		/* Do access_ok check later - it depends on whether it's a load or a store. */
	}

	*address = addr;
	return 0;
}