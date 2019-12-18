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
 int BOOT_DEVICE_CDFS ; 
 int BOOT_DEVICE_CDROM ; 
 int BOOT_DEVICE_HDD ; 
 int BOOT_DEVICE_HDD0 ; 
 int BOOT_DEVICE_HOST ; 
 int BOOT_DEVICE_HOST0 ; 
 int BOOT_DEVICE_HOST1 ; 
 int BOOT_DEVICE_HOST2 ; 
 int BOOT_DEVICE_HOST3 ; 
 int BOOT_DEVICE_HOST4 ; 
 int BOOT_DEVICE_HOST5 ; 
 int BOOT_DEVICE_HOST6 ; 
 int BOOT_DEVICE_HOST7 ; 
 int BOOT_DEVICE_HOST8 ; 
 int BOOT_DEVICE_HOST9 ; 
 int BOOT_DEVICE_MASS ; 
 int BOOT_DEVICE_MASS0 ; 
 int BOOT_DEVICE_MC0 ; 
 int BOOT_DEVICE_MC1 ; 
 int BOOT_DEVICE_UNKNOWN ; 
 int /*<<< orphan*/  DEVICE_CDFS ; 
 int /*<<< orphan*/  DEVICE_CDROM ; 
 int /*<<< orphan*/  DEVICE_HDD ; 
 int /*<<< orphan*/  DEVICE_HDD0 ; 
 int /*<<< orphan*/  DEVICE_HOST ; 
 int /*<<< orphan*/  DEVICE_HOST0 ; 
 int /*<<< orphan*/  DEVICE_HOST1 ; 
 int /*<<< orphan*/  DEVICE_HOST2 ; 
 int /*<<< orphan*/  DEVICE_HOST3 ; 
 int /*<<< orphan*/  DEVICE_HOST4 ; 
 int /*<<< orphan*/  DEVICE_HOST5 ; 
 int /*<<< orphan*/  DEVICE_HOST6 ; 
 int /*<<< orphan*/  DEVICE_HOST7 ; 
 int /*<<< orphan*/  DEVICE_HOST8 ; 
 int /*<<< orphan*/  DEVICE_HOST9 ; 
 int /*<<< orphan*/  DEVICE_MASS ; 
 int /*<<< orphan*/  DEVICE_MASS0 ; 
 int /*<<< orphan*/  DEVICE_MC0 ; 
 int /*<<< orphan*/  DEVICE_MC1 ; 
 int /*<<< orphan*/  strncmp (char*,int /*<<< orphan*/ ,int) ; 

enum BootDeviceIDs getBootDeviceID(char *path)
{
   if (!strncmp(path, DEVICE_MC0, 4))
      return BOOT_DEVICE_MC0;
   else if (!strncmp(path, DEVICE_MC1, 4))
      return BOOT_DEVICE_MC1;
   else if (!strncmp(path, DEVICE_CDROM, 7))
      return BOOT_DEVICE_CDROM;
   else if (!strncmp(path, DEVICE_CDFS, 5))
      return BOOT_DEVICE_CDFS;
   else if (!strncmp(path, DEVICE_MASS, 5))
      return BOOT_DEVICE_MASS;
   else if (!strncmp(path, DEVICE_MASS0, 6))
      return BOOT_DEVICE_MASS0;
   else if (!strncmp(path, DEVICE_HDD, 4))
      return BOOT_DEVICE_HDD;
   else if (!strncmp(path, DEVICE_HDD0, 5))
      return BOOT_DEVICE_HDD0;
   else if (!strncmp(path, DEVICE_HOST, 5))
      return BOOT_DEVICE_HOST;
   else if (!strncmp(path, DEVICE_HOST0, 6))
      return BOOT_DEVICE_HOST0;
   else if (!strncmp(path, DEVICE_HOST1, 6))
      return BOOT_DEVICE_HOST1;
   else if (!strncmp(path, DEVICE_HOST2, 6))
      return BOOT_DEVICE_HOST2;
   else if (!strncmp(path, DEVICE_HOST3, 6))
      return BOOT_DEVICE_HOST3;
   else if (!strncmp(path, DEVICE_HOST4, 6))
      return BOOT_DEVICE_HOST4;
   else if (!strncmp(path, DEVICE_HOST5, 6))
      return BOOT_DEVICE_HOST5;
   else if (!strncmp(path, DEVICE_HOST6, 6))
      return BOOT_DEVICE_HOST6;
   else if (!strncmp(path, DEVICE_HOST7, 6))
      return BOOT_DEVICE_HOST7;
   else if (!strncmp(path, DEVICE_HOST8, 6))
      return BOOT_DEVICE_HOST8;
   else if (!strncmp(path, DEVICE_HOST9, 6))
      return BOOT_DEVICE_HOST9;
   else
      return BOOT_DEVICE_UNKNOWN;
}