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
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_TO_FLASH_U2 (int) ; 
 int /*<<< orphan*/  DATA_TO_FLASH (int /*<<< orphan*/ ) ; 
 scalar_t__ FLASH_DEVICE_16mbit_BOTTOM ; 
 scalar_t__ FLASH_DEVICE_16mbit_TOP ; 
 scalar_t__ FLASH_MANUFACTURER ; 
 scalar_t__ FLASH_TO_DATA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  READ_ARRAY ; 
 int /*<<< orphan*/  READ_ID_CODES ; 
 int /*<<< orphan*/  read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int flash_probe (void)
{
   __u32 manufacturer,devtype;

   /* setup "Read Identifier Codes" mode */
   write32 (DATA_TO_FLASH (READ_ID_CODES),0x00000000);

   /* probe U2. U2/U3 returns the same data since the first 3
	* address lines is mangled in the same way */
   manufacturer = FLASH_TO_DATA (read32 (ADDR_TO_FLASH_U2 (0x00000000)));
   devtype = FLASH_TO_DATA (read32 (ADDR_TO_FLASH_U2 (0x00000001)));

   /* put the flash back into command mode */
   write32 (DATA_TO_FLASH (READ_ARRAY),0x00000000);

   return (manufacturer == FLASH_MANUFACTURER && (devtype == FLASH_DEVICE_16mbit_TOP || devtype == FLASH_DEVICE_16mbit_BOTTOM));
}