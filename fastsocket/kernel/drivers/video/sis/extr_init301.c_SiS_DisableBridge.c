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
struct SiS_Private {int SiS_VBType; scalar_t__ ChipType; scalar_t__ SiS_CustomT; int SiS_IF_DEF_CH70xx; int /*<<< orphan*/  SiS_Part1Port; int /*<<< orphan*/  SiS_P3c4; int /*<<< orphan*/  SiS_Part2Port; int /*<<< orphan*/  SiS_Part4Port; int /*<<< orphan*/  SiS_P3c6; int /*<<< orphan*/  SiS_P3d4; } ;

/* Variables and functions */
 scalar_t__ CUT_CLEVO1400 ; 
 scalar_t__ CUT_COMPAQ1280 ; 
 scalar_t__ IS_SIS740 ; 
 scalar_t__ SIS_315H ; 
 scalar_t__ SIS_550 ; 
 scalar_t__ SIS_730 ; 
 scalar_t__ SIS_740 ; 
 int /*<<< orphan*/  SiS_CR36BIOSWord23b (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_CR36BIOSWord23d (struct SiS_Private*) ; 
 scalar_t__ SiS_CRT2IsLCD (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_Chrontel701xBLOff (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_Chrontel701xOff (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_DDC2Delay (struct SiS_Private*,int) ; 
 int /*<<< orphan*/  SiS_DisplayOff (struct SiS_Private*) ; 
 unsigned short SiS_GetCH701x (struct SiS_Private*,int) ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int SiS_HandlePWD (struct SiS_Private*) ; 
 scalar_t__ SiS_Is301B (struct SiS_Private*) ; 
 scalar_t__ SiS_IsDualEdge (struct SiS_Private*) ; 
 scalar_t__ SiS_IsLCDOrLCDA (struct SiS_Private*) ; 
 scalar_t__ SiS_IsNotM650orLater (struct SiS_Private*) ; 
 scalar_t__ SiS_IsTVOrYPbPrOrScart (struct SiS_Private*) ; 
 scalar_t__ SiS_IsVAMode (struct SiS_Private*) ; 
 scalar_t__ SiS_IsVAorLCD (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_PanelDelay (struct SiS_Private*,int) ; 
 int /*<<< orphan*/  SiS_PanelDelayLoop (struct SiS_Private*,int,int) ; 
 int /*<<< orphan*/  SiS_SetCH700x (struct SiS_Private*,int,int) ; 
 int /*<<< orphan*/  SiS_SetCH701x (struct SiS_Private*,int,int) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,unsigned short) ; 
 int /*<<< orphan*/  SiS_SetRegAND (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegByte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegSR11ANDOR (struct SiS_Private*,int,int) ; 
 int /*<<< orphan*/  SiS_ShortDelay (struct SiS_Private*,int) ; 
 int /*<<< orphan*/  SiS_UnLockCRT2 (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_WaitVBRetrace (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_WeHaveBacklightCtrl (struct SiS_Private*) ; 
 int VB_SIS30xBLV ; 
 int VB_SISEMI ; 
 int VB_SISLVDS ; 
 int VB_SISVB ; 

void
SiS_DisableBridge(struct SiS_Private *SiS_Pr)
{
#ifdef SIS315H
  unsigned short tempah, pushax=0, modenum;
#endif
  unsigned short temp=0;

  if(SiS_Pr->SiS_VBType & VB_SISVB) {

     if(SiS_Pr->SiS_VBType & VB_SIS30xBLV) {		/* ===== For 30xB/C/LV ===== */

	if(SiS_Pr->ChipType < SIS_315H) {

#ifdef SIS300	   /* 300 series */

	   if(!(SiS_CR36BIOSWord23b(SiS_Pr))) {
	      if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
		 SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xFE);
	      } else {
		 SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x08);
	      }
	      SiS_PanelDelay(SiS_Pr, 3);
	   }
	   if(SiS_Is301B(SiS_Pr)) {
	      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x1f,0x3f);
	      SiS_ShortDelay(SiS_Pr,1);
	   }
	   SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x00,0xDF);
	   SiS_DisplayOff(SiS_Pr);
	   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);
	   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1E,0xDF);
	   SiS_UnLockCRT2(SiS_Pr);
	   if(!(SiS_Pr->SiS_VBType & VB_SISLVDS)) {
	      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x01,0x80);
	      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x02,0x40);
	   }
	   if( (!(SiS_CRT2IsLCD(SiS_Pr))) ||
	       (!(SiS_CR36BIOSWord23d(SiS_Pr))) ) {
	      SiS_PanelDelay(SiS_Pr, 2);
	      if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
	         SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xFD);
	      } else {
		 SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x04);
	      }
	   }

