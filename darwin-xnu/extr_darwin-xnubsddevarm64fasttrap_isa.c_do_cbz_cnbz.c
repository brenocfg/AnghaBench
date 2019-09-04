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
typedef  int user_addr_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_4__ {int pc; } ;
typedef  TYPE_1__ arm_saved_state64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int extract_address_literal_sign_extended (int,int,int) ; 
 int get_saved_state64_regno (TYPE_1__*,int,int) ; 

__attribute__((used)) static void
do_cbz_cnbz(arm_saved_state64_t *regs64, uint32_t regwidth, uint32_t instr, int is_cbz, user_addr_t *pc_out)
{
	uint32_t regno;
	uint64_t regval;
	uint64_t offset;

	/* Extract register */
	regno = (instr & 0x1f);
	assert(regno <= 31);
	regval = get_saved_state64_regno(regs64, regno, 1);

	/* Control for size */
	if (regwidth == 32) {
		regval &= 0xFFFFFFFFULL;
	}

	/* Extract offset */
	offset = extract_address_literal_sign_extended(instr, 5, 19); 

	/* Do test */
	if ((is_cbz && regval == 0) || ((!is_cbz) && regval != 0)) {
		/* Set PC from label */
		*pc_out = regs64->pc + offset;
	} else {
		/* Advance PC */
		*pc_out = regs64->pc + 4;
	}
}