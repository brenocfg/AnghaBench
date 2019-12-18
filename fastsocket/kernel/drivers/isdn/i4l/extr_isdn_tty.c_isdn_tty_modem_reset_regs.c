#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int* mdmreg; int* msn; int* lmsn; scalar_t__ mdmcmdl; int /*<<< orphan*/  plmsn; int /*<<< orphan*/  pmsn; int /*<<< orphan*/  profile; } ;
struct TYPE_6__ {int xmit_size; TYPE_2__ emu; } ;
typedef  TYPE_1__ modem_info ;
typedef  TYPE_2__ atemu ;

/* Variables and functions */
 int BIT_DTRR ; 
 int /*<<< orphan*/  ISDN_LMSNLEN ; 
 int /*<<< orphan*/  ISDN_MODEM_NUMREG ; 
 int /*<<< orphan*/  ISDN_MSNLEN ; 
 size_t REG_DTRR ; 
 size_t REG_PSIZE ; 
 int /*<<< orphan*/  isdn_tty_modem_reset_faxpar (TYPE_1__*) ; 
 int /*<<< orphan*/  isdn_tty_modem_reset_vpar (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
isdn_tty_modem_reset_regs(modem_info * info, int force)
{
	atemu *m = &info->emu;
	if ((m->mdmreg[REG_DTRR] & BIT_DTRR) || force) {
		memcpy(m->mdmreg, m->profile, ISDN_MODEM_NUMREG);
		memcpy(m->msn, m->pmsn, ISDN_MSNLEN);
		memcpy(m->lmsn, m->plmsn, ISDN_LMSNLEN);
		info->xmit_size = m->mdmreg[REG_PSIZE] * 16;
	}
#ifdef CONFIG_ISDN_AUDIO
	isdn_tty_modem_reset_vpar(m);
#endif
#ifdef CONFIG_ISDN_TTY_FAX
	isdn_tty_modem_reset_faxpar(info);
#endif
	m->mdmcmdl = 0;
}