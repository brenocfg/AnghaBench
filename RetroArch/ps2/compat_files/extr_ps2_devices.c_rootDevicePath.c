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
typedef  enum BootDeviceIDs { ____Placeholder_BootDeviceIDs } BootDeviceIDs ;

/* Variables and functions */
#define  BOOT_DEVICE_CDFS 146 
#define  BOOT_DEVICE_CDROM 145 
#define  BOOT_DEVICE_HDD 144 
#define  BOOT_DEVICE_HDD0 143 
#define  BOOT_DEVICE_HOST 142 
#define  BOOT_DEVICE_HOST0 141 
#define  BOOT_DEVICE_HOST1 140 
#define  BOOT_DEVICE_HOST2 139 
#define  BOOT_DEVICE_HOST3 138 
#define  BOOT_DEVICE_HOST4 137 
#define  BOOT_DEVICE_HOST5 136 
#define  BOOT_DEVICE_HOST6 135 
#define  BOOT_DEVICE_HOST7 134 
#define  BOOT_DEVICE_HOST8 133 
#define  BOOT_DEVICE_HOST9 132 
#define  BOOT_DEVICE_MASS 131 
#define  BOOT_DEVICE_MASS0 130 
#define  BOOT_DEVICE_MC0 129 
#define  BOOT_DEVICE_MC1 128 
 char* DEVICE_CDFS_PATH ; 
 char* DEVICE_CDROM_PATH ; 
 char* DEVICE_HDD0_PATH ; 
 char* DEVICE_HDD_PATH ; 
 char* DEVICE_HOST0_PATH ; 
 char* DEVICE_HOST1_PATH ; 
 char* DEVICE_HOST2_PATH ; 
 char* DEVICE_HOST3_PATH ; 
 char* DEVICE_HOST4_PATH ; 
 char* DEVICE_HOST5_PATH ; 
 char* DEVICE_HOST6_PATH ; 
 char* DEVICE_HOST7_PATH ; 
 char* DEVICE_HOST8_PATH ; 
 char* DEVICE_HOST9_PATH ; 
 char* DEVICE_HOST_PATH ; 
 char* DEVICE_MASS_PATH ; 
 char* DEVICE_MC0_PATH ; 
 char* DEVICE_MC1_PATH ; 

char *rootDevicePath(enum BootDeviceIDs device_id)
{
   switch (device_id)
   {
      case BOOT_DEVICE_MC0:
         return DEVICE_MC0_PATH;
      case BOOT_DEVICE_MC1:
         return DEVICE_MC1_PATH;
      case BOOT_DEVICE_CDROM:
         return DEVICE_CDROM_PATH;
      case BOOT_DEVICE_CDFS:
         return DEVICE_CDFS_PATH;
      case BOOT_DEVICE_MASS:
         return DEVICE_MASS_PATH;
      case BOOT_DEVICE_MASS0:
         return DEVICE_MASS_PATH;
      case BOOT_DEVICE_HDD:
         return DEVICE_HDD_PATH;
      case BOOT_DEVICE_HDD0:
         return DEVICE_HDD0_PATH;
      case BOOT_DEVICE_HOST:
         return DEVICE_HOST_PATH;
      case BOOT_DEVICE_HOST0:
         return DEVICE_HOST0_PATH;
      case BOOT_DEVICE_HOST1:
         return DEVICE_HOST1_PATH;
      case BOOT_DEVICE_HOST2:
         return DEVICE_HOST2_PATH;
      case BOOT_DEVICE_HOST3:
         return DEVICE_HOST3_PATH;
      case BOOT_DEVICE_HOST4:
         return DEVICE_HOST4_PATH;
      case BOOT_DEVICE_HOST5:
         return DEVICE_HOST5_PATH;
      case BOOT_DEVICE_HOST6:
         return DEVICE_HOST6_PATH;
      case BOOT_DEVICE_HOST7:
         return DEVICE_HOST7_PATH;
      case BOOT_DEVICE_HOST8:
         return DEVICE_HOST8_PATH;
      case BOOT_DEVICE_HOST9:
         return DEVICE_HOST9_PATH;
      default:
         return "";
   }
}