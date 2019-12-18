#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread_info {int tp_value; } ;
struct pt_regs {int* regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  linesz; } ;
struct TYPE_4__ {int /*<<< orphan*/  linesz; } ;
struct TYPE_6__ {int /*<<< orphan*/  cputype; TYPE_2__ icache; TYPE_1__ dcache; } ;

/* Variables and functions */
#define  CPU_20KC 129 
#define  CPU_25KF 128 
 unsigned int FUNC ; 
 unsigned int OPCODE ; 
 unsigned int RD ; 
 unsigned int RDHWR ; 
 unsigned int RT ; 
 unsigned int SPEC3 ; 
 int /*<<< orphan*/  current ; 
 TYPE_3__ current_cpu_data ; 
 int min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_c0_count () ; 
 int smp_processor_id () ; 
 struct thread_info* task_thread_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simulate_rdhwr(struct pt_regs *regs, unsigned int opcode)
{
	struct thread_info *ti = task_thread_info(current);

	if ((opcode & OPCODE) == SPEC3 && (opcode & FUNC) == RDHWR) {
		int rd = (opcode & RD) >> 11;
		int rt = (opcode & RT) >> 16;
		switch (rd) {
		case 0:		/* CPU number */
			regs->regs[rt] = smp_processor_id();
			return 0;
		case 1:		/* SYNCI length */
			regs->regs[rt] = min(current_cpu_data.dcache.linesz,
					     current_cpu_data.icache.linesz);
			return 0;
		case 2:		/* Read count register */
			regs->regs[rt] = read_c0_count();
			return 0;
		case 3:		/* Count register resolution */
			switch (current_cpu_data.cputype) {
			case CPU_20KC:
			case CPU_25KF:
				regs->regs[rt] = 1;
				break;
			default:
				regs->regs[rt] = 2;
			}
			return 0;
		case 29:
			regs->regs[rt] = ti->tp_value;
			return 0;
		default:
			return -1;
		}
	}

	/* Not ours.  */
	return -1;
}