#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int u_char ;
typedef  int u32 ;
struct TYPE_7__ {int addr; int size; } ;
struct sym_pmc {int ret; TYPE_2__ sg; } ;
struct sym_hcb {int features; int rv_ctest3; int scripta_ba; int scripta_sz; int scriptb_ba; int scriptb_sz; int /*<<< orphan*/ * msgout; scalar_t__ scriptb0; scalar_t__ scripta0; } ;
struct TYPE_6__ {void* size; void* addr; } ;
struct TYPE_8__ {int sel_scntl3; } ;
struct TYPE_9__ {TYPE_1__ wresid; TYPE_3__ select; struct sym_pmc pm1; struct sym_pmc pm0; } ;
struct sym_ccb {TYPE_5__* cmd; int /*<<< orphan*/  lun; int /*<<< orphan*/  host_status; int /*<<< orphan*/  tag; TYPE_4__ phys; } ;
struct scsi_device {int /*<<< orphan*/  ppr; } ;
struct TYPE_10__ {struct scsi_device* device; } ;

/* Variables and functions */
 int CLF ; 
 int CSF ; 
 int DEBUG_FLAGS ; 
 int DEBUG_PHASE ; 
 int DEBUG_TINY ; 
 int DFS ; 
 int EWS ; 
 int FE_C10 ; 
 int FE_DFBC ; 
 int HF_ACT_PM ; 
 int HF_DP_SAVED ; 
 int HF_IN_PM0 ; 
 int HF_IN_PM1 ; 
 int /*<<< orphan*/  HF_PRT ; 
 int /*<<< orphan*/  HS_BUSY ; 
 int /*<<< orphan*/  IDENTIFY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int INB (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int INL (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int INW (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_TAG ; 
 int OLF ; 
 int OLF1 ; 
 int ORF ; 
 int ORF1 ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL_DSP (struct sym_hcb*,int) ; 
 int SCRIPTA_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int SCRIPTB_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int TE ; 
 int WSR ; 
 int /*<<< orphan*/  clrack ; 
 void* cpu_to_scr (int) ; 
 int /*<<< orphan*/  dispatch ; 
 int /*<<< orphan*/  ident_break ; 
 int /*<<< orphan*/  ident_break_atn ; 
 int /*<<< orphan*/  nc_ctest3 ; 
 int /*<<< orphan*/  nc_dbc ; 
 int /*<<< orphan*/  nc_dfbc ; 
 int /*<<< orphan*/  nc_dfifo ; 
 int /*<<< orphan*/  nc_dsa ; 
 int /*<<< orphan*/  nc_dsp ; 
 int /*<<< orphan*/  nc_sbcl ; 
 int /*<<< orphan*/  nc_scntl2 ; 
 int /*<<< orphan*/  nc_sstat0 ; 
 int /*<<< orphan*/  nc_sstat2 ; 
 int /*<<< orphan*/  nc_stest3 ; 
 int /*<<< orphan*/  nego_bad_phase ; 
 int /*<<< orphan*/  pm0_data ; 
 int /*<<< orphan*/  pm1_data ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int scr_to_cpu (int) ; 
 int /*<<< orphan*/  send_ident ; 
 int /*<<< orphan*/  send_ppr ; 
 int /*<<< orphan*/  send_sdtr ; 
 int /*<<< orphan*/  send_wdtr ; 
 struct sym_ccb* sym_ccb_from_dsa (struct sym_hcb*,int) ; 
 char* sym_name (struct sym_hcb*) ; 
 int /*<<< orphan*/  sym_print_addr (TYPE_5__*,char*,int,int,...) ; 
 int /*<<< orphan*/  sym_set_script_dp (struct sym_hcb*,struct sym_ccb*,int) ; 
 int /*<<< orphan*/  sym_start_reset (struct sym_hcb*) ; 
 int /*<<< orphan*/  wsr_ma_helper ; 

__attribute__((used)) static void sym_int_ma (struct sym_hcb *np)
{
	u32	dbc;
	u32	rest;
	u32	dsp;
	u32	dsa;
	u32	nxtdsp;
	u32	*vdsp;
	u32	oadr, olen;
	u32	*tblp;
        u32	newcmd;
	u_int	delta;
	u_char	cmd;
	u_char	hflags, hflags0;
	struct	sym_pmc *pm;
	struct sym_ccb *cp;

	dsp	= INL(np, nc_dsp);
	dbc	= INL(np, nc_dbc);
	dsa	= INL(np, nc_dsa);

	cmd	= dbc >> 24;
	rest	= dbc & 0xffffff;
	delta	= 0;

	/*
	 *  locate matching cp if any.
	 */
	cp = sym_ccb_from_dsa(np, dsa);

	/*
	 *  Donnot take into account dma fifo and various buffers in 
	 *  INPUT phase since the chip flushes everything before 
	 *  raising the MA interrupt for interrupted INPUT phases.
	 *  For DATA IN phase, we will check for the SWIDE later.
	 */
	if ((cmd & 7) != 1 && (cmd & 7) != 5) {
		u_char ss0, ss2;

		if (np->features & FE_DFBC)
			delta = INW(np, nc_dfbc);
		else {
			u32 dfifo;

			/*
			 * Read DFIFO, CTEST[4-6] using 1 PCI bus ownership.
			 */
			dfifo = INL(np, nc_dfifo);

			/*
			 *  Calculate remaining bytes in DMA fifo.
			 *  (CTEST5 = dfifo >> 16)
			 */
			if (dfifo & (DFS << 16))
				delta = ((((dfifo >> 8) & 0x300) |
				          (dfifo & 0xff)) - rest) & 0x3ff;
			else
				delta = ((dfifo & 0xff) - rest) & 0x7f;
		}

		/*
		 *  The data in the dma fifo has not been transfered to
		 *  the target -> add the amount to the rest
		 *  and clear the data.
		 *  Check the sstat2 register in case of wide transfer.
		 */
		rest += delta;
		ss0  = INB(np, nc_sstat0);
		if (ss0 & OLF) rest++;
		if (!(np->features & FE_C10))
			if (ss0 & ORF) rest++;
		if (cp && (cp->phys.select.sel_scntl3 & EWS)) {
			ss2 = INB(np, nc_sstat2);
			if (ss2 & OLF1) rest++;
			if (!(np->features & FE_C10))
				if (ss2 & ORF1) rest++;
		}

		/*
		 *  Clear fifos.
		 */
		OUTB(np, nc_ctest3, np->rv_ctest3 | CLF);	/* dma fifo  */
		OUTB(np, nc_stest3, TE|CSF);		/* scsi fifo */
	}

	/*
	 *  log the information
	 */
	if (DEBUG_FLAGS & (DEBUG_TINY|DEBUG_PHASE))
		printf ("P%x%x RL=%d D=%d ", cmd&7, INB(np, nc_sbcl)&7,
			(unsigned) rest, (unsigned) delta);

	/*
	 *  try to find the interrupted script command,
	 *  and the address at which to continue.
	 */
	vdsp	= NULL;
	nxtdsp	= 0;
	if	(dsp >  np->scripta_ba &&
		 dsp <= np->scripta_ba + np->scripta_sz) {
		vdsp = (u32 *)((char*)np->scripta0 + (dsp-np->scripta_ba-8));
		nxtdsp = dsp;
	}
	else if	(dsp >  np->scriptb_ba &&
		 dsp <= np->scriptb_ba + np->scriptb_sz) {
		vdsp = (u32 *)((char*)np->scriptb0 + (dsp-np->scriptb_ba-8));
		nxtdsp = dsp;
	}

	/*
	 *  log the information
	 */
	if (DEBUG_FLAGS & DEBUG_PHASE) {
		printf ("\nCP=%p DSP=%x NXT=%x VDSP=%p CMD=%x ",
			cp, (unsigned)dsp, (unsigned)nxtdsp, vdsp, cmd);
	}

	if (!vdsp) {
		printf ("%s: interrupted SCRIPT address not found.\n", 
			sym_name (np));
		goto reset_all;
	}

	if (!cp) {
		printf ("%s: SCSI phase error fixup: CCB already dequeued.\n", 
			sym_name (np));
		goto reset_all;
	}

	/*
	 *  get old startaddress and old length.
	 */
	oadr = scr_to_cpu(vdsp[1]);

	if (cmd & 0x10) {	/* Table indirect */
		tblp = (u32 *) ((char*) &cp->phys + oadr);
		olen = scr_to_cpu(tblp[0]);
		oadr = scr_to_cpu(tblp[1]);
	} else {
		tblp = (u32 *) 0;
		olen = scr_to_cpu(vdsp[0]) & 0xffffff;
	}

	if (DEBUG_FLAGS & DEBUG_PHASE) {
		printf ("OCMD=%x\nTBLP=%p OLEN=%x OADR=%x\n",
			(unsigned) (scr_to_cpu(vdsp[0]) >> 24),
			tblp,
			(unsigned) olen,
			(unsigned) oadr);
	}

	/*
	 *  check cmd against assumed interrupted script command.
	 *  If dt data phase, the MOVE instruction hasn't bit 4 of 
	 *  the phase.
	 */
	if (((cmd & 2) ? cmd : (cmd & ~4)) != (scr_to_cpu(vdsp[0]) >> 24)) {
		sym_print_addr(cp->cmd,
			"internal error: cmd=%02x != %02x=(vdsp[0] >> 24)\n",
			cmd, scr_to_cpu(vdsp[0]) >> 24);

		goto reset_all;
	}

	/*
	 *  if old phase not dataphase, leave here.
	 */
	if (cmd & 2) {
		sym_print_addr(cp->cmd,
			"phase change %x-%x %d@%08x resid=%d.\n",
			cmd&7, INB(np, nc_sbcl)&7, (unsigned)olen,
			(unsigned)oadr, (unsigned)rest);
		goto unexpected_phase;
	}

	/*
	 *  Choose the correct PM save area.
	 *
	 *  Look at the PM_SAVE SCRIPT if you want to understand 
	 *  this stuff. The equivalent code is implemented in 
	 *  SCRIPTS for the 895A, 896 and 1010 that are able to 
	 *  handle PM from the SCRIPTS processor.
	 */
	hflags0 = INB(np, HF_PRT);
	hflags = hflags0;

	if (hflags & (HF_IN_PM0 | HF_IN_PM1 | HF_DP_SAVED)) {
		if (hflags & HF_IN_PM0)
			nxtdsp = scr_to_cpu(cp->phys.pm0.ret);
		else if	(hflags & HF_IN_PM1)
			nxtdsp = scr_to_cpu(cp->phys.pm1.ret);

		if (hflags & HF_DP_SAVED)
			hflags ^= HF_ACT_PM;
	}

	if (!(hflags & HF_ACT_PM)) {
		pm = &cp->phys.pm0;
		newcmd = SCRIPTA_BA(np, pm0_data);
	}
	else {
		pm = &cp->phys.pm1;
		newcmd = SCRIPTA_BA(np, pm1_data);
	}

	hflags &= ~(HF_IN_PM0 | HF_IN_PM1 | HF_DP_SAVED);
	if (hflags != hflags0)
		OUTB(np, HF_PRT, hflags);

	/*
	 *  fillin the phase mismatch context
	 */
	pm->sg.addr = cpu_to_scr(oadr + olen - rest);
	pm->sg.size = cpu_to_scr(rest);
	pm->ret     = cpu_to_scr(nxtdsp);

	/*
	 *  If we have a SWIDE,
	 *  - prepare the address to write the SWIDE from SCRIPTS,
	 *  - compute the SCRIPTS address to restart from,
	 *  - move current data pointer context by one byte.
	 */
	nxtdsp = SCRIPTA_BA(np, dispatch);
	if ((cmd & 7) == 1 && cp && (cp->phys.select.sel_scntl3 & EWS) &&
	    (INB(np, nc_scntl2) & WSR)) {
		u32 tmp;

		/*
		 *  Set up the table indirect for the MOVE
		 *  of the residual byte and adjust the data 
		 *  pointer context.
		 */
		tmp = scr_to_cpu(pm->sg.addr);
		cp->phys.wresid.addr = cpu_to_scr(tmp);
		pm->sg.addr = cpu_to_scr(tmp + 1);
		tmp = scr_to_cpu(pm->sg.size);
		cp->phys.wresid.size = cpu_to_scr((tmp&0xff000000) | 1);
		pm->sg.size = cpu_to_scr(tmp - 1);

		/*
		 *  If only the residual byte is to be moved, 
		 *  no PM context is needed.
		 */
		if ((tmp&0xffffff) == 1)
			newcmd = pm->ret;

		/*
		 *  Prepare the address of SCRIPTS that will 
		 *  move the residual byte to memory.
		 */
		nxtdsp = SCRIPTB_BA(np, wsr_ma_helper);
	}

	if (DEBUG_FLAGS & DEBUG_PHASE) {
		sym_print_addr(cp->cmd, "PM %x %x %x / %x %x %x.\n",
			hflags0, hflags, newcmd,
			(unsigned)scr_to_cpu(pm->sg.addr),
			(unsigned)scr_to_cpu(pm->sg.size),
			(unsigned)scr_to_cpu(pm->ret));
	}

	/*
	 *  Restart the SCRIPTS processor.
	 */
	sym_set_script_dp (np, cp, newcmd);
	OUTL_DSP(np, nxtdsp);
	return;

	/*
	 *  Unexpected phase changes that occurs when the current phase 
	 *  is not a DATA IN or DATA OUT phase are due to error conditions.
	 *  Such event may only happen when the SCRIPTS is using a 
	 *  multibyte SCSI MOVE.
	 *
	 *  Phase change		Some possible cause
	 *
	 *  COMMAND  --> MSG IN	SCSI parity error detected by target.
	 *  COMMAND  --> STATUS	Bad command or refused by target.
	 *  MSG OUT  --> MSG IN     Message rejected by target.
	 *  MSG OUT  --> COMMAND    Bogus target that discards extended
	 *  			negotiation messages.
	 *
	 *  The code below does not care of the new phase and so 
	 *  trusts the target. Why to annoy it ?
	 *  If the interrupted phase is COMMAND phase, we restart at
	 *  dispatcher.
	 *  If a target does not get all the messages after selection, 
	 *  the code assumes blindly that the target discards extended 
	 *  messages and clears the negotiation status.
	 *  If the target does not want all our response to negotiation,
	 *  we force a SIR_NEGO_PROTO interrupt (it is a hack that avoids 
	 *  bloat for such a should_not_happen situation).
	 *  In all other situation, we reset the BUS.
	 *  Are these assumptions reasonnable ? (Wait and see ...)
	 */
unexpected_phase:
	dsp -= 8;
	nxtdsp = 0;

	switch (cmd & 7) {
	case 2:	/* COMMAND phase */
		nxtdsp = SCRIPTA_BA(np, dispatch);
		break;
#if 0
	case 3:	/* STATUS  phase */
		nxtdsp = SCRIPTA_BA(np, dispatch);
		break;
#endif
	case 6:	/* MSG OUT phase */
		/*
		 *  If the device may want to use untagged when we want 
		 *  tagged, we prepare an IDENTIFY without disc. granted, 
		 *  since we will not be able to handle reselect.
		 *  Otherwise, we just don't care.
		 */
		if	(dsp == SCRIPTA_BA(np, send_ident)) {
			if (cp->tag != NO_TAG && olen - rest <= 3) {
				cp->host_status = HS_BUSY;
				np->msgout[0] = IDENTIFY(0, cp->lun);
				nxtdsp = SCRIPTB_BA(np, ident_break_atn);
			}
			else
				nxtdsp = SCRIPTB_BA(np, ident_break);
		}
		else if	(dsp == SCRIPTB_BA(np, send_wdtr) ||
			 dsp == SCRIPTB_BA(np, send_sdtr) ||
			 dsp == SCRIPTB_BA(np, send_ppr)) {
			nxtdsp = SCRIPTB_BA(np, nego_bad_phase);
			if (dsp == SCRIPTB_BA(np, send_ppr)) {
				struct scsi_device *dev = cp->cmd->device;
				dev->ppr = 0;
			}
		}
		break;
#if 0
	case 7:	/* MSG IN  phase */
		nxtdsp = SCRIPTA_BA(np, clrack);
		break;
#endif
	}

	if (nxtdsp) {
		OUTL_DSP(np, nxtdsp);
		return;
	}

reset_all:
	sym_start_reset(np);
}