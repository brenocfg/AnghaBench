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
struct SiS_Private {scalar_t__ ChipType; int SiS_SysFlags; int /*<<< orphan*/  SiS_P3d4; } ;

/* Variables and functions */
 int SF_760LFB ; 
 int SF_760UMA ; 
 scalar_t__ SIS_760 ; 
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int SiS_GetRegByte (unsigned int) ; 
 int /*<<< orphan*/  SiS_SetRegByte (unsigned int,unsigned char) ; 
 unsigned int pciReadWord (int,int) ; 
 int /*<<< orphan*/  pciWriteByte (int,int,unsigned char) ; 
 unsigned int sisfb_read_mio_pci_word (struct SiS_Private*,int) ; 
 int /*<<< orphan*/  sisfb_write_nbridge_pci_byte (struct SiS_Private*,int,unsigned char) ; 

__attribute__((used)) static void
SiS_Handle760(struct SiS_Private *SiS_Pr)
{
#ifdef SIS315H
   unsigned int somebase;
   unsigned char temp1, temp2, temp3;

   if( (SiS_Pr->ChipType != SIS_760)                         ||
       ((SiS_GetReg(SiS_Pr->SiS_P3d4, 0x5c) & 0xf8) != 0x80) ||
       (!(SiS_Pr->SiS_SysFlags & SF_760LFB))                 ||
       (!(SiS_Pr->SiS_SysFlags & SF_760UMA)) )
      return;

#ifdef SIS_LINUX_KERNEL
   somebase = sisfb_read_mio_pci_word(SiS_Pr, 0x74);
#else
   somebase = pciReadWord(0x00001000, 0x74);
#endif
   somebase &= 0xffff;

   if(somebase == 0) return;

   temp3 = SiS_GetRegByte((somebase + 0x85)) & 0xb7;

   if(SiS_GetReg(SiS_Pr->SiS_P3d4,0x31) & 0x40) {
      temp1 = 0x21;
      temp2 = 0x03;
      temp3 |= 0x08;
   } else {
      temp1 = 0x25;
      temp2 = 0x0b;
   }

#ifdef SIS_LINUX_KERNEL
   sisfb_write_nbridge_pci_byte(SiS_Pr, 0x7e, temp1);
   sisfb_write_nbridge_pci_byte(SiS_Pr, 0x8d, temp2);
#else
   pciWriteByte(0x00000000, 0x7e, temp1);
   pciWriteByte(0x00000000, 0x8d, temp2);
#endif

   SiS_SetRegByte((somebase + 0x85), temp3);
#endif
}