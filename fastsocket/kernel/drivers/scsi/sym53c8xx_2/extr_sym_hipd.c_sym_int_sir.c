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
typedef  size_t u_char ;
typedef  int /*<<< orphan*/  u32 ;
struct sym_tcb {int dummy; } ;
struct sym_hcb {int* msgout; int lastmsg; int* msgin; struct sym_tcb* target; } ;
struct sym_ccb {int host_flags; int /*<<< orphan*/  cmd; int /*<<< orphan*/  xerr_status; int /*<<< orphan*/  extra_bytes; } ;

/* Variables and functions */
 int DEBUG_FLAGS ; 
 int DEBUG_POINTER ; 
 int DEBUG_TINY ; 
 int /*<<< orphan*/  HF_EXT_ERR ; 
 int /*<<< orphan*/  HF_PRT ; 
 int HF_SENSE ; 
 int /*<<< orphan*/  HS_BUSY ; 
 int HS_NEGOTIATE ; 
 int /*<<< orphan*/  HS_PRT ; 
 int INB (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INL (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int M_ABORT ; 
 int M_ABORT_TAG ; 
#define  M_EXTENDED 157 
 int M_ID_ERROR ; 
#define  M_IGN_RESIDUE 156 
 void* M_NOOP ; 
 int M_PARITY ; 
#define  M_REJECT 155 
 int M_RESET ; 
#define  M_X_MODIFY_DP 154 
#define  M_X_PPR_REQ 153 
#define  M_X_SYNC_REQ 152 
#define  M_X_WIDE_REQ 151 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTL_DSP (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTOFFB (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTONB (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OUTONB_STD () ; 
 int /*<<< orphan*/  SCRIPTA_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRIPTB_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
#define  SIR_ABORT_SENT 150 
#define  SIR_BAD_PHASE 149 
#define  SIR_BAD_SCSI_STATUS 148 
#define  SIR_COMPLETE_ERROR 147 
#define  SIR_DATA_OVERRUN 146 
#define  SIR_DMAP_DIRTY 145 
#define  SIR_MSG_OUT_DONE 144 
#define  SIR_MSG_RECEIVED 143 
#define  SIR_MSG_WEIRD 142 
#define  SIR_NEGO_FAILED 141 
#define  SIR_NEGO_PROTO 140 
#define  SIR_REJECT_TO_SEND 139 
#define  SIR_RESEL_ABORTED 138 
#define  SIR_RESEL_BAD_I_T_L 137 
#define  SIR_RESEL_BAD_I_T_L_Q 136 
#define  SIR_RESEL_BAD_LUN 135 
#define  SIR_RESEL_NO_IDENTIFY 134 
#define  SIR_RESEL_NO_MSG_IN 133 
#define  SIR_SCRIPT_STOPPED 132 
#define  SIR_SEL_ATN_NO_MSG_OUT 131 
#define  SIR_SODL_UNDERRUN 130 
#define  SIR_SWIDE_OVERRUN 129 
#define  SIR_TARGET_SELECTED 128 
 int /*<<< orphan*/  XE_BAD_PHASE ; 
 int /*<<< orphan*/  XE_EXTRA_DATA ; 
 int /*<<< orphan*/  XE_PARITY_ERR ; 
 int /*<<< orphan*/  XE_SODL_UNRUN ; 
 int /*<<< orphan*/  XE_SWIDE_OVRUN ; 
 int /*<<< orphan*/  clrack ; 
 int /*<<< orphan*/  msg_bad ; 
 int /*<<< orphan*/  msg_weird ; 
 int /*<<< orphan*/  nc_dsa ; 
 int /*<<< orphan*/  nc_dsps ; 
 int /*<<< orphan*/  nc_scratcha ; 
 int /*<<< orphan*/  nc_sdid ; 
 int /*<<< orphan*/  printf (char*,size_t) ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  scr_to_cpu (int) ; 
 struct sym_ccb* sym_ccb_from_dsa (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_complete_error (struct sym_hcb*,struct sym_ccb*) ; 
 int /*<<< orphan*/  sym_modify_dp (struct sym_hcb*,struct sym_tcb*,struct sym_ccb*,int) ; 
 int /*<<< orphan*/  sym_nego_default (struct sym_hcb*,struct sym_tcb*,struct sym_ccb*) ; 
 int /*<<< orphan*/  sym_nego_rejected (struct sym_hcb*,struct sym_tcb*,struct sym_ccb*) ; 
 int /*<<< orphan*/  sym_ppr_nego (struct sym_hcb*,struct sym_tcb*,struct sym_ccb*) ; 
 int /*<<< orphan*/  sym_print_addr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sym_print_msg (struct sym_ccb*,char*,int*) ; 
 int /*<<< orphan*/  sym_sir_bad_scsi_status (struct sym_hcb*,size_t,struct sym_ccb*) ; 
 int /*<<< orphan*/  sym_sir_task_recovery (struct sym_hcb*,size_t) ; 
 int /*<<< orphan*/  sym_sync_nego (struct sym_hcb*,struct sym_tcb*,struct sym_ccb*) ; 
 int /*<<< orphan*/  sym_update_dmap_regs (struct sym_hcb*) ; 
 int /*<<< orphan*/  sym_wide_nego (struct sym_hcb*,struct sym_tcb*,struct sym_ccb*) ; 

__attribute__((used)) static void sym_int_sir(struct sym_hcb *np)
{
	u_char	num	= INB(np, nc_dsps);
	u32	dsa	= INL(np, nc_dsa);
	struct sym_ccb *cp	= sym_ccb_from_dsa(np, dsa);
	u_char	target	= INB(np, nc_sdid) & 0x0f;
	struct sym_tcb *tp	= &np->target[target];
	int	tmp;

	if (DEBUG_FLAGS & DEBUG_TINY) printf ("I#%d", num);

	switch (num) {
#if   SYM_CONF_DMA_ADDRESSING_MODE == 2
	/*
	 *  SCRIPTS tell us that we may have to update 
	 *  64 bit DMA segment registers.
	 */
	case SIR_DMAP_DIRTY:
		sym_update_dmap_regs(np);
		goto out;
#endif
	/*
	 *  Command has been completed with error condition 
	 *  or has been auto-sensed.
	 */
	case SIR_COMPLETE_ERROR:
		sym_complete_error(np, cp);
		return;
	/*
	 *  The C code is currently trying to recover from something.
	 *  Typically, user want to abort some command.
	 */
	case SIR_SCRIPT_STOPPED:
	case SIR_TARGET_SELECTED:
	case SIR_ABORT_SENT:
		sym_sir_task_recovery(np, num);
		return;
	/*
	 *  The device didn't go to MSG OUT phase after having 
	 *  been selected with ATN.  We do not want to handle that.
	 */
	case SIR_SEL_ATN_NO_MSG_OUT:
		scmd_printk(KERN_WARNING, cp->cmd,
				"No MSG OUT phase after selection with ATN\n");
		goto out_stuck;
	/*
	 *  The device didn't switch to MSG IN phase after 
	 *  having reselected the initiator.
	 */
	case SIR_RESEL_NO_MSG_IN:
		scmd_printk(KERN_WARNING, cp->cmd,
				"No MSG IN phase after reselection\n");
		goto out_stuck;
	/*
	 *  After reselection, the device sent a message that wasn't 
	 *  an IDENTIFY.
	 */
	case SIR_RESEL_NO_IDENTIFY:
		scmd_printk(KERN_WARNING, cp->cmd,
				"No IDENTIFY after reselection\n");
		goto out_stuck;
	/*
	 *  The device reselected a LUN we do not know about.
	 */
	case SIR_RESEL_BAD_LUN:
		np->msgout[0] = M_RESET;
		goto out;
	/*
	 *  The device reselected for an untagged nexus and we 
	 *  haven't any.
	 */
	case SIR_RESEL_BAD_I_T_L:
		np->msgout[0] = M_ABORT;
		goto out;
	/*
	 * The device reselected for a tagged nexus that we do not have.
	 */
	case SIR_RESEL_BAD_I_T_L_Q:
		np->msgout[0] = M_ABORT_TAG;
		goto out;
	/*
	 *  The SCRIPTS let us know that the device has grabbed 
	 *  our message and will abort the job.
	 */
	case SIR_RESEL_ABORTED:
		np->lastmsg = np->msgout[0];
		np->msgout[0] = M_NOOP;
		scmd_printk(KERN_WARNING, cp->cmd,
			"message %x sent on bad reselection\n", np->lastmsg);
		goto out;
	/*
	 *  The SCRIPTS let us know that a message has been 
	 *  successfully sent to the device.
	 */
	case SIR_MSG_OUT_DONE:
		np->lastmsg = np->msgout[0];
		np->msgout[0] = M_NOOP;
		/* Should we really care of that */
		if (np->lastmsg == M_PARITY || np->lastmsg == M_ID_ERROR) {
			if (cp) {
				cp->xerr_status &= ~XE_PARITY_ERR;
				if (!cp->xerr_status)
					OUTOFFB(np, HF_PRT, HF_EXT_ERR);
			}
		}
		goto out;
	/*
	 *  The device didn't send a GOOD SCSI status.
	 *  We may have some work to do prior to allow 
	 *  the SCRIPTS processor to continue.
	 */
	case SIR_BAD_SCSI_STATUS:
		if (!cp)
			goto out;
		sym_sir_bad_scsi_status(np, num, cp);
		return;
	/*
	 *  We are asked by the SCRIPTS to prepare a 
	 *  REJECT message.
	 */
	case SIR_REJECT_TO_SEND:
		sym_print_msg(cp, "M_REJECT to send for ", np->msgin);
		np->msgout[0] = M_REJECT;
		goto out;
	/*
	 *  We have been ODD at the end of a DATA IN 
	 *  transfer and the device didn't send a 
	 *  IGNORE WIDE RESIDUE message.
	 *  It is a data overrun condition.
	 */
	case SIR_SWIDE_OVERRUN:
		if (cp) {
			OUTONB(np, HF_PRT, HF_EXT_ERR);
			cp->xerr_status |= XE_SWIDE_OVRUN;
		}
		goto out;
	/*
	 *  We have been ODD at the end of a DATA OUT 
	 *  transfer.
	 *  It is a data underrun condition.
	 */
	case SIR_SODL_UNDERRUN:
		if (cp) {
			OUTONB(np, HF_PRT, HF_EXT_ERR);
			cp->xerr_status |= XE_SODL_UNRUN;
		}
		goto out;
	/*
	 *  The device wants us to tranfer more data than 
	 *  expected or in the wrong direction.
	 *  The number of extra bytes is in scratcha.
	 *  It is a data overrun condition.
	 */
	case SIR_DATA_OVERRUN:
		if (cp) {
			OUTONB(np, HF_PRT, HF_EXT_ERR);
			cp->xerr_status |= XE_EXTRA_DATA;
			cp->extra_bytes += INL(np, nc_scratcha);
		}
		goto out;
	/*
	 *  The device switched to an illegal phase (4/5).
	 */
	case SIR_BAD_PHASE:
		if (cp) {
			OUTONB(np, HF_PRT, HF_EXT_ERR);
			cp->xerr_status |= XE_BAD_PHASE;
		}
		goto out;
	/*
	 *  We received a message.
	 */
	case SIR_MSG_RECEIVED:
		if (!cp)
			goto out_stuck;
		switch (np->msgin [0]) {
		/*
		 *  We received an extended message.
		 *  We handle MODIFY DATA POINTER, SDTR, WDTR 
		 *  and reject all other extended messages.
		 */
		case M_EXTENDED:
			switch (np->msgin [2]) {
			case M_X_MODIFY_DP:
				if (DEBUG_FLAGS & DEBUG_POINTER)
					sym_print_msg(cp, NULL, np->msgin);
				tmp = (np->msgin[3]<<24) + (np->msgin[4]<<16) + 
				      (np->msgin[5]<<8)  + (np->msgin[6]);
				sym_modify_dp(np, tp, cp, tmp);
				return;
			case M_X_SYNC_REQ:
				sym_sync_nego(np, tp, cp);
				return;
			case M_X_PPR_REQ:
				sym_ppr_nego(np, tp, cp);
				return;
			case M_X_WIDE_REQ:
				sym_wide_nego(np, tp, cp);
				return;
			default:
				goto out_reject;
			}
			break;
		/*
		 *  We received a 1/2 byte message not handled from SCRIPTS.
		 *  We are only expecting MESSAGE REJECT and IGNORE WIDE 
		 *  RESIDUE messages that haven't been anticipated by 
		 *  SCRIPTS on SWIDE full condition. Unanticipated IGNORE 
		 *  WIDE RESIDUE messages are aliased as MODIFY DP (-1).
		 */
		case M_IGN_RESIDUE:
			if (DEBUG_FLAGS & DEBUG_POINTER)
				sym_print_msg(cp, NULL, np->msgin);
			if (cp->host_flags & HF_SENSE)
				OUTL_DSP(np, SCRIPTA_BA(np, clrack));
			else
				sym_modify_dp(np, tp, cp, -1);
			return;
		case M_REJECT:
			if (INB(np, HS_PRT) == HS_NEGOTIATE)
				sym_nego_rejected(np, tp, cp);
			else {
				sym_print_addr(cp->cmd,
					"M_REJECT received (%x:%x).\n",
					scr_to_cpu(np->lastmsg), np->msgout[0]);
			}
			goto out_clrack;
			break;
		default:
			goto out_reject;
		}
		break;
	/*
	 *  We received an unknown message.
	 *  Ignore all MSG IN phases and reject it.
	 */
	case SIR_MSG_WEIRD:
		sym_print_msg(cp, "WEIRD message received", np->msgin);
		OUTL_DSP(np, SCRIPTB_BA(np, msg_weird));
		return;
	/*
	 *  Negotiation failed.
	 *  Target does not send us the reply.
	 *  Remove the HS_NEGOTIATE status.
	 */
	case SIR_NEGO_FAILED:
		OUTB(np, HS_PRT, HS_BUSY);
	/*
	 *  Negotiation failed.
	 *  Target does not want answer message.
	 */
	case SIR_NEGO_PROTO:
		sym_nego_default(np, tp, cp);
		goto out;
	}

out:
	OUTONB_STD();
	return;
out_reject:
	OUTL_DSP(np, SCRIPTB_BA(np, msg_bad));
	return;
out_clrack:
	OUTL_DSP(np, SCRIPTA_BA(np, clrack));
	return;
out_stuck:
	return;
}