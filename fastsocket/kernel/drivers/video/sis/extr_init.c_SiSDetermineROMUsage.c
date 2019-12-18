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
struct SiS_Private {unsigned char* VirtualRomBase; int SiS_UseROM; int SiS_ROMNew; int SiS_PWDOffset; scalar_t__ ChipType; int SiS_EMIOffset; int SiS661LCD2TableSize; scalar_t__ UseROM; } ;

/* Variables and functions */
 unsigned short SISGETROMW (int) ; 
 scalar_t__ SIS_300 ; 
 scalar_t__ SIS_315H ; 
 int SiSDetermineROMLayout661 (struct SiS_Private*) ; 
 scalar_t__ XGI_20 ; 

__attribute__((used)) static void
SiSDetermineROMUsage(struct SiS_Private *SiS_Pr)
{
   unsigned char  *ROMAddr  = SiS_Pr->VirtualRomBase;
   unsigned short romptr = 0;

   SiS_Pr->SiS_UseROM = false;
   SiS_Pr->SiS_ROMNew = false;
   SiS_Pr->SiS_PWDOffset = 0;

   if(SiS_Pr->ChipType >= XGI_20) return;

   if((ROMAddr) && (SiS_Pr->UseROM)) {
      if(SiS_Pr->ChipType == SIS_300) {
	 /* 300: We check if the code starts below 0x220 by
	  * checking the jmp instruction at the beginning
	  * of the BIOS image.
	  */
	 if((ROMAddr[3] == 0xe9) && ((ROMAddr[5] << 8) | ROMAddr[4]) > 0x21a)
	    SiS_Pr->SiS_UseROM = true;
      } else if(SiS_Pr->ChipType < SIS_315H) {
	 /* Sony's VAIO BIOS 1.09 follows the standard, so perhaps
	  * the others do as well
	  */
	 SiS_Pr->SiS_UseROM = true;
      } else {
	 /* 315/330 series stick to the standard(s) */
	 SiS_Pr->SiS_UseROM = true;
	 if((SiS_Pr->SiS_ROMNew = SiSDetermineROMLayout661(SiS_Pr))) {
	    SiS_Pr->SiS_EMIOffset = 14;
	    SiS_Pr->SiS_PWDOffset = 17;
	    SiS_Pr->SiS661LCD2TableSize = 36;
	    /* Find out about LCD data table entry size */
	    if((romptr = SISGETROMW(0x0102))) {
	       if(ROMAddr[romptr + (32 * 16)] == 0xff)
		  SiS_Pr->SiS661LCD2TableSize = 32;
	       else if(ROMAddr[romptr + (34 * 16)] == 0xff)
		  SiS_Pr->SiS661LCD2TableSize = 34;
	       else if(ROMAddr[romptr + (36 * 16)] == 0xff)	   /* 0.94, 2.05.00+ */
		  SiS_Pr->SiS661LCD2TableSize = 36;
	       else if( (ROMAddr[romptr + (38 * 16)] == 0xff) ||   /* 2.00.00 - 2.02.00 */
		 	(ROMAddr[0x6F] & 0x01) ) {		   /* 2.03.00 - <2.05.00 */
		  SiS_Pr->SiS661LCD2TableSize = 38;		   /* UMC data layout abandoned at 2.05.00 */
		  SiS_Pr->SiS_EMIOffset = 16;
		  SiS_Pr->SiS_PWDOffset = 19;
	       }
	    }
	 }
      }
   }
}