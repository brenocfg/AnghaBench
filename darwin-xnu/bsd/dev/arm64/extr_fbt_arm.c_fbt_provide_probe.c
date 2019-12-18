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
typedef  int /*<<< orphan*/  uint64_t ;
struct modctl {int /*<<< orphan*/  mod_loadcnt; } ;
typedef  void* machine_inst_t ;
struct TYPE_6__ {scalar_t__ fbtp_currentval; scalar_t__ fbtp_patchval; void** fbtp_patchpoint; uintptr_t fbtp_roffset; void* fbtp_id; void* fbtp_hashnext; void* fbtp_savedval; int /*<<< orphan*/  fbtp_rval; int /*<<< orphan*/  fbtp_loadcnt; struct modctl* fbtp_ctl; struct TYPE_6__* fbtp_next; int /*<<< orphan*/  fbtp_name; } ;
typedef  TYPE_1__ fbt_probe_t ;
typedef  scalar_t__ dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACE_INVOP_PUSH_FRAME ; 
 int /*<<< orphan*/  DTRACE_INVOP_RET ; 
 size_t FBT_ADDR2NDX (void**) ; 
 int /*<<< orphan*/  FBT_AFRAMES_ENTRY ; 
 int /*<<< orphan*/  FBT_AFRAMES_RETURN ; 
 int /*<<< orphan*/  FBT_ENTRY ; 
 int FBT_GET_ARM64_B_IMM (void*) ; 
 scalar_t__ FBT_IS_ARM64_ADD_FP_SP (void*) ; 
 scalar_t__ FBT_IS_ARM64_B_INSTR (void*) ; 
 scalar_t__ FBT_IS_ARM64_FRAME_POP (void*) ; 
 scalar_t__ FBT_IS_ARM64_FRAME_PUSH (void*) ; 
 int FBT_IS_ARM64_RET (void*) ; 
 void* FBT_PATCHVAL ; 
 int /*<<< orphan*/  FBT_RETURN ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MAX_FBTP_NAME_CHARS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* dtrace_probe_arg (int /*<<< orphan*/ ,scalar_t__) ; 
 void* dtrace_probe_create (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ dtrace_probe_lookup (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbt_enable (int /*<<< orphan*/ *,void*,TYPE_1__*) ; 
 int /*<<< orphan*/  fbt_id ; 
 void** fbt_probetab ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,char const*,...) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 

void
fbt_provide_probe(struct modctl *ctl, const char *modname, const char* symbolName, machine_inst_t* symbolStart, machine_inst_t *instrHigh)
{
        int		doenable = 0;
	dtrace_id_t	thisid;

	fbt_probe_t	*newfbt, *retfbt, *entryfbt;
	machine_inst_t *instr, *pushinstr = NULL, *limit, theInstr;
	int             foundPushLR, savedRegs;

	/*
	 * Guard against null and invalid symbols
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

	assert(sizeof(*instr) == 4);

	for (instr = symbolStart, theInstr = 0; instr < instrHigh; instr++)
	{
		/*
		 * Count the number of time we pushed something onto the stack
		 * before hitting a frame push. That will give us an estimation
		 * of how many stack pops we should expect when looking for the
		 * RET instruction.
		 */
		theInstr = *instr;
		if (FBT_IS_ARM64_FRAME_PUSH(theInstr)) {
			foundPushLR = 1;
			pushinstr = instr;
		}

		if (foundPushLR && (FBT_IS_ARM64_ADD_FP_SP(theInstr)))
			/* Guard against a random setting of fp from sp, we make sure we found the push first */
			break;
		if (FBT_IS_ARM64_RET(theInstr)) /* We've gone too far, bail. */
			break;
		if (FBT_IS_ARM64_FRAME_POP(theInstr)) /* We've gone too far, bail. */
			break;
	}

	if (!(foundPushLR && (FBT_IS_ARM64_ADD_FP_SP(theInstr)))) {
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
	newfbt->fbtp_rval = DTRACE_INVOP_PUSH_FRAME;
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
	 * before FP was adjusted.
	 */
	instr = pushinstr + 1;
again:
	if (instr >= limit)
		return;

	/* XXX FIXME ... extra jump table detection? */

	/*
	 * OK, it's an instruction.
	 */
	theInstr = *instr;

	/* Walked onto the start of the next routine? If so, bail out from this function */
	if (FBT_IS_ARM64_FRAME_PUSH(theInstr)) {
		if (!retfbt)
			kprintf("dtrace: fbt: No return probe for %s, walked to next routine at 0x%016llx\n",symbolName,(uint64_t)instr);
		return;
	}

	/* XXX fancy detection of end of function using PC-relative loads */

	/*
	 * Look for:
	 * 	ldp fp, lr, [sp], #val
	 * 	ldp fp, lr, [sp,  #val]
	 */
	if (!FBT_IS_ARM64_FRAME_POP(theInstr)) {
		instr++;
		goto again;
	}

	/* go to the next instruction */
	instr++;

	/* Scan ahead for a ret or a branch outside the function */
	for (; instr < limit; instr++) {
		theInstr = *instr;
		if (FBT_IS_ARM64_RET(theInstr))
			break;
		if (FBT_IS_ARM64_B_INSTR(theInstr)) {
			machine_inst_t *dest = instr + FBT_GET_ARM64_B_IMM(theInstr);
			/*
			 * Check whether the destination of the branch
			 * is outside of the function
			 */
			if (dest >= limit || dest < symbolStart)
				break;
		}
	}

	if (!FBT_IS_ARM64_RET(theInstr) && !FBT_IS_ARM64_B_INSTR(theInstr))
		return;

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

	ASSERT(FBT_IS_ARM64_RET(theInstr));
	newfbt->fbtp_rval = DTRACE_INVOP_RET;
	newfbt->fbtp_roffset = (uintptr_t) ((uint8_t*) instr - (uint8_t *)symbolStart);
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