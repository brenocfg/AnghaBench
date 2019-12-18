#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
struct modctl {int /*<<< orphan*/  mod_loadcnt; } ;
typedef  void* machine_inst_t ;
struct TYPE_6__ {scalar_t__ fbtp_currentval; scalar_t__ fbtp_patchval; void** fbtp_patchpoint; uintptr_t fbtp_roffset; void* fbtp_id; void* fbtp_hashnext; void* fbtp_savedval; int /*<<< orphan*/  fbtp_rval; int /*<<< orphan*/  fbtp_loadcnt; struct modctl* fbtp_ctl; struct TYPE_6__* fbtp_next; int /*<<< orphan*/  fbtp_name; } ;
typedef  TYPE_1__ fbt_probe_t ;
typedef  scalar_t__ dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACE_INVOP_POP_PC ; 
 int /*<<< orphan*/  DTRACE_INVOP_PUSH_LR ; 
 size_t FBT_ADDR2NDX (void**) ; 
 int /*<<< orphan*/  FBT_AFRAMES_ENTRY ; 
 int /*<<< orphan*/  FBT_AFRAMES_RETURN ; 
 int /*<<< orphan*/  FBT_ENTRY ; 
 scalar_t__ FBT_IS_THUMB32_LDR_PC (void*,void*) ; 
 int /*<<< orphan*/  FBT_IS_THUMB32_POP_R7LR (void*,void*) ; 
 scalar_t__ FBT_IS_THUMB_BX_REG (void*) ; 
 scalar_t__ FBT_IS_THUMB_LDR_PC (void*) ; 
 scalar_t__ FBT_IS_THUMB_MOV_SP_TO_R7 (void*) ; 
 scalar_t__ FBT_IS_THUMB_POP_PC (void*) ; 
 int /*<<< orphan*/  FBT_IS_THUMB_POP_R7 (void*) ; 
 scalar_t__ FBT_IS_THUMB_PUSH_LR (void*) ; 
 scalar_t__ FBT_IS_THUMB_SET_R7 (void*) ; 
 void* FBT_PATCHVAL ; 
 int /*<<< orphan*/  FBT_RETURN ; 
 int FBT_THUMB_STACK_REGS (void*) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MAX_FBTP_NAME_CHARS ; 
 int dtrace_instr_size (void*,int) ; 
 TYPE_1__* dtrace_probe_arg (int /*<<< orphan*/ ,scalar_t__) ; 
 void* dtrace_probe_create (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ dtrace_probe_lookup (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbt_enable (int /*<<< orphan*/ *,void*,TYPE_1__*) ; 
 int /*<<< orphan*/  fbt_id ; 
 void** fbt_probetab ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,char const*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ thumb32_ldr_pc_address (scalar_t__) ; 
 scalar_t__ thumb_ldr_pc_address (scalar_t__) ; 

void
fbt_provide_probe(struct modctl *ctl, const char *modname, const char* symbolName, machine_inst_t* symbolStart, machine_inst_t *instrHigh)
{
	unsigned int	j;
        int		doenable = 0;
	dtrace_id_t	thisid;

	fbt_probe_t	*newfbt, *retfbt, *entryfbt;
	machine_inst_t *instr, *pushinstr = NULL, *limit, theInstr;
	int             foundPushLR, savedRegs;

	/*
	 * Guard against null symbols
	 */
	if (!symbolStart || !instrHigh || instrHigh < symbolStart) {
		kprintf("dtrace: %s has an invalid address\n", symbolName);
		return;
	}

	/*
	 * Assume the compiler doesn't schedule instructions in the prologue.
	 */
	foundPushLR = 0;
	savedRegs = -1;
	limit = (machine_inst_t *)instrHigh;
	for (j = 0, instr = symbolStart, theInstr = 0;
	     (j < 8) && instr < instrHigh; j++, instr++)
	{
		theInstr = *instr;
		if (FBT_IS_THUMB_PUSH_LR(theInstr)) {
			foundPushLR = 1;
			/* Keep track of what registers we pushed. Compare this against the pop later. */
			savedRegs = FBT_THUMB_STACK_REGS(theInstr);
			pushinstr = instr;
		}
		if (foundPushLR && (FBT_IS_THUMB_SET_R7(theInstr) || FBT_IS_THUMB_MOV_SP_TO_R7(theInstr)))
			/* Guard against a random setting of r7 from sp, we make sure we found the push first */
			break;
		if (FBT_IS_THUMB_BX_REG(theInstr)) /* We've gone too far, bail. */
			break;
		if (FBT_IS_THUMB_POP_PC(theInstr)) /* We've gone too far, bail. */
			break;

		/* Check for 4 byte thumb instruction */
		if (dtrace_instr_size(theInstr,1) == 4)
			instr++;
	}

	if (!(foundPushLR && (FBT_IS_THUMB_SET_R7(theInstr) || FBT_IS_THUMB_MOV_SP_TO_R7(theInstr)))) {
		return;
	}

	thisid = dtrace_probe_lookup(fbt_id, modname, symbolName, FBT_ENTRY);
	newfbt = kmem_zalloc(sizeof(fbt_probe_t), KM_SLEEP);
	newfbt->fbtp_next = NULL;
	strlcpy( (char *)&(newfbt->fbtp_name), symbolName, MAX_FBTP_NAME_CHARS );

	if (thisid != 0) {
		/*
		 * The dtrace_probe previously existed, so we have to hook
		 * the newfbt entry onto the end of the existing fbt's
		 * chain.
		 * If we find an fbt entry that was previously patched to
		 * fire, (as indicated by the current patched value), then
		 * we want to enable this newfbt on the spot.
		 */
		entryfbt = dtrace_probe_arg (fbt_id, thisid);
		ASSERT (entryfbt != NULL);
		for(; entryfbt != NULL; entryfbt = entryfbt->fbtp_next) {
			if (entryfbt->fbtp_currentval == entryfbt->fbtp_patchval)
				doenable++;

			if (entryfbt->fbtp_next == NULL) {
				entryfbt->fbtp_next = newfbt;
				newfbt->fbtp_id = entryfbt->fbtp_id;
				break;
			}
		}
	}
	else {
		/*
		 * The dtrace_probe did not previously exist, so we
		 * create it and hook in the newfbt.  Since the probe is
		 * new, we obviously do not need to enable it on the spot.
		 */
		newfbt->fbtp_id = dtrace_probe_create(fbt_id, modname, symbolName, FBT_ENTRY, FBT_AFRAMES_ENTRY, newfbt);
		doenable = 0;
	}

	newfbt->fbtp_patchpoint = instr;
	newfbt->fbtp_ctl = ctl;
	newfbt->fbtp_loadcnt = ctl->mod_loadcnt;
	newfbt->fbtp_rval = DTRACE_INVOP_PUSH_LR;
	newfbt->fbtp_savedval = theInstr;
	newfbt->fbtp_patchval = FBT_PATCHVAL;
	newfbt->fbtp_currentval = 0;
	newfbt->fbtp_hashnext = fbt_probetab[FBT_ADDR2NDX(instr)];
	fbt_probetab[FBT_ADDR2NDX(instr)] = newfbt;

	if (doenable)
		fbt_enable(NULL, newfbt->fbtp_id, newfbt);

	/*
	 * The fbt entry chain is in place, one entry point per symbol.
	 * The fbt return chain can have multiple return points per
	 * symbol.
	 * Here we find the end of the fbt return chain.
	 */

	doenable=0;

	thisid = dtrace_probe_lookup(fbt_id, modname, symbolName, FBT_RETURN);

	if (thisid != 0) {
		/* The dtrace_probe previously existed, so we have to
		 * find the end of the existing fbt chain.  If we find
		 * an fbt return that was previously patched to fire,
		 * (as indicated by the currrent patched value), then
		 * we want to enable any new fbts on the spot.
		 */
		retfbt = dtrace_probe_arg (fbt_id, thisid);
		ASSERT(retfbt != NULL);
		for (;  retfbt != NULL; retfbt =  retfbt->fbtp_next) {
			if (retfbt->fbtp_currentval == retfbt->fbtp_patchval)
				doenable++;
			if(retfbt->fbtp_next == NULL)
				break;
		}
	}
	else {
		doenable = 0;
		retfbt = NULL;
	}

	/*
	 * Go back to the start of the function, in case
	 * the compiler emitted pcrel data loads
	 * before R7 was adjusted.
	 */
	instr = pushinstr + 1;
again:
	if (instr >= limit)
		return;

	/*
	 * We (desperately) want to avoid erroneously instrumenting a
	 * jump table. To determine if we're looking at a true instruction
	 * or an inline jump table that happens to contain the same
	 * byte sequences, we resort to some heuristic sleeze:  we
	 * treat this instruction as being contained within a pointer,
	 * and see if that pointer points to within the body of the
	 * function.  If it does, we refuse to instrument it.
	 */
	if (((uintptr_t)instr & 0x3) == 0) {
		machine_inst_t *ptr = *(machine_inst_t **)(void *)instr;

		if (ptr >= (machine_inst_t *)symbolStart && ptr < limit) {
			/* kprintf("dtrace: fbt: Found jump table in %s, at %08x\n",symbolName,(unsigned)instr); */
			instr++;
			goto again;
		}
	}

	/*
	 * OK, it's an instruction.
	 */
	theInstr = *instr;

	/* Walked onto the start of the next routine? If so, bail out from this function */
	if (FBT_IS_THUMB_PUSH_LR(theInstr)) {
		if (!retfbt)
			kprintf("dtrace: fbt: No return probe for %s, walked to next routine at %08x\n",symbolName,(unsigned)instr);
		return;
	}

	/* The PC relative data should be stored after the end of the function. If
	 * we see a PC relative load, assume the address to load from is the new end
	 * of the function. */
	if (FBT_IS_THUMB_LDR_PC(theInstr)) {
		uint32_t newlimit = thumb_ldr_pc_address((uint32_t) instr);
		if (newlimit < (uint32_t) limit)
			limit = (machine_inst_t*) newlimit;
	}
	if ((instr+1) < limit && FBT_IS_THUMB32_LDR_PC(*instr,*(instr+1))) {
		uint32_t newlimit = thumb32_ldr_pc_address((uint32_t) instr);
		if (newlimit < (uint32_t) limit)
			limit = (machine_inst_t*) newlimit;
	}

	/* Look for the 1. pop { ..., pc } or 2. pop { ..., r7 } ... bx reg or 3. ldmia.w sp!, { ..., r7, lr } ... bx reg */
	if (!FBT_IS_THUMB_POP_PC(theInstr) &&
	    !FBT_IS_THUMB_POP_R7(theInstr) &&
	    !FBT_IS_THUMB32_POP_R7LR(theInstr,*(instr+1))) {
		instr++;
		if (dtrace_instr_size(theInstr,1) == 4)
			instr++;
		goto again;
	}

	if (FBT_IS_THUMB_POP_PC(theInstr)) {
		if (savedRegs != FBT_THUMB_STACK_REGS(theInstr)) {
			/* What we're popping doesn't match what we're pushing, assume that we've
			 * gone too far in the function. Bail.
			 */
			kprintf("dtrace: fbt: No return probe for %s, popped regs don't match at %08x\n",symbolName,(unsigned)instr);
			return;
		}
	} else {
		/* Scan ahead for the bx */
		for (j = 0; (j < 4) && (instr < limit); j++, instr++) {
			theInstr = *instr;
			if (FBT_IS_THUMB_BX_REG(theInstr))
				break;
			if (dtrace_instr_size(theInstr,1) == 4)
				instr++;
		}

		if (!FBT_IS_THUMB_BX_REG(theInstr))
			return;
	}

	/*
	 * pop { ..., pc}, bx reg -- We have a winner!
	 */

	newfbt = kmem_zalloc(sizeof(fbt_probe_t), KM_SLEEP);
	newfbt->fbtp_next = NULL;
	strlcpy( (char *)&(newfbt->fbtp_name), symbolName, MAX_FBTP_NAME_CHARS );

	if (retfbt == NULL) {
		newfbt->fbtp_id = dtrace_probe_create(fbt_id, modname,
		    symbolName, FBT_RETURN, FBT_AFRAMES_RETURN, newfbt);
	} else {
		retfbt->fbtp_next = newfbt;
		newfbt->fbtp_id = retfbt->fbtp_id;
	}

	retfbt = newfbt;
	newfbt->fbtp_patchpoint = instr;
	newfbt->fbtp_ctl = ctl;
	newfbt->fbtp_loadcnt = ctl->mod_loadcnt;

	ASSERT(FBT_IS_THUMB_POP_PC(theInstr) || FBT_IS_THUMB_BX_REG(theInstr));
	newfbt->fbtp_rval = DTRACE_INVOP_POP_PC;
	newfbt->fbtp_roffset =
	    (uintptr_t) ((uint8_t*) instr - (uint8_t *)symbolStart);
	newfbt->fbtp_savedval = theInstr;
	newfbt->fbtp_patchval = FBT_PATCHVAL;
	newfbt->fbtp_currentval = 0;
	newfbt->fbtp_hashnext = fbt_probetab[FBT_ADDR2NDX(instr)];
	fbt_probetab[FBT_ADDR2NDX(instr)] = newfbt;

	if (doenable)
		fbt_enable(NULL, newfbt->fbtp_id, newfbt);

	instr++;
	goto again;
}