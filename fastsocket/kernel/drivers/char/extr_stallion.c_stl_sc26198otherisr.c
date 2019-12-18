#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  txxon; int /*<<< orphan*/  txxoff; int /*<<< orphan*/  modem; } ;
struct stlport {TYPE_1__ stats; int /*<<< orphan*/  istate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYI_TXFLOWED ; 
 int /*<<< orphan*/  CIR ; 
#define  CIR_SUBBREAK 130 
#define  CIR_SUBCOS 129 
 unsigned char CIR_SUBTYPEMASK ; 
#define  CIR_SUBXONXOFF 128 
 int /*<<< orphan*/  CR_BREAKRESET ; 
 int /*<<< orphan*/  IPR ; 
 unsigned char IPR_DCDCHANGE ; 
 int /*<<< orphan*/  SCCR ; 
 int /*<<< orphan*/  XISR ; 
 unsigned char XISR_RXXOFFGOT ; 
 unsigned char XISR_RXXONGOT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,struct stlport*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stl_cd_change (struct stlport*) ; 
 unsigned char stl_sc26198getglobreg (struct stlport*,int /*<<< orphan*/ ) ; 
 unsigned char stl_sc26198getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_sc26198rxbadchars (struct stlport*) ; 
 int /*<<< orphan*/  stl_sc26198setreg (struct stlport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stl_sc26198otherisr(struct stlport *portp, unsigned int iack)
{
	unsigned char	cir, ipr, xisr;

	pr_debug("stl_sc26198otherisr(portp=%p,iack=%x)\n", portp, iack);

	cir = stl_sc26198getglobreg(portp, CIR);

	switch (cir & CIR_SUBTYPEMASK) {
	case CIR_SUBCOS:
		ipr = stl_sc26198getreg(portp, IPR);
		if (ipr & IPR_DCDCHANGE) {
			stl_cd_change(portp);
			portp->stats.modem++;
		}
		break;
	case CIR_SUBXONXOFF:
		xisr = stl_sc26198getreg(portp, XISR);
		if (xisr & XISR_RXXONGOT) {
			set_bit(ASYI_TXFLOWED, &portp->istate);
			portp->stats.txxoff++;
		}
		if (xisr & XISR_RXXOFFGOT) {
			clear_bit(ASYI_TXFLOWED, &portp->istate);
			portp->stats.txxon++;
		}
		break;
	case CIR_SUBBREAK:
		stl_sc26198setreg(portp, SCCR, CR_BREAKRESET);
		stl_sc26198rxbadchars(portp);
		break;
	default:
		break;
	}
}