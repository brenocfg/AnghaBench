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
typedef  int u16 ;

/* Variables and functions */
 int resxratio ; 
 int resyratio ; 
 int vdp2height ; 
 int vdp2width ; 

void VIDGCDVdp2SetResolution(u16 TVMD)
{
   // This needs some work

   // Horizontal Resolution
   switch (TVMD & 0x7)
   {
      case 0:
         vdp2width = 320;
         resxratio=1;
         break;
      case 1:
         vdp2width = 352;
         resxratio=1;
         break;
      case 2: // 640
         vdp2width = 320;
         resxratio=2;
         break;
      case 3: // 704
         vdp2width = 352;
         resxratio=2;
         break;
      case 4:
         vdp2width = 320;
         resxratio=1;
         break;
      case 5:
         vdp2width = 352;
         resxratio=1;
         break;
      case 6: // 640
         vdp2width = 320;
         resxratio=2;
         break;
      case 7: // 704
         vdp2width = 352;
         resxratio=2;
         break;
   }

   // Vertical Resolution
   switch ((TVMD >> 4) & 0x3)
   {
      case 0:
         vdp2height = 224;
         break;
      case 1:
         vdp2height = 240;
         break;
      case 2:
         vdp2height = 256;
         break;
      default: break;
   }
   resyratio=1;

   // Check for interlace
   switch ((TVMD >> 6) & 0x3)
   {
      case 3: // Double-density Interlace
//         vdp2height *= 2;
         resyratio=2;
         break;
      case 2: // Single-density Interlace
      case 0: // Non-interlace
      default: break;
   }
}