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

/* Variables and functions */

__attribute__((used)) static const char* get_profile(unsigned short profile)
{
   switch (profile)
   {
      case 2:
         return "Removable disk";
         break;
      case 8:
         return "CD-ROM";
         break;
      case 9:
         return "CD-R";
         break;
      case 0xA:
         return "CD-RW";
         break;
      case 0x10:
         return "DVD-ROM";
         break;
      case 0x11:
         return "DVD-R Sequential Recording";
         break;
      case 0x12:
         return "DVD-RAM";
         break;
      case 0x13:
         return "DVD-RW Restricted Overwrite";
         break;
      case 0x14:
         return "DVD-RW Sequential recording";
         break;
      case 0x15:
         return "DVD-R Dual Layer Sequential Recording";
         break;
      case 0x16:
         return "DVD-R Dual Layer Jump Recording";
         break;
      case 0x17:
         return "DVD-RW Dual Layer";
         break;
      case 0x1A:
         return "DVD+RW";
         break;
      case 0x1B:
         return "DVD+R";
         break;
      case 0x2A:
         return "DVD+RW Dual Layer";
         break;
      case 0x2B:
         return "DVD+R Dual Layer";
         break;
      case 0x40:
         return "BD-ROM";
         break;
      case 0x41:
         return "BD-R SRM";
         break;
      case 0x42:
         return "BD-R RRM";
         break;
      case 0x43:
         return "BD-RE";
         break;
      case 0x50:
         return "HD DVD-ROM";
         break;
      case 0x51:
         return "HD DVD-R";
         break;
      case 0x52:
         return "HD DVD-RAM";
         break;
      case 0x53:
         return "HD DVD-RW";
         break;
      case 0x58:
         return "HD DVD-R Dual Layer";
         break;
      case 0x5A:
         return "HD DVD-RW Dual Layer";
         break;
      default:
         break;
   }

   return "Unknown";
}