#endif  /* SIS300 */

        } else {

#ifdef SIS315H	   /* 315 series */

	   int didpwd = 0;
	   bool custom1 = (SiS_Pr->SiS_CustomT == CUT_COMPAQ1280) ||
	                  (SiS_Pr->SiS_CustomT == CUT_CLEVO1400);

	   modenum = SiS_GetReg(SiS_Pr->SiS_P3d4,0x34) & 0x7f;

	   if(SiS_Pr->SiS_VBType & VB_SISLVDS) {

#ifdef SET_EMI
	      if(SiS_Pr->SiS_VBType & VB_SISEMI) {
		 if(SiS_Pr->SiS_CustomT != CUT_CLEVO1400) {
		    SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x30,0x0c);
		 }
	      }
#endif

	      didpwd = SiS_HandlePWD(SiS_Pr);

	      if( (modenum <= 0x13)           ||
		  (SiS_IsVAMode(SiS_Pr))      ||
		  (!(SiS_IsDualEdge(SiS_Pr))) ) {
		 if(!didpwd) {
		    SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xfe);
		    if(custom1) SiS_PanelDelay(SiS_Pr, 3);
		 } else {
		    SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xfc);
		 }
	      }

	      if(!custom1) {
		 SiS_DDC2Delay(SiS_Pr,0xff00);
		 SiS_DDC2Delay(SiS_Pr,0xe000);
		 SiS_SetRegByte(SiS_Pr->SiS_P3c6,0x00);
		 pushax = SiS_GetReg(SiS_Pr->SiS_P3c4,0x06);
		 if(IS_SIS740) {
		    SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x06,0xE3);
		 }
	         SiS_PanelDelay(SiS_Pr, 3);
	      }

	   }

	   if(!(SiS_IsNotM650orLater(SiS_Pr))) {
	      /* if(SiS_Pr->ChipType < SIS_340) {*/
		 tempah = 0xef;
		 if(SiS_IsVAMode(SiS_Pr)) tempah = 0xf7;
		 SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x4c,tempah);
	      /*}*/
	   }

	   if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
	      SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x1F,~0x10);
	   }

	   tempah = 0x3f;
	   if(SiS_IsDualEdge(SiS_Pr)) {
	      tempah = 0x7f;
	      if(!(SiS_IsVAMode(SiS_Pr))) tempah = 0xbf;
	   }
	   SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x1F,tempah);

	   if((SiS_IsVAMode(SiS_Pr)) ||
	      ((SiS_Pr->SiS_VBType & VB_SISLVDS) && (modenum <= 0x13))) {

	      SiS_DisplayOff(SiS_Pr);
	      if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
		 SiS_PanelDelay(SiS_Pr, 2);
	      }
	      SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1E,0xDF);

	   }

	   if((!(SiS_IsVAMode(SiS_Pr))) ||
	      ((SiS_Pr->SiS_VBType & VB_SISLVDS) && (modenum <= 0x13))) {

	      if(!(SiS_IsDualEdge(SiS_Pr))) {
		 SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x00,0xdf);
		 SiS_DisplayOff(SiS_Pr);
	      }
	      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x00,0x80);

	      if(SiS_Pr->SiS_VBType & VB_SISLVDS) {
		 SiS_PanelDelay(SiS_Pr, 2);
	      }

	      SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);
	      temp = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00);
	      SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x00,0x10);
	      SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1E,0xDF);
	      SiS_SetReg(SiS_Pr->SiS_Part1Port,0x00,temp);

	   }

	   if(SiS_IsNotM650orLater(SiS_Pr)) {
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0x7f);
	   }

	   if(SiS_Pr->SiS_VBType & VB_SISLVDS) {

	      if( (!(SiS_IsVAMode(SiS_Pr)))  &&
		  (!(SiS_CRT2IsLCD(SiS_Pr))) &&
		  (!(SiS_IsDualEdge(SiS_Pr))) ) {

		 if(custom1) SiS_PanelDelay(SiS_Pr, 2);
		 if(!didpwd) {
		    SiS_SetRegAND(SiS_Pr->SiS_Part4Port,0x26,0xFD);
		 }
		 if(custom1) SiS_PanelDelay(SiS_Pr, 4);
	      }

	      if(!custom1) {
		 SiS_SetReg(SiS_Pr->SiS_P3c4,0x06,pushax);
		 if(SiS_Pr->SiS_VBType & VB_SISEMI) {
		    if(SiS_IsVAorLCD(SiS_Pr)) {
		       SiS_PanelDelayLoop(SiS_Pr, 3, 20);
		    }
		 }
	      }

	   }

