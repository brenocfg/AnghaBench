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
struct SiS_Private {int SiS_VBInfo; int UsePanelScaler; int /*<<< orphan*/  SiS_LCDInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  DontExpandLCD ; 
 int SetCRT2ToLCD ; 

__attribute__((used)) static void
SiS_CheckScaling(struct SiS_Private *SiS_Pr, unsigned short resinfo,
			const unsigned char *nonscalingmodes)
{
   int i = 0;
   while(nonscalingmodes[i] != 0xff) {
      if(nonscalingmodes[i++] == resinfo) {
	 if((SiS_Pr->SiS_VBInfo & SetCRT2ToLCD) ||
	    (SiS_Pr->UsePanelScaler == -1)) {
	    SiS_Pr->SiS_LCDInfo |= DontExpandLCD;
	 }
	 break;
      }
   }
}