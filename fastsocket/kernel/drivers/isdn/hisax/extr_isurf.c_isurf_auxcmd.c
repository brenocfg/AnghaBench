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
typedef  int /*<<< orphan*/  u_long ;
struct IsdnCardState {int /*<<< orphan*/  lock; int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {scalar_t__ command; int arg; } ;
typedef  TYPE_1__ isdn_ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  ISAC_CMDR ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 scalar_t__ ISDN_CMD_IOCTL ; 
 int ISURF_ARCOFI_RESET ; 
 int ISURF_ISAC_RESET ; 
 int ISURF_ISAR_EA ; 
 int /*<<< orphan*/  initisac (struct IsdnCardState*) ; 
 int isar_auxcmd (struct IsdnCardState*,TYPE_1__*) ; 
 int /*<<< orphan*/  reset_isurf (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
isurf_auxcmd(struct IsdnCardState *cs, isdn_ctrl *ic) {
	int ret;
	u_long flags;

	if ((ic->command == ISDN_CMD_IOCTL) && (ic->arg == 9)) {
		ret = isar_auxcmd(cs, ic);
		spin_lock_irqsave(&cs->lock, flags);
		if (!ret) {
			reset_isurf(cs, ISURF_ISAR_EA | ISURF_ISAC_RESET |
				ISURF_ARCOFI_RESET);
			initisac(cs);
			cs->writeisac(cs, ISAC_MASK, 0);
			cs->writeisac(cs, ISAC_CMDR, 0x41);
		}
		spin_unlock_irqrestore(&cs->lock, flags);
		return(ret);
	}
	return(isar_auxcmd(cs, ic));
}