#endif /* SIS315H */

	}

     } else {     /* ============ For 301 ================ */

        if(SiS_Pr->ChipType < SIS_315H) {
#ifdef SIS300
	   if(!(SiS_CR36BIOSWord23b(SiS_Pr))) {
	      SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x08);
	      SiS_PanelDelay(SiS_Pr, 3);
	   }
#endif
	}

	SiS_SetRegAND(SiS_Pr->SiS_Part2Port,0x00,0xDF);           /* disable VB */
	SiS_DisplayOff(SiS_Pr);

	if(SiS_Pr->ChipType >= SIS_315H) {
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x00,0x80);
	}

	SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);                /* disable lock mode */

	if(SiS_Pr->ChipType >= SIS_315H) {
	    temp = SiS_GetReg(SiS_Pr->SiS_Part1Port,0x00);
	    SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x00,0x10);
	    SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x20);
	    SiS_SetReg(SiS_Pr->SiS_Part1Port,0x00,temp);
	} else {
#ifdef SIS300
	    SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1E,0xDF);            /* disable CRT2 */
	    if( (!(SiS_CRT2IsLCD(SiS_Pr))) ||
		(!(SiS_CR36BIOSWord23d(SiS_Pr))) ) {
		SiS_PanelDelay(SiS_Pr, 2);
		SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x04);
	    }
#endif
	}

      }

  } else {     /* ============ For LVDS =============*/

    if(SiS_Pr->ChipType < SIS_315H) {

#ifdef SIS300	/* 300 series */

	if(SiS_Pr->SiS_IF_DEF_CH70xx == 1) {
	   SiS_SetCH700x(SiS_Pr,0x0E,0x09);
	}

	if(SiS_Pr->ChipType == SIS_730) {
	   if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x11) & 0x08)) {
	      SiS_WaitVBRetrace(SiS_Pr);
	   }
	   if(!(SiS_CR36BIOSWord23b(SiS_Pr))) {
	      SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x08);
	      SiS_PanelDelay(SiS_Pr, 3);
	   }
	} else {
	   if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x11) & 0x08)) {
	      if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x13) & 0x40)) {
		 if(!(SiS_CR36BIOSWord23b(SiS_Pr))) {
		    SiS_WaitVBRetrace(SiS_Pr);
		    if(!(SiS_GetReg(SiS_Pr->SiS_P3c4,0x06) & 0x1c)) {
		       SiS_DisplayOff(SiS_Pr);
		    }
		    SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x08);
		    SiS_PanelDelay(SiS_Pr, 3);
		 }
	      }
	   }
	}

	SiS_DisplayOff(SiS_Pr);

	SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);

	SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1E,0xDF);
	SiS_UnLockCRT2(SiS_Pr);
	SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x01,0x80);
	SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x02,0x40);

	if( (!(SiS_CRT2IsLCD(SiS_Pr))) ||
	    (!(SiS_CR36BIOSWord23d(SiS_Pr))) ) {
	   SiS_PanelDelay(SiS_Pr, 2);
	   SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x04);
	}

