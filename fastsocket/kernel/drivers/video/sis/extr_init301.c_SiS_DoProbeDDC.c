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
struct SiS_Private {int SiS_DDC_DeviceAddr; } ;

/* Variables and functions */
 scalar_t__ SiS_PrepareDDC (struct SiS_Private*) ; 
 scalar_t__ SiS_ReadDDC2Data (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SendACK (struct SiS_Private*,int) ; 
 int /*<<< orphan*/  SiS_SetStop (struct SiS_Private*) ; 
 int /*<<< orphan*/  SiS_SetSwitchDDC2 (struct SiS_Private*) ; 
 int /*<<< orphan*/  X_INFO ; 
 int /*<<< orphan*/  xf86DrvMsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static unsigned short
SiS_DoProbeDDC(struct SiS_Private *SiS_Pr)
{
    unsigned char mask, value;
    unsigned short  temp, ret=0;
    bool failed = false;

    SiS_SetSwitchDDC2(SiS_Pr);
    if(SiS_PrepareDDC(SiS_Pr)) {
         SiS_SetStop(SiS_Pr);
#ifdef SIS_XORG_XF86
#ifdef TWDEBUG
         xf86DrvMsg(0, X_INFO, "Probe: Prepare failed\n");
#endif
#endif
         return 0xFFFF;
    }
    mask = 0xf0;
    value = 0x20;
    if(SiS_Pr->SiS_DDC_DeviceAddr == 0xa0) {
       temp = (unsigned char)SiS_ReadDDC2Data(SiS_Pr);
       SiS_SendACK(SiS_Pr, 0);
       if(temp == 0) {
           mask = 0xff;
	   value = 0xff;
       } else {
           failed = true;
	   ret = 0xFFFF;
#ifdef SIS_XORG_XF86
#ifdef TWDEBUG
           xf86DrvMsg(0, X_INFO, "Probe: Read 1 failed\n");
#endif
#endif
       }
    }
    if(!failed) {
       temp = (unsigned char)SiS_ReadDDC2Data(SiS_Pr);
       SiS_SendACK(SiS_Pr, 1);
       temp &= mask;
       if(temp == value) ret = 0;
       else {
          ret = 0xFFFF;
#ifdef SIS_XORG_XF86
#ifdef TWDEBUG
          xf86DrvMsg(0, X_INFO, "Probe: Read 2 failed\n");
#endif
#endif
          if(SiS_Pr->SiS_DDC_DeviceAddr == 0xa0) {
             if(temp == 0x30) ret = 0;
          }
       }
    }
    SiS_SetStop(SiS_Pr);
    return ret;
}