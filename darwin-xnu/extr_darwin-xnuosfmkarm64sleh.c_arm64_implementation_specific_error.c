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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  panic_plain (char*) ; 

__attribute__((used)) static void
arm64_implementation_specific_error(arm_saved_state_t *state, uint32_t esr, vm_offset_t far)
{
#if defined(APPLE_ARM64_ARCH_FAMILY)
	uint64_t fed_err_sts, mmu_err_sts, lsu_err_sts;
#if defined(NO_ECORE)
	uint64_t l2c_err_sts, l2c_err_adr, l2c_err_inf;

	mmu_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_MMU_ERR_STS));
	l2c_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_L2C_ERR_STS));
	l2c_err_adr = __builtin_arm_rsr64(STR(ARM64_REG_L2C_ERR_ADR));
	l2c_err_inf = __builtin_arm_rsr64(STR(ARM64_REG_L2C_ERR_INF));
	lsu_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_LSU_ERR_STS));
	fed_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_FED_ERR_STS));

	panic_plain("Unhandled " CPU_NAME
	            " implementation specific error. state=%p esr=%#x far=%p\n"
	            "\tlsu_err_sts:%p, fed_err_sts:%p, mmu_err_sts:%p\n"
	            "\tl2c_err_sts:%p, l2c_err_adr:%p, l2c_err_inf:%p\n",
	            state, esr, (void *)far,
	            (void *)lsu_err_sts, (void *)fed_err_sts, (void *)mmu_err_sts,
	            (void *)l2c_err_sts, (void *)l2c_err_adr, (void *)l2c_err_inf);

#elif defined(HAS_MIGSTS)
	uint64_t l2c_err_sts, l2c_err_adr, l2c_err_inf, mpidr, migsts;

	mpidr = __builtin_arm_rsr64("MPIDR_EL1");
	migsts = __builtin_arm_rsr64(STR(ARM64_REG_MIGSTS_EL1));
	mmu_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_MMU_ERR_STS));
	l2c_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_L2C_ERR_STS));
	l2c_err_adr = __builtin_arm_rsr64(STR(ARM64_REG_L2C_ERR_ADR));
	l2c_err_inf = __builtin_arm_rsr64(STR(ARM64_REG_L2C_ERR_INF));
	lsu_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_LSU_ERR_STS));
	fed_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_FED_ERR_STS));

	panic_plain("Unhandled " CPU_NAME
	            " implementation specific error. state=%p esr=%#x far=%p p-core?%d migsts=%p\n"
	            "\tlsu_err_sts:%p, fed_err_sts:%p, mmu_err_sts:%p\n"
	            "\tl2c_err_sts:%p, l2c_err_adr:%p, l2c_err_inf:%p\n",
	            state, esr, (void *)far, !!(mpidr & MPIDR_PNE), (void *)migsts,
	            (void *)lsu_err_sts, (void *)fed_err_sts, (void *)mmu_err_sts,
	            (void *)l2c_err_sts, (void *)l2c_err_adr, (void *)l2c_err_inf);
#else // !defined(NO_ECORE) && !defined(HAS_MIGSTS)
	uint64_t llc_err_sts, llc_err_adr, llc_err_inf, mpidr;

	mpidr = __builtin_arm_rsr64("MPIDR_EL1");

	if (mpidr & MPIDR_PNE) {
		mmu_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_MMU_ERR_STS));
		lsu_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_LSU_ERR_STS));
		fed_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_FED_ERR_STS));
	} else {
		mmu_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_E_MMU_ERR_STS));
		lsu_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_E_LSU_ERR_STS));
		fed_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_E_FED_ERR_STS));
	}

	llc_err_sts = __builtin_arm_rsr64(STR(ARM64_REG_L2C_ERR_STS));
	llc_err_adr = __builtin_arm_rsr64(STR(ARM64_REG_L2C_ERR_ADR));
	llc_err_inf = __builtin_arm_rsr64(STR(ARM64_REG_L2C_ERR_INF));

	panic_plain("Unhandled " CPU_NAME
	            " implementation specific error. state=%p esr=%#x far=%p p-core?%d\n"
	            "\tlsu_err_sts:%p, fed_err_sts:%p, mmu_err_sts:%p\n"
	            "\tllc_err_sts:%p, llc_err_adr:%p, llc_err_inf:%p\n",
	            state, esr, (void *)far, !!(mpidr & MPIDR_PNE),
	            (void *)lsu_err_sts, (void *)fed_err_sts, (void *)mmu_err_sts,
	            (void *)llc_err_sts, (void *)llc_err_adr, (void *)llc_err_inf);
#endif
#else // !defined(APPLE_ARM64_ARCH_FAMILY)
#pragma unused (state, esr, far)
	panic_plain("Unhandled implementation specific error\n");
#endif
}