#endif  /* SIS300 */

    } else {

#ifdef SIS315H	/* 315 series */

	if(!(SiS_IsNotM650orLater(SiS_Pr))) {
	   /*if(SiS_Pr->ChipType < SIS_340) { */ /* XGI needs this */
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x4c,~0x18);
	   /* } */
	}

	if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {

	   if(SiS_Pr->ChipType == SIS_740) {
	      temp = SiS_GetCH701x(SiS_Pr,0x61);
	      if(temp < 1) {
		 SiS_SetCH701x(SiS_Pr,0x76,0xac);
		 SiS_SetCH701x(SiS_Pr,0x66,0x00);
	      }

	      if( (!(SiS_IsDualEdge(SiS_Pr))) ||
		  (SiS_IsTVOrYPbPrOrScart(SiS_Pr)) ) {
		 SiS_SetCH701x(SiS_Pr,0x49,0x3e);
	      }
	   }

	   if( (!(SiS_IsDualEdge(SiS_Pr))) ||
	       (SiS_IsVAMode(SiS_Pr)) ) {
	      SiS_Chrontel701xBLOff(SiS_Pr);
	      SiS_Chrontel701xOff(SiS_Pr);
	   }

	   if(SiS_Pr->ChipType != SIS_740) {
	      if( (!(SiS_IsDualEdge(SiS_Pr))) ||
		  (SiS_IsTVOrYPbPrOrScart(SiS_Pr)) ) {
		 SiS_SetCH701x(SiS_Pr,0x49,0x01);
	      }
	   }

	}

	if(SiS_Pr->SiS_IF_DEF_CH70xx == 0) {
	   SiS_SetRegSR11ANDOR(SiS_Pr,0xF7,0x08);
	   SiS_PanelDelay(SiS_Pr, 3);
	}

	if( (SiS_Pr->SiS_IF_DEF_CH70xx == 0)   ||
	    (!(SiS_IsDualEdge(SiS_Pr))) ||
	    (!(SiS_IsTVOrYPbPrOrScart(SiS_Pr))) ) {
	   SiS_DisplayOff(SiS_Pr);
	}

	if( (SiS_Pr->SiS_IF_DEF_CH70xx == 0)   ||
	    (!(SiS_IsDualEdge(SiS_Pr))) ||
	    (!(SiS_IsVAMode(SiS_Pr))) ) {
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x00,0x80);
	}

	if(SiS_Pr->ChipType == SIS_740) {
	   SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0x7f);
	}

	SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x32,0xDF);

	if( (SiS_Pr->SiS_IF_DEF_CH70xx == 0)   ||
	    (!(SiS_IsDualEdge(SiS_Pr))) ||
	    (!(SiS_IsVAMode(SiS_Pr))) ) {
	   SiS_SetRegAND(SiS_Pr->SiS_P3c4,0x1E,0xDF);
	}

	if(SiS_Pr->SiS_IF_DEF_CH70xx == 0) {
	   if(SiS_CRT2IsLCD(SiS_Pr)) {
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1e,0xdf);
	      if(SiS_Pr->ChipType == SIS_550) {
		 SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1e,0xbf);
		 SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1e,0xef);
	      }
	   }
	} else {
	   if(SiS_Pr->ChipType == SIS_740) {
	      if(SiS_IsLCDOrLCDA(SiS_Pr)) {
		 SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1e,0xdf);
	      }
	   } else if(SiS_IsVAMode(SiS_Pr)) {
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x1e,0xdf);
	   }
	}

	if(SiS_Pr->SiS_IF_DEF_CH70xx != 0) {
	   if(SiS_IsDualEdge(SiS_Pr)) {
	      /* SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xff); */
	   } else {
	      SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x13,0xfb);
	   }
	}

	SiS_UnLockCRT2(SiS_Pr);

	if(SiS_Pr->ChipType == SIS_550) {
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x01,0x80); /* DirectDVD PAL?*/
	   SiS_SetRegOR(SiS_Pr->SiS_Part1Port,0x02,0x40); /* VB clock / 4 ? */
	} else if( (SiS_Pr->SiS_IF_DEF_CH70xx == 0)   ||
		   (!(SiS_IsDualEdge(SiS_Pr))) ||
		   (!(SiS_IsVAMode(SiS_Pr))) ) {
	   SiS_SetRegAND(SiS_Pr->SiS_Part1Port,0x2e,0xf7);
	}

        if(SiS_Pr->SiS_IF_DEF_CH70xx == 0) {
	   if(SiS_CRT2IsLCD(SiS_Pr)) {
	      if(!(SiS_WeHaveBacklightCtrl(SiS_Pr))) {
		 SiS_PanelDelay(SiS_Pr, 2);
		 SiS_SetRegSR11ANDOR(SiS_Pr,0xFB,0x04);
	      }
	   }
        }

#endif  /* SIS315H */

    }  /* 315 series */

  }  /* LVDS */

}