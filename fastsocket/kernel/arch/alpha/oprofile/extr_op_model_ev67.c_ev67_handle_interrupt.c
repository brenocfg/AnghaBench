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
struct pt_regs {unsigned long pc; } ;
struct op_counter_config {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_DTB_MISS ; 
 int /*<<< orphan*/  PM_ITB_MISS ; 
 int /*<<< orphan*/  PM_LOAD_STORE ; 
 int /*<<< orphan*/  PM_MISPREDICT ; 
 int /*<<< orphan*/  PM_REPLAY ; 
 int /*<<< orphan*/  PM_STALLED ; 
 int /*<<< orphan*/  PM_TAKEN ; 
 int /*<<< orphan*/  PM_UNALIGNED ; 
 int /*<<< orphan*/  op_add_pm (unsigned long,int,unsigned long,struct op_counter_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oprofile_add_pc (unsigned long,int,unsigned long) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 
 void* wrperfmon (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ev67_handle_interrupt(unsigned long which, struct pt_regs *regs,
		      struct op_counter_config *ctr)
{
	unsigned long pmpc, pctr_ctl;
	int kern = !user_mode(regs);
	int mispredict = 0;
	union {
		unsigned long v;
		struct {
			unsigned reserved:	30; /*  0-29 */
			unsigned overcount:	 3; /* 30-32 */
			unsigned icache_miss:	 1; /*    33 */
			unsigned trap_type:	 4; /* 34-37 */
			unsigned load_store:	 1; /*    38 */
			unsigned trap:		 1; /*    39 */
			unsigned mispredict:	 1; /*    40 */
		} fields;
	} i_stat;

	enum trap_types {
		TRAP_REPLAY,
		TRAP_INVALID0,
		TRAP_DTB_DOUBLE_MISS_3,
		TRAP_DTB_DOUBLE_MISS_4,
		TRAP_FP_DISABLED,
		TRAP_UNALIGNED,
		TRAP_DTB_SINGLE_MISS,
		TRAP_DSTREAM_FAULT,
		TRAP_OPCDEC,
		TRAP_INVALID1,
		TRAP_MACHINE_CHECK,
		TRAP_INVALID2,
		TRAP_ARITHMETIC,
		TRAP_INVALID3,
		TRAP_MT_FPCR,
		TRAP_RESET
	};

	pmpc = wrperfmon(9, 0);
	/* ??? Don't know how to handle physical-mode PALcode address.  */
	if (pmpc & 1)
		return;
	pmpc &= ~2;		/* clear reserved bit */

	i_stat.v = wrperfmon(8, 0);
	if (i_stat.fields.trap) {
		switch (i_stat.fields.trap_type) {
		case TRAP_INVALID1:
		case TRAP_INVALID2:
		case TRAP_INVALID3:
			/* Pipeline redirection ocurred. PMPC points
			   to PALcode. Recognize ITB miss by PALcode
			   offset address, and get actual PC from
			   EXC_ADDR.  */
			oprofile_add_pc(regs->pc, kern, which);
			if ((pmpc & ((1 << 15) - 1)) ==  581)
				op_add_pm(regs->pc, kern, which,
					  ctr, PM_ITB_MISS);
			/* Most other bit and counter values will be
			   those for the first instruction in the
			   fault handler, so we're done.  */
			return;
		case TRAP_REPLAY:
			op_add_pm(pmpc, kern, which, ctr,
				  (i_stat.fields.load_store
				   ? PM_LOAD_STORE : PM_REPLAY));
			break;
		case TRAP_DTB_DOUBLE_MISS_3:
		case TRAP_DTB_DOUBLE_MISS_4:
		case TRAP_DTB_SINGLE_MISS:
			op_add_pm(pmpc, kern, which, ctr, PM_DTB_MISS);
			break;
		case TRAP_UNALIGNED:
			op_add_pm(pmpc, kern, which, ctr, PM_UNALIGNED);
			break;
		case TRAP_INVALID0:
		case TRAP_FP_DISABLED:
		case TRAP_DSTREAM_FAULT:
		case TRAP_OPCDEC:
		case TRAP_MACHINE_CHECK:
		case TRAP_ARITHMETIC:
		case TRAP_MT_FPCR:
		case TRAP_RESET:
			break;
		}

		/* ??? JSR/JMP/RET/COR or HW_JSR/HW_JMP/HW_RET/HW_COR
		   mispredicts do not set this bit but can be
		   recognized by the presence of one of these
		   instructions at the PMPC location with bit 39
		   set.  */
		if (i_stat.fields.mispredict) {
			mispredict = 1;
			op_add_pm(pmpc, kern, which, ctr, PM_MISPREDICT);
		}
	}

	oprofile_add_pc(pmpc, kern, which);

	pctr_ctl = wrperfmon(5, 0);
	if (pctr_ctl & (1UL << 27))
		op_add_pm(pmpc, kern, which, ctr, PM_STALLED);

	/* Unfortunately, TAK is undefined on mispredicted branches.
	   ??? It is also undefined for non-cbranch insns, should
	   check that.  */
	if (!mispredict && pctr_ctl & (1UL << 0))
		op_add_pm(pmpc, kern, which, ctr, PM_TAKEN);
}