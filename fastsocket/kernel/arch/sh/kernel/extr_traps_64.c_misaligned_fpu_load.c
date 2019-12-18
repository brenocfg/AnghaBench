#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {scalar_t__ pc; int /*<<< orphan*/  sr; } ;
typedef  scalar_t__ __u64 ;
typedef  int __u32 ;
struct TYPE_7__ {int* fp_regs; } ;
struct TYPE_8__ {TYPE_1__ hard; } ;
struct TYPE_9__ {TYPE_2__ fpu; } ;
struct TYPE_10__ {TYPE_3__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SR_FD ; 
 int /*<<< orphan*/  VERIFY_READ ; 
 scalar_t__ __copy_user (scalar_t__*,void const*,int) ; 
 int /*<<< orphan*/  access_ok (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  die (char*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_fpu () ; 
 int /*<<< orphan*/  enable_fpu () ; 
 int generate_and_check_address (struct pt_regs*,int,int,int,scalar_t__*) ; 
 TYPE_4__* last_task_used_math ; 
 int /*<<< orphan*/  printk (char*,int,unsigned long) ; 
 int /*<<< orphan*/  save_fpu (TYPE_4__*,struct pt_regs*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static int misaligned_fpu_load(struct pt_regs *regs,
			   __u32 opcode,
			   int displacement_not_indexed,
			   int width_shift,
			   int do_paired_load)
{
	/* Return -1 for a fault, 0 for OK */
	int error;
	int destreg;
	__u64 address;

	error = generate_and_check_address(regs, opcode,
			displacement_not_indexed, width_shift, &address);
	if (error < 0) {
		return error;
	}

	destreg = (opcode >> 4) & 0x3f;
	if (user_mode(regs)) {
		__u64 buffer;
		__u32 buflo, bufhi;

		if (!access_ok(VERIFY_READ, (unsigned long) address, 1UL<<width_shift)) {
			return -1;
		}

		if (__copy_user(&buffer, (const void *)(int)address, (1 << width_shift)) > 0) {
			return -1; /* fault */
		}
		/* 'current' may be the current owner of the FPU state, so
		   context switch the registers into memory so they can be
		   indexed by register number. */
		if (last_task_used_math == current) {
			enable_fpu();
			save_fpu(current, regs);
			disable_fpu();
			last_task_used_math = NULL;
			regs->sr |= SR_FD;
		}

		buflo = *(__u32*) &buffer;
		bufhi = *(1 + (__u32*) &buffer);

		switch (width_shift) {
		case 2:
			current->thread.fpu.hard.fp_regs[destreg] = buflo;
			break;
		case 3:
			if (do_paired_load) {
				current->thread.fpu.hard.fp_regs[destreg] = buflo;
				current->thread.fpu.hard.fp_regs[destreg+1] = bufhi;
			} else {
#if defined(CONFIG_CPU_LITTLE_ENDIAN)
				current->thread.fpu.hard.fp_regs[destreg] = bufhi;
				current->thread.fpu.hard.fp_regs[destreg+1] = buflo;
#else
				current->thread.fpu.hard.fp_regs[destreg] = buflo;
				current->thread.fpu.hard.fp_regs[destreg+1] = bufhi;
#endif
			}
			break;
		default:
			printk("Unexpected width_shift %d in misaligned_fpu_load, PC=%08lx\n",
				width_shift, (unsigned long) regs->pc);
			break;
		}
		return 0;
	} else {
		die ("Misaligned FPU load inside kernel", regs, 0);
		return -1;
	}


}