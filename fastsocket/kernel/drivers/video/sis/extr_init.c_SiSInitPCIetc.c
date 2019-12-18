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
struct SiS_Private {int ChipType; int /*<<< orphan*/  SiS_P3c4; } ;

/* Variables and functions */
#define  SIS_300 146 
#define  SIS_315 145 
#define  SIS_315H 144 
#define  SIS_315PRO 143 
#define  SIS_330 142 
#define  SIS_340 141 
#define  SIS_540 140 
#define  SIS_550 139 
#define  SIS_630 138 
#define  SIS_650 137 
#define  SIS_660 136 
#define  SIS_661 135 
#define  SIS_730 134 
#define  SIS_740 133 
#define  SIS_741 132 
#define  SIS_760 131 
#define  SIS_761 130 
 int /*<<< orphan*/  SiS_SetRegANDOR (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SiS_SetRegOR (int /*<<< orphan*/ ,int,int) ; 
#define  XGI_20 129 
#define  XGI_40 128 

__attribute__((used)) static void
SiSInitPCIetc(struct SiS_Private *SiS_Pr)
{
   switch(SiS_Pr->ChipType) {
#ifdef SIS300
   case SIS_300:
   case SIS_540:
   case SIS_630:
   case SIS_730:
      /* Set - PCI LINEAR ADDRESSING ENABLE (0x80)
       *     - RELOCATED VGA IO ENABLED (0x20)
       *     - MMIO ENABLED (0x01)
       * Leave other bits untouched.
       */
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x20,0xa1);
      /*  - Enable 2D (0x40)
       *  - Enable 3D (0x02)
       *  - Enable 3D Vertex command fetch (0x10) ?
       *  - Enable 3D command parser (0x08) ?
       */
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0x5A);
      break;
#endif
#ifdef SIS315H
   case SIS_315H:
   case SIS_315:
   case SIS_315PRO:
   case SIS_650:
   case SIS_740:
   case SIS_330:
   case SIS_661:
   case SIS_741:
   case SIS_660:
   case SIS_760:
   case SIS_761:
   case SIS_340:
   case XGI_40:
      /* See above */
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x20,0xa1);
      /*  - Enable 3D G/L transformation engine (0x80)
       *  - Enable 2D (0x40)
       *  - Enable 3D vertex command fetch (0x10)
       *  - Enable 3D command parser (0x08)
       *  - Enable 3D (0x02)
       */
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x1E,0xDA);
      break;
   case XGI_20:
   case SIS_550:
      /* See above */
      SiS_SetRegOR(SiS_Pr->SiS_P3c4,0x20,0xa1);
      /* No 3D engine ! */
      /*  - Enable 2D (0x40)
       *  - disable 3D
       */
      SiS_SetRegANDOR(SiS_Pr->SiS_P3c4,0x1E,0x60,0x40);
      break;
#endif
   default:
      break;
   }
}