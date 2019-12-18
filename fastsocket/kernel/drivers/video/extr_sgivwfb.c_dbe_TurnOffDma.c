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
struct sgivw_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRLSTAT ; 
 int /*<<< orphan*/  DBE_GETREG (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DBE_SETREG (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  DID_CONTROL ; 
 int /*<<< orphan*/  DID_DMA_ENABLE ; 
 int /*<<< orphan*/  DID_INHWCTRL ; 
 int /*<<< orphan*/  FRM_CONTROL ; 
 int /*<<< orphan*/  FRM_DMA_ENABLE ; 
 int /*<<< orphan*/  FRM_INHWCTRL ; 
 int GET_DBE_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  OVR_CONTROL ; 
 int /*<<< orphan*/  OVR_DMA_ENABLE ; 
 int /*<<< orphan*/  OVR_INHWCTRL ; 
 int /*<<< orphan*/  PCLKSEL ; 
 int /*<<< orphan*/  SET_DBE_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT_FREEZE ; 
 int /*<<< orphan*/  VT_XY ; 
 int /*<<< orphan*/  ctrlstat ; 
 int /*<<< orphan*/  did_control ; 
 int /*<<< orphan*/  did_inhwctrl ; 
 int /*<<< orphan*/  frm_control ; 
 int /*<<< orphan*/  frm_inhwctrl ; 
 int /*<<< orphan*/  ovr_control ; 
 int /*<<< orphan*/  ovr_inhwctrl ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  vt_xy ; 

__attribute__((used)) static void dbe_TurnOffDma(struct sgivw_par *par)
{
	unsigned int readVal;
	int i;

	// Check to see if things are already turned off:
	// 1) Check to see if dbe is not using the internal dotclock.
	// 2) Check to see if the xy counter in dbe is already off.

	DBE_GETREG(ctrlstat, readVal);
	if (GET_DBE_FIELD(CTRLSTAT, PCLKSEL, readVal) < 2)
		return;

	DBE_GETREG(vt_xy, readVal);
	if (GET_DBE_FIELD(VT_XY, VT_FREEZE, readVal) == 1)
		return;

	// Otherwise, turn off dbe

	DBE_GETREG(ovr_control, readVal);
	SET_DBE_FIELD(OVR_CONTROL, OVR_DMA_ENABLE, readVal, 0);
	DBE_SETREG(ovr_control, readVal);
	udelay(1000);
	DBE_GETREG(frm_control, readVal);
	SET_DBE_FIELD(FRM_CONTROL, FRM_DMA_ENABLE, readVal, 0);
	DBE_SETREG(frm_control, readVal);
	udelay(1000);
	DBE_GETREG(did_control, readVal);
	SET_DBE_FIELD(DID_CONTROL, DID_DMA_ENABLE, readVal, 0);
	DBE_SETREG(did_control, readVal);
	udelay(1000);

	// XXX HACK:
	//
	//    This was necessary for GBE--we had to wait through two
	//    vertical retrace periods before the pixel DMA was
	//    turned off for sure.  I've left this in for now, in
	//    case dbe needs it.

	for (i = 0; i < 10000; i++) {
		DBE_GETREG(frm_inhwctrl, readVal);
		if (GET_DBE_FIELD(FRM_INHWCTRL, FRM_DMA_ENABLE, readVal) ==
		    0)
			udelay(10);
		else {
			DBE_GETREG(ovr_inhwctrl, readVal);
			if (GET_DBE_FIELD
			    (OVR_INHWCTRL, OVR_DMA_ENABLE, readVal) == 0)
				udelay(10);
			else {
				DBE_GETREG(did_inhwctrl, readVal);
				if (GET_DBE_FIELD
				    (DID_INHWCTRL, DID_DMA_ENABLE,
				     readVal) == 0)
					udelay(10);
				else
					break;
			}
		}
	}
}