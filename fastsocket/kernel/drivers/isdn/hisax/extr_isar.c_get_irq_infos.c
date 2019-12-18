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
struct isar_reg {int /*<<< orphan*/  clsb; int /*<<< orphan*/  cmsb; int /*<<< orphan*/  iis; } ;
struct IsdnCardState {int debug; int /*<<< orphan*/  (* BC_Read_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ISAR_CTRL_H ; 
 int /*<<< orphan*/  ISAR_CTRL_L ; 
 int /*<<< orphan*/  ISAR_IIS ; 
 int L1_DEB_HSCX ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
get_irq_infos(struct IsdnCardState *cs, struct isar_reg *ireg)
{
	ireg->iis = cs->BC_Read_Reg(cs, 1, ISAR_IIS);
	ireg->cmsb = cs->BC_Read_Reg(cs, 1, ISAR_CTRL_H);
	ireg->clsb = cs->BC_Read_Reg(cs, 1, ISAR_CTRL_L);
#if DUMP_MBOXFRAME
	if (cs->debug & L1_DEB_HSCX)
		debugl1(cs, "irq_stat(%02x,%02x,%d)", ireg->iis, ireg->cmsb,
			ireg->clsb);
#endif
}