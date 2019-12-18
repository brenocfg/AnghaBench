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
struct SiS_Private {unsigned short SiS_LCDResInfo; } ;

/* Variables and functions */
 unsigned short Panel661_1280x854 ; 
 unsigned short Panel_1280x768 ; 
#define  Panel_1280x768_2 130 
 unsigned short Panel_1280x800 ; 
#define  Panel_1280x800_2 129 
#define  Panel_1280x854 128 

__attribute__((used)) static unsigned short
SiS_GetBIOSLCDResInfo(struct SiS_Private *SiS_Pr)
{
   unsigned short temp = SiS_Pr->SiS_LCDResInfo;
   /* Translate my LCDResInfo to BIOS value */
   switch(temp) {
   case Panel_1280x768_2: temp = Panel_1280x768;    break;
   case Panel_1280x800_2: temp = Panel_1280x800;    break;
   case Panel_1280x854:   temp = Panel661_1280x854; break;
   }
   return temp;
}