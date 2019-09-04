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
typedef  scalar_t__ uint8_t ;
struct modctl {int /*<<< orphan*/  mod_loadcnt; } ;
typedef  scalar_t__ machine_inst_t ;
struct TYPE_6__ {scalar_t__ fbtp_currentval; scalar_t__ fbtp_patchval; scalar_t__* fbtp_patchpoint; uintptr_t fbtp_roffset; void* fbtp_id; void* fbtp_hashnext; scalar_t__ fbtp_savedval; int /*<<< orphan*/  fbtp_rval; int /*<<< orphan*/  fbtp_loadcnt; struct modctl* fbtp_ctl; struct TYPE_6__* fbtp_next; int /*<<< orphan*/  fbtp_name; } ;
typedef  TYPE_1__ fbt_probe_t ;
typedef  scalar_t__ dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DTRACE_INVOP_LEAVE ; 
 int /*<<< orphan*/  DTRACE_INVOP_MOV_RSP_RBP ; 
 int /*<<< orphan*/  DTRACE_INVOP_POP_RBP ; 
 size_t FBT_ADDR2NDX (scalar_t__*) ; 
 int /*<<< orphan*/  FBT_AFRAMES_ENTRY ; 
 int /*<<< orphan*/  FBT_AFRAMES_RETURN ; 
 int /*<<< orphan*/  FBT_ENTRY ; 
 scalar_t__ FBT_JMP_FAR_ABS ; 
 int FBT_JMP_FAR_ABS_LEN ; 
 scalar_t__ FBT_JMP_NEAR_REL ; 
 int FBT_JMP_NEAR_REL_LEN ; 
 scalar_t__ FBT_JMP_SHORT_REL ; 
 int FBT_JMP_SHORT_REL_LEN ; 
 scalar_t__ FBT_LEAVE ; 
 scalar_t__ FBT_MOV_RSP_RBP0 ; 
 scalar_t__ FBT_MOV_RSP_RBP1 ; 
 void* FBT_PATCHVAL ; 
 scalar_t__ FBT_POP_RBP ; 
 scalar_t__ FBT_PUSH_RBP ; 
 scalar_t__ FBT_RET ; 
 int /*<<< orphan*/  FBT_RETURN ; 
 scalar_t__ FBT_RET_IMM16 ; 
 int FBT_RET_IMM16_LEN ; 
 int FBT_RET_LEN ; 
 scalar_t__ FBT_REX_RSP_RBP ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MAX_FBTP_NAME_CHARS ; 
 int dtrace_instr_size (scalar_t__*) ; 
 TYPE_1__* dtrace_probe_arg (int /*<<< orphan*/ ,scalar_t__) ; 
 void* dtrace_probe_create (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ dtrace_probe_lookup (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbt_enable (int /*<<< orphan*/ *,void*,TYPE_1__*) ; 
 int /*<<< orphan*/  fbt_id ; 
 void** fbt_probetab ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int /*<<< orphan*/ ) ; 

void
fbt_provide_probe(struct modctl *ctl, const char *modname, const char* symbolName, machine_inst_t* symbolStart, machine_inst_t* instrHigh)
{
	unsigned int			j;
	unsigned int			doenable = 0;
	dtrace_id_t			thisid;

	fbt_probe_t *newfbt, *retfbt, *entryfbt;
	machine_inst_t *instr, *limit, theInstr, i1, i2, i3;
	int size;

	/*
	 * Guard against null symbols
	 */
	if (!symbolStart || !instrHigh || instrHigh < symbolStart) {
		kprintf("dtrace: %s has an invalid address\n", symbolName);
		return;
	}

	for (j = 0, instr = symbolStart, theInstr = 0;
	     (j < 4) && (instrHigh > (instr + 2)); j++) {
		theInstr = instr[0];
		if (theInstr == FBT_PUSH_RBP || theInstr == FBT_RET || theInstr == FBT_RET_IMM16)
			break;

		if ((size = dtrace_instr_size(instr)) <= 0)
			break;

		instr += size;
	}

	if (theInstr != FBT_PUSH_RBP)
		return;

	i1 = instr[1];
	i2 = instr[2];
	i3 = instr[3];

	limit = (machine_inst_t *)instrHigh;

	if (i1 == FBT_REX_RSP_RBP && i2 == FBT_MOV_RSP_RBP0 && i3 == FBT_MOV_RSP_RBP1) {
		instr += 1; /* Advance to the mov %rsp,%rbp */
		theInstr = i1;
	} else {
		return;
	}
#if 0
	else {
		/*
		 * Sometimes, the compiler will schedule an intervening instruction
		 * in the function prologue. Example:
		 *
		 * _mach_vm_read:
		 * 000006d8        pushl   %ebp
		 * 000006d9        movl    $0x00000004,%edx
		 * 000006de        movl    %esp,%ebp
		 *
		 * Try the next instruction, to see if it is a movl %esp,%ebp
		 */

		instr += 1; /* Advance past the pushl %ebp */
		if ((size = dtrace_instr_size(instr)) <= 0)
			return;

		instr += size;

		if ((instr + 1) >= limit)
			return;

		i1 = instr[0];
		i2 = instr[1];

		if (!(i1 == FBT_MOVL_ESP_EBP0_V0 && i2 == FBT_MOVL_ESP_EBP1_V0) &&
		    !(i1 == FBT_MOVL_ESP_EBP0_V1 && i2 == FBT_MOVL_ESP_EBP1_V1))
			return;

		/* instr already points at the movl %esp,%ebp */
		theInstr = i1;
	}
#endif
	thisid = dtrace_probe_lookup(fbt_id, modname, symbolName, FBT_ENTRY);
	newfbt = kmem_zalloc(sizeof (fbt_probe_t), KM_SLEEP);
	strlcpy( (char *)&(newfbt->fbtp_name), symbolName, MAX_FBTP_NAME_CHARS );

	if (thisid != 0) {
		/*
		 * The dtrace_probe previously existed, so we have to hook
		 * the newfbt entry onto the end of the existing fbt's chain.
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
	newfbt->fbtp_rval = DTRACE_INVOP_MOV_RSP_RBP;
	newfbt->fbtp_savedval = theInstr;
	newfbt->fbtp_patchval = FBT_PATCHVAL;
	newfbt->fbtp_currentval = 0;
	newfbt->fbtp_hashnext = fbt_probetab[FBT_ADDR2NDX(instr)];
	fbt_probetab[FBT_ADDR2NDX(instr)] = newfbt;

	if (doenable)
		fbt_enable(NULL, newfbt->fbtp_id, newfbt);

	/*
	 * The fbt entry chain is in place, one entry point per symbol.
	 * The fbt return chain can have multiple return points per symbol.
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

again:
	if (instr >= limit)
		return;

	/*
	 * If this disassembly fails, then we've likely walked off into
	 * a jump table or some other unsuitable area.  Bail out of the
	 * disassembly now.
	 */
	if ((size = dtrace_instr_size(instr)) <= 0)
		return;

	/*
	 * We (desperately) want to avoid erroneously instrumenting a
	 * jump table, especially given that our markers are pretty
	 * short:  two bytes on x86, and just one byte on amd64.  To
	 * determine if we're looking at a true instruction sequence
	 * or an inline jump table that happens to contain the same
	 * byte sequences, we resort to some heuristic sleeze:  we
	 * treat this instruction as being contained within a pointer,
	 * and see if that pointer points to within the body of the
	 * function.  If it does, we refuse to instrument it.
	 */
	for (j = 0; j < sizeof (uintptr_t); j++) {
		uintptr_t check = (uintptr_t)instr - j;
		uint8_t *ptr;

		if (check < (uintptr_t)symbolStart)
			break;

		if (check + sizeof (uintptr_t) > (uintptr_t)limit)
			continue;

		ptr = *(uint8_t **)check;

		if (ptr >= (uint8_t *)symbolStart && ptr < limit) {
			instr += size;
			goto again;
		}
	}

	/*
	 * OK, it's an instruction.
	 */
	theInstr = instr[0];

	/* Walked onto the start of the next routine? If so, bail out of this function. */
	if (theInstr == FBT_PUSH_RBP)
		return;

	if (!(size == 1 && (theInstr == FBT_POP_RBP || theInstr == FBT_LEAVE))) {
		instr += size;
		goto again;
	}

	/*
	 * Found the pop %rbp; or leave.
	 */
	machine_inst_t *patch_instr = instr;

	/*
	 * Scan forward for a "ret", or "jmp".
	 */
	instr += size;
	if (instr >= limit)
		return;

	size = dtrace_instr_size(instr);
	if (size <= 0) /* Failed instruction decode? */
		return;

	theInstr = instr[0];

	if (!(size == FBT_RET_LEN && (theInstr == FBT_RET)) &&
	    !(size == FBT_RET_IMM16_LEN && (theInstr == FBT_RET_IMM16)) &&
	    !(size == FBT_JMP_SHORT_REL_LEN && (theInstr == FBT_JMP_SHORT_REL)) &&
	    !(size == FBT_JMP_NEAR_REL_LEN && (theInstr == FBT_JMP_NEAR_REL)) &&
	    !(size == FBT_JMP_FAR_ABS_LEN && (theInstr == FBT_JMP_FAR_ABS)))
		return;

	/*
	 * pop %rbp; ret; or leave; ret; or leave; jmp tailCalledFun; -- We have a winner!
	 */
	newfbt = kmem_zalloc(sizeof (fbt_probe_t), KM_SLEEP);
	strlcpy( (char *)&(newfbt->fbtp_name), symbolName, MAX_FBTP_NAME_CHARS );

	if (retfbt == NULL) {
		newfbt->fbtp_id = dtrace_probe_create(fbt_id, modname,
						      symbolName, FBT_RETURN, FBT_AFRAMES_RETURN, newfbt);
	} else {
		retfbt->fbtp_next = newfbt;
		newfbt->fbtp_id = retfbt->fbtp_id;
	}

	retfbt = newfbt;
	newfbt->fbtp_patchpoint = patch_instr;
	newfbt->fbtp_ctl = ctl;
	newfbt->fbtp_loadcnt = ctl->mod_loadcnt;

	if (*patch_instr == FBT_POP_RBP) {
		newfbt->fbtp_rval = DTRACE_INVOP_POP_RBP;
	} else {
		ASSERT(*patch_instr == FBT_LEAVE);
		newfbt->fbtp_rval = DTRACE_INVOP_LEAVE;
	}
	newfbt->fbtp_roffset =
	(uintptr_t)(patch_instr - (uint8_t *)symbolStart);

	newfbt->fbtp_savedval = *patch_instr;
	newfbt->fbtp_patchval = FBT_PATCHVAL;
	newfbt->fbtp_hashnext = fbt_probetab[FBT_ADDR2NDX(patch_instr)];
	fbt_probetab[FBT_ADDR2NDX(patch_instr)] = newfbt;

	if (doenable)
		fbt_enable(NULL, newfbt->fbtp_id, newfbt);

	instr += size;
	goto again